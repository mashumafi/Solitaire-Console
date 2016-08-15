#pragma once

#include <StreamWrapper.hpp>
#include <ArchiveUtil.hpp>

class HeaderStream;
class AllocatorStream;
class DirectoryStream;
class FileStream;

#include <string>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/endian/buffers.hpp>

struct Header
{
  boost::endian::big_int64_buf_at m_root;
  boost::endian::big_int64_buf_at m_alloc;
};

class HeaderStream : public StreamWrapper<Header>
{
public:
  HeaderStream(std::iostream* ios) : StreamWrapper<Header>(ios), m_root(nullptr), m_alloc(nullptr)
  {
    m_data.m_root = 0;
    m_data.m_alloc = 0;
  }
  virtual ~HeaderStream() {}
  DirectoryStream* getRoot(void);
  AllocatorStream* getAllocator(void);
private:
  DirectoryStream* m_root;
  AllocatorStream* m_alloc;
friend AllocatorStream;
template<class T> friend class MetaStream;
};

struct Allocator
{
  boost::endian::big_int64_buf_at pos[100];
  boost::endian::big_int64_buf_at next;
};

class AllocatorStream : public StreamWrapper<Allocator>
{
public:
  AllocatorStream(HeaderStream* header) : StreamWrapper<Allocator>(header->m_stream), m_next(nullptr) {}
  virtual ~AllocatorStream() {}
  void alloc(void)
  {
  }
  void erase(long)
  {
  }
private:
  AllocatorStream* m_next;
  AllocatorStream* next(void) const
  {
    if(m_next != nullptr)
    {
      return m_next;
    }
    if(m_data.next.value() == 0)
    {
      
    }
    return nullptr;
  }
};

// Meta

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
  MetaStream(HeaderStream* header) : StreamWrapper<T>(header->m_stream) {}
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
private:
  void created(void)
  {
    string_to_big(boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time()), this->data.created, sizeof(this->m_data.created));
  }
  void changed(void)
  {
    string_to_big(boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time()), this->m_data.changed, sizeof(this->m_data.changed));
  }
};

// Directory

struct Directory : Meta
{
  boost::endian::big_int64_buf_at content[64];
  boost::endian::big_int64_buf_at next;
};

class DirectoryStream : public MetaStream<Directory>
{
public:
  DirectoryStream(HeaderStream* header) : MetaStream(header), m_next(nullptr)
  {
  }
  virtual ~DirectoryStream() {}
private:
  DirectoryStream* m_next;
  DirectoryStream* next(void) const
  {
    if(m_next != nullptr)
    {
      return m_next;
    }
    if(m_data.next.value() == 0)
    {
      
    }
    return nullptr;
  }
};

struct File : Meta
{
  boost::endian::big_int8_buf_at content[512];
  boost::endian::big_int64_buf_at next;
};

// File

class FileStream : public MetaStream<File>
{
public:
  FileStream(HeaderStream* header) : MetaStream(header), m_next(nullptr)
  {
  }
  virtual ~FileStream() {}
private:
  FileStream* m_next;
  FileStream* next(void) const
  {
    if(m_next != nullptr)
    {
      return m_next;
    }
    if(m_data.next.value() == 0)
    {
      
    }
    return nullptr;
  }
};

// Definitions

inline DirectoryStream* HeaderStream::getRoot(void)
{
  if(m_root != nullptr)
  {
    return m_root;
  }
  if(m_data.m_root.value() == 0)
  {
    AllocatorStream* allocator = getAllocator();
    allocator->alloc();
  }
  return m_root = new DirectoryStream(this);
}

inline AllocatorStream* HeaderStream::getAllocator(void)
{
  if(m_alloc != nullptr)
  {
    return m_alloc;
  }
  if(m_data.m_alloc.value() == 0)
  {
    
  }
  return m_alloc = new AllocatorStream(this);
}
