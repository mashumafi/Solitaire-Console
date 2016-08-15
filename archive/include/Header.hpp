#pragma once

class HeaderStream;
#include <Allocator.hpp>
#include <Directory.hpp>
#include <File.hpp>

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
  DirectoryStream* getRoot(void)
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
  AllocatorStream* getAllocator(void)
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
private:
  DirectoryStream* m_root;
  AllocatorStream* m_alloc;
};
