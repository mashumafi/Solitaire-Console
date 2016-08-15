#pragma once

#include <StreamWrapper.hpp>
#include <ArchiveUtil.hpp>
class HeaderStream;
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
  MetaStream(HeaderStream* header, DirectoryStream* parent = nullptr);
  virtual ~MetaStream();
  boost::posix_time::ptime created(void) const;
  boost::posix_time::ptime changed(void) const;
  std::string name() const;
  void name(const std::string& s);
  virtual void saved(void) override;
  virtual void load(void) override;
  void create(const std::string& n);
  DirectoryStream* parent(void) const;
  void parent(DirectoryStream*);
private:
  DirectoryStream* m_parent;
  void created(void);
  void changed(void);
};

#include <Header.hpp>
#include <Directory.hpp>

template<class T> inline MetaStream<T>::MetaStream(HeaderStream* header, DirectoryStream* parent) : StreamWrapper<T>(header->m_stream)
{
}

template<class T> inline MetaStream<T>::~MetaStream()
{
}

template<class T> inline boost::posix_time::ptime MetaStream<T>::created(void) const
{
  std::string iso;
  big_to_string(this->m_data.created, iso, sizeof(this->m_data.created));
  return boost::posix_time::from_iso_string(iso);
}

template<class T> inline boost::posix_time::ptime MetaStream<T>::changed(void) const
{
  std::string iso;
  big_to_string(this->m_data.changed, iso, sizeof(this->m_data.changed));
  return boost::posix_time::from_iso_string(iso);
}

template<class T> inline std::string MetaStream<T>::name() const
{
  std::string ret;
  string_to_big(ret, this->m_data, sizeof(this->m_data));
  return ret;
}

template<class T> inline void MetaStream<T>::name(const std::string& s)
{
  big_to_string(this->m_data, s, sizeof(this->m_data));
  save(this->m_data.name);
}

template<class T> inline void MetaStream<T>::saved(void)
{
  changed();
}

template<class T> inline void MetaStream<T>::load(void)
{
  StreamWrapper<T>::load();
}

template<class T> inline void MetaStream<T>::create(const std::string& n)
{
  created();
  name(n);
  changed();
}

template<class T> inline DirectoryStream* MetaStream<T>::parent(void) const
{
  return m_parent;
}

template<class T> inline void MetaStream<T>::parent(DirectoryStream*)
{
}

template<class T> inline void MetaStream<T>::created(void)
{
  string_to_big(boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time()), this->data.created, sizeof(this->m_data.created));
}


template<class T> inline void MetaStream<T>::changed(void)
{
  string_to_big(boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time()), this->m_data.changed, sizeof(this->m_data.changed));
}
