#pragma once

#include <StreamWrapper.hpp>
class HeaderStream;

#include <boost/endian/buffers.hpp>

struct Allocator
{
  boost::endian::big_int64_buf_at pos[100];
  boost::endian::big_int64_buf_at next;
};

class AllocatorStream : public StreamWrapper<Allocator>
{
public:
  AllocatorStream(HeaderStream* header);
  virtual ~AllocatorStream();
  void alloc(void);
  void erase(long);
private:
  AllocatorStream* m_next;
  AllocatorStream* next(void) const;
};

#include <Header.hpp>

inline AllocatorStream::AllocatorStream(HeaderStream* header) : StreamWrapper<Allocator>(header->m_stream), m_next(nullptr)
{
}

inline AllocatorStream::~AllocatorStream()
{
  if(m_next != nullptr)
  {
    delete m_next;
  }
}

inline void AllocatorStream::alloc(void)
{
  if(pos() == 0L)
  {
    m_stream->seekg(0, std::ios::end);
  }
  else
  {
    
  }
}

inline void AllocatorStream::erase(long)
{
}

inline AllocatorStream* AllocatorStream::next(void) const
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
