#pragma once

#include <HeaderWrapper.hpp>
#include <ArchiveUtil.hpp>

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
  boost::endian::big_int64_buf_at content[64];
  boost::endian::big_int64_buf_at next;
};

class MetaStream : public HeaderWrapper<Meta, MetaStream>
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
  bool isHidden(void) const;
  bool isDirectory(void) const;
protected:
  void saved(void);
friend class StreamWrapper<Meta, MetaStream>;
private:
  DirectoryStream* m_parent;
  bool m_created;
  void created(void);
  void changed(void);
};

#include <Directory.hpp>

inline MetaStream::MetaStream(HeaderStream* header, DirectoryStream* parent)
                                                  : HeaderWrapper<Meta, MetaStream>(header)
                                                  , m_parent(parent)
                                                  , m_created(false)
{
}

inline MetaStream::~MetaStream(void)
{
}

inline boost::posix_time::ptime MetaStream::created(void) const
{
  std::string iso;
  big_to_string(this->m_data.created, iso, sizeof(this->m_data.created));
  return boost::posix_time::from_iso_string(iso);
}

inline boost::posix_time::ptime MetaStream::changed(void) const
{
  std::string iso;
  big_to_string(this->m_data.changed, iso, sizeof(this->m_data.changed));
  return boost::posix_time::from_iso_string(iso);
}

inline std::string MetaStream::name() const
{
  std::string ret;
  big_to_string(this->m_data.name, ret, sizeof(this->m_data.name));
  return ret;
}

inline void MetaStream::name(const std::string& s)
{
  string_to_big(s, this->m_data.name, sizeof(this->m_data.name));
  HeaderWrapper<Meta, MetaStream>::save(&this->m_data.name);
}

inline void MetaStream::saved(void)
{
  if(this->m_created)
  {
    changed();
  }
}

inline void MetaStream::load(void)
{
  HeaderWrapper<Meta, MetaStream>::load();
  this->m_created = true;
}

inline void MetaStream::create(const std::string& n)
{
  if(!this->m_created)
  {
    memset(&this->m_data, 0, sizeof(this->m_data));
    created();
    name(n);
    changed();
    if(dynamic_cast<const DirectoryStream*>(this))
    {
      this->m_data.flags = this->m_data.flags.value() | MF_Directory;
    }
    HeaderWrapper<Meta, MetaStream>::save();
    this->m_created = true;
  }
}

inline DirectoryStream* MetaStream::parent(void) const
{
  return m_parent;
}

inline void MetaStream::parent(DirectoryStream*)
{
}

inline void MetaStream::created(void)
{
  string_to_big(boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time()), this->m_data.created, sizeof(this->m_data.created));
}

inline void MetaStream::changed(void)
{
  string_to_big(boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time()), this->m_data.changed, sizeof(this->m_data.changed));
}

inline void MetaStream::remove(void)
{
  if(this->hasNext())
  {
    this->next()->remove();
  }
  this->getAllocator()->erase(this->pos());
}

inline bool MetaStream::isHidden(void) const
{
  return m_data.flags.value() | MF_Hidden;
}

inline bool MetaStream::isDirectory(void) const
{
  return m_data.flags.value() | MF_Directory;
}
