#pragma once

#include <StreamWrapper.hpp>
#include <ArchiveUtil.hpp>
#include <Header.hpp>
class DirectoryStream;

#include <string>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/endian/buffers.hpp>

const std::string ISO_FORMAT = "YYYYMMDDTHHMMSS";

struct Meta
{
  boost::endian::big_uint8_buf_at name[256];
  boost::endian::big_uint8_buf_at created[16];
  boost::endian::big_uint8_buf_at changed[16];
};

template<class T> class MetaStream : public StreamWrapper<T>
{
public:
  MetaStream(HeaderStream* header, DirectoryStream* parent = nullptr) : StreamWrapper<T>(nullptr) {}
  virtual ~MetaStream() {}
  boost::posix_time::ptime created(void) const
  {
    std::string iso;
    big_to_string(this->m_data.created, iso, sizeof(this->m_data.created));
    return boost::posix_time::from_iso_string(iso);
  }
  boost::posix_time::ptime changed(void) const
  {
    std::string iso;
    big_to_string(this->m_data.changed, iso, sizeof(this->m_data.changed));
    return boost::posix_time::from_iso_string(iso);
  }
  std::string name() const
  {
    std::string ret;
    string_to_big(ret, this->m_data, sizeof(this->m_data));
    return ret;
  }
  void name(const std::string& s)
  {
    big_to_string(this->m_data, s, sizeof(this->m_data));
    save(this->m_data.name);
  }
  virtual void saved(void) override
  {
    changed();
  }
  virtual void load(void) override
  {
    StreamWrapper<T>::load();
  }
  void create(const std::string& n)
  {
    created();
    name(n);
    changed();
  }
  DirectoryStream* parent(void) const { return m_parent; }
  void parent(DirectoryStream*) { }
private:
  DirectoryStream* m_parent;
  void created(void)
  {
    string_to_big(boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time()), this->data.created, sizeof(this->m_data.created));
  }
  void changed(void)
  {
    string_to_big(boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time()), this->m_data.changed, sizeof(this->m_data.changed));
  }
};
