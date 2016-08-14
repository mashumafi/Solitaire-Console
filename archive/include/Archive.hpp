#pragma once

#include <Main.hpp>

#include <Header.hpp>
#include <Available.hpp>
#include <Directory.hpp>
#include <File.hpp>

#include <fstream>

#include <boost/static_assert.hpp>

BOOST_STATIC_ASSERT(sizeof(Directory) == sizeof(File));
BOOST_STATIC_ASSERT(sizeof(Available) == sizeof(File));
BOOST_STATIC_ASSERT(sizeof(Directory) == sizeof(Available));

class Archive : public Main
{
private:
  std::iostream* m_stream;
  HeaderStream* m_header;
public:
  Archive(const std::string&);
  Archive(std::iostream*);
  Archive();
  virtual ~Archive();
  virtual int main(const std::vector<std::string>&) override;
  void close();
};
