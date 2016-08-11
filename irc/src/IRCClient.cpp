#include <IRCClient.hpp>

#include <stdarg.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

#include <boost/thread.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>

using namespace boost::assign;
using boost::asio::ip::tcp;

IRCClient::IRCClient(const std::string& host, const std::string& port, const std::string& nick, const std::string& pass) : m_nick(nick), m_pass(pass)
{
  tcp::resolver resolver(io_service);
  tcp::resolver::query query(tcp::v4(), host, port);
  tcp::resolver::iterator iterator = resolver.resolve(query);

  s = new tcp::socket(io_service);
  connect(iterator);
  boost::thread t([this](){ io_service.run(); });
}

IRCClient::~IRCClient()
{
  io_service.stop();
  s->close();
  delete s;
}

void IRCClient::send(const std::string& cmd, const std::vector<std::string>& vec)
{
  send(str(boost::format("%1% %2%") % cmd % boost::algorithm::join(vec, " ")));
}

void IRCClient::send(const std::string& raw)
{
  std::string* msg = new std::string(raw + "\r\n");
  boost::asio::async_write(*s, boost::asio::buffer(msg->c_str(), msg->length()), [msg] (boost::system::error_code ec, std::size_t)
  {
    std::cout << "< " << *msg;
    delete msg;
  });
}

bool IRCClient::message(const Message& msg)
{
  switch(msg.command[0])
  {
    case 'P':
    {
      switch(msg.command[1])
      {
        case 'R': // PRIVMSG
        {
          privmsg(msg, msg.params[0], msg.params[1]);
          return false;
        }
        case 'I': // PING
        {
          if(msg.params.size() == 1)
          {
            ping(msg, msg.params[0]);
          }
          else if(msg.params.size() > 1)
          {
            ping(msg, msg.params[0], msg.params[1]);
          }
          return false;
        }
      }
      return true;
    }
    case 'J': // JOIN
    {
      std::vector<std::string> channels;
      std::vector<std::string> keys;
      if(msg.params.size() > 0)
      {
        boost::split(channels, msg.params[0], boost::is_any_of(","));
      }
      if(msg.params.size() > 1)
      {
        boost::split(keys, msg.params[1], boost::is_any_of(","));
      }
      join(msg, channels, keys);
      return false;
    }
  }
  return true;
}

bool IRCClient::reply(const Message& msg, const Reply code)
{
  return true;
}

void IRCClient::pass(const std::string& password)
{
  send("PASS", list_of(password));
}

void IRCClient::nick(const std::string& nickname)
{
  send("NICK", list_of(nickname));
}
  
void IRCClient::user(const std::string& user, const unsigned int& mode, const std::string& unused, const std::string& realname)
{
}

void IRCClient::oper(const std::string& name, const std::string& password)
{
}

void IRCClient::mode(const std::string& nickname, const std::string& mode)
{
}

void IRCClient::service(const std::string& nickname, const std::string& reserved1, const std::string& distribution, const std::string& type, const std::string& reserved2, const std::string& info)
{
}

void IRCClient::quit(const std::string& quit_message)
{
  send("QUIT", list_of(quit_message));
}

void IRCClient::squit(const std::string& server, const std::string& comment)
{
}

void IRCClient::join(const std::vector<std::string>& channels, const std::vector<std::string>& keys)
{
  join(boost::algorithm::join(channels, ","), boost::algorithm::join(keys, ","));
}

void IRCClient::join(const std::string& channels, const std::string& keys)
{
  send("JOIN", list_of(channels)(keys));
}

void IRCClient::join0()
{
  send("JOIN", list_of("0"));
}

void IRCClient::join(const Message& msg, const std::vector<std::string>& channels, const std::vector<std::string>& keys)
{
  std::cout << boost::format("%1% joined %2%") % msg.nickname % boost::algorithm::join(channels, ",") << std::endl;
}

void IRCClient::part(const std::vector<std::string>& channels, const std::string& part_message)
{
  part(boost::algorithm::join(channels, ","), part_message);
}

void IRCClient::part(const std::string& channels, const std::string& part_message)
{
  send("PART", list_of(channels)(part_message));
}

void IRCClient::part(const Message& msg)
{
}

void IRCClient::mode(const std::string& channel, const std::string& modes, const std::string& modeparams)
{
}

void IRCClient::topic(const std::string& channel, const std::string& topic)
{
}

void IRCClient::names(const std::vector<std::string>& channels, const std::string& target)
{
}

void IRCClient::names(const std::string& channels, const std::string& target)
{
}

void IRCClient::list(const std::vector<std::string>& channels, const std::string& target)
{
}

void IRCClient::list(const std::string& channels, const std::string& target)
{
}

void IRCClient::invite(const std::string& nickname, const std::string& channel)
{
  
}

void IRCClient::kick(const std::vector<std::string>& channels, const std::vector<std::string>& users, const std::string& comment)
{
  
}

void IRCClient::privmsg(const std::string& msgtarget, const std::string& text_to_be_sent)
{
  send("PRIVMSG", list_of(msgtarget)(":" + text_to_be_sent));
}

void IRCClient::privmsg(const Message& msg, const std::string& msgtarget, const std::string& text_to_be_sent)
{
  std::cout << msgtarget << "> " << msg.nickname << ": " << text_to_be_sent << std::endl;
}

void IRCClient::notice(const std::string& msgtarget, const std::string& text)
{
}

void IRCClient::motd(const std::string& target)
{
}

void IRCClient::lusers(const std::string& mask, const std::string& target)
{
}

void IRCClient::version(const std::string& target)
{
}

void IRCClient::stats(const std::string& query, const std::string& target)
{
}

void IRCClient::links(const std::string& remote_server, const std::string& server_mask)
{
}

void IRCClient::time(const std::string& target)
{
}

void IRCClient::connect(const std::string& target_server, const std::string& port, const std::string& remote_server)
{
}

void IRCClient::trace(const std::string& target)
{
}

void IRCClient::admin(const std::string& target)
{
}

void IRCClient::info(const std::string& target)
{
}
  
void IRCClient::servlist(const std::string& mask, const std::string& type)
{
}

void IRCClient::squery(const std::string& servicename, const std::string& text)
{
}

void IRCClient::who(const std::string& mask, const std::string& parameter)
{
}

void IRCClient::whois(const std::string& mask, const std::string& target)
{
}

void IRCClient::whowas(const std::string& nicknames, unsigned int count, const std::string& target)
{
}

void IRCClient::kill(const std::string& nickname, const std::string& comment)
{
  
}

void IRCClient::ping(const std::string& server, const std::string& server2)
{
  send("PING", list_of(server)(server2));
}

void IRCClient::ping(const Message& msg, const std::string& server, const std::string& server2)
{
  pong(server, server2);
}

void IRCClient::pong(const std::string& server, const std::string& server2)
{
  send("PONG", list_of(server)(server2));
}

void IRCClient::error(const std::string& error_message)
{
  
}

void IRCClient::connect(tcp::resolver::iterator endpoint_iterator)
{
  boost::asio::async_connect(*s, endpoint_iterator,
    [this](boost::system::error_code ec, tcp::resolver::iterator)
    {
      if (!ec)
      {
        read();
        connected();
      }
      else
      {
      }
    });
}

void IRCClient::read()
{
  boost::asio::async_read_until(*s, response, "\r\n",
    [this](boost::system::error_code ec, std::size_t)
    {
      if (!ec)
      {
        std::istream response_stream(&response);
        std::string line;
        do
        {
          getline(response_stream, line);
          read(line);
        } while(response.size() > 0);
        read();
      }
      else
      {
        s->close();
      }
    });
}

void IRCClient::read(const std::string& msg)
{
  read(Message(msg));
}

void IRCClient::read(const Message& msg)
{
  try
  {
    if(reply(msg, static_cast<Reply>(stoi(msg.command))))
    {
      std::cout << "> " << msg.raw() << std::endl;
    }
  }
  catch(std::invalid_argument)
  {
    if(message(msg))
    {
      std::cout << "> " << msg.raw() << std::endl;
    }
  }
}

void IRCClient::connected()
{
  pass(m_pass);
  nick(m_nick);
}

void IRCClient::close()
{
  io_service.post([this]() { s->close(); });
}
