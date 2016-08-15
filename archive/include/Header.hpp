#pragma once

#include "StreamWrapper.hpp"
class AllocatorStream;
class DirectoryStream;

#include <boost/endian/buffers.hpp>

struct Header
{
  boost::endian::big_int64_buf_at m_root;
  boost::endian::big_int64_buf_at m_alloc;
};

class HeaderStream : public StreamWrapper<Header>
{
public:
  HeaderStream(std::fstream*);
  virtual ~HeaderStream();
  DirectoryStream* getRoot(void);
  AllocatorStream* getAllocator(void);
private:
  DirectoryStream* m_root;
  AllocatorStream* m_alloc;
friend class AllocatorStream;
template<class T> friend class MetaStream;
};

#include <Allocator.hpp>
#include <Directory.hpp>

inline HeaderStream::HeaderStream(std::fstream* ios) : StreamWrapper<Header>(ios), m_root(nullptr), m_alloc(nullptr)
{
  m_data.m_root = 0;
  m_data.m_alloc = 0;
}

inline HeaderStream::~HeaderStream()
{
  if(m_root != nullptr)
  {
    delete m_root;
  }
  if(m_alloc != nullptr)
  {
    delete m_alloc;
  }
}

inline DirectoryStream* HeaderStream::getRoot(void)
{
  if(m_root != nullptr)
  {
    return m_root;
  }
  if(m_data.m_root.value() == 0)
  {
    getAllocator()->alloc();
  }
  else
  {
    m_stream->seekp(m_data.m_root.value());
  }
  return m_root = new DirectoryStream(this);
}

inline AllocatorStream* HeaderStream::getAllocator(void)
{
  if(m_alloc != nullptr)
  {
    return m_alloc;
  }
  m_stream->seekp(m_data.m_alloc.value() == 0 ? 0 : m_data.m_alloc.value());
  return m_alloc = new AllocatorStream(this);
}
