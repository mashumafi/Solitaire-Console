#pragma once

#include <HeaderWrapper.hpp>
#include <ArchiveUtil.hpp>
class HeaderStream;
class DirectoryStream;

#include <string>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/endian/buffers.hpp>

enum MetaFlags
{
  MF_Directory = 1,
  MF_Hidden  =   2
};

struct Meta
{
  boost::endian::big_uint64_buf_at flags;
  boost::endian::big_uint8_buf_at created[16];
  boost::endian::big_uint8_buf_at changed[16];
  boost::endian::big_uint8_buf_at name[256];
};

template<class T, class U> class MetaStream : public HeaderWrapper<T, U>
{
public:
  MetaStream(HeaderStream* header, DirectoryStream* parent = nullptr);
  virtual ~MetaStream(void);
  boost::posix_time::ptime created(void) const;
  boost::posix_time::ptime changed(void) const;
  std::string name() const;
  void name(const std::string& s);
  virtual void load(void) override;
  void create(const std::string& n);
  DirectoryStream* parent(void) const;
  void parent(DirectoryStream*);
  void remove();
protected:
  void saved(void);
friend class StreamWrapper<T, U>;
private:
  DirectoryStream* m_parent;
  bool m_created;
  void created(void);
  void changed(void);
};

#include <StreamWrapper.hpp>
#include <Directory.hpp>

template<class T, class U> inline MetaStream<T, U>::MetaStream(HeaderStream* header, DirectoryStream* parent)
                                                  : HeaderWrapper<T, U>(header)
                                                  , m_created(false)
{
}

template<class T, class U> inline MetaStream<T, U>::~MetaStream(void)
{
}

template<class T, class U> inline boost::posix_time::ptime MetaStream<T, U>::created(void) const
{
  std::string iso;
  big_to_string(this->m_data.created, iso, sizeof(this->m_data.created));
  return boost::posix_time::from_iso_string(iso);
}

template<class T, class U> inline boost::posix_time::ptime MetaStream<T, U>::changed(void) const
{
  std::string iso;
  big_to_string(this->m_data.changed, iso, sizeof(this->m_data.changed));
  return boost::posix_time::from_iso_string(iso);
}

template<class T, class U> inline std::string MetaStream<T, U>::name() const
{
  std::string ret;
  big_to_string(this->m_data.name, ret, sizeof(this->m_data.name));
  return ret;
}

template<class T, class U> inline void MetaStream<T, U>::name(const std::string& s)
{
  string_to_big(s, this->m_data.name, sizeof(this->m_data.name));
  HeaderWrapper<T, U>::save(&this->m_data.name);
}

template<class T, class U> inline void MetaStream<T, U>::saved(void)
{
  if(this->m_created)
  {
    changed();
  }
}

template<class T, class U> inline void MetaStream<T, U>::load(void)
{
  HeaderWrapper<T, U>::load();
  this->m_created = true;
}

template<class T, class U> inline void MetaStream<T, U>::create(const std::string& n)
{
  if(!this->m_created)
  {
    memset(&this->m_data, 0, sizeof(this->m_data));
    created();
    name(n);
    changed();
    this->m_created = true;
  }
}

template<class T, class U> inline DirectoryStream* MetaStream<T, U>::parent(void) const
{
  return m_parent;
}

template<class T, class U> inline void MetaStream<T, U>::parent(DirectoryStream*)
{
}

template<class T, class U> inline void MetaStream<T, U>::created(void)
{
  string_to_big(boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time()), this->m_data.created, sizeof(this->m_data.created));
}

template<class T, class U> inline void MetaStream<T, U>::changed(void)
{
  string_to_big(boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time()), this->m_data.changed, sizeof(this->m_data.changed));
}

template<class T, class U> inline void MetaStream<T, U>::remove(void)
{
  if(this->hasNext())
  {
    this->next()->remove();
  }
  this->getAllocator()->erase(this->pos());
}
