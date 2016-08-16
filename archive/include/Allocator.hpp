#pragma once

#include <HeaderWrapper.hpp>
class HeaderStream;

#include <boost/endian/buffers.hpp>
#include <boost/endian/arithmetic.hpp>

struct Allocator
{
  boost::endian::big_int64_buf_at pos[100];
  boost::endian::big_int64_buf_at next;
};

class AllocatorStream : public HeaderWrapper<Allocator>
{
public:
  AllocatorStream(HeaderStream* header);
  virtual ~AllocatorStream(void);
  void alloc(void);
  void erase(long);
private:
  HeaderStream* m_header;
};

inline AllocatorStream::AllocatorStream(HeaderStream* header)
             : HeaderWrapper<Allocator>(header), m_header(header)
{
    std::cout << "Allocator m_pos: " << pos() << std::endl;
}

inline AllocatorStream::~AllocatorStream(void)
{
}

inline void AllocatorStream::alloc(void)
{
  if(pos() == 0)
  {
    m_stream->seekg(0, std::ios::end);
    std::cout << "Appending" << std::endl;
  }
  else
  {
  }
}

inline void AllocatorStream::erase(long)
{
}
