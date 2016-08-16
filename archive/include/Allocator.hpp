#pragma once

#include <HeaderWrapper.hpp>
class HeaderStream;

#include <boost/endian/buffers.hpp>

struct Allocator
{
  boost::endian::big_int64_buf_at pos[101];
  boost::endian::big_int64_buf_at next;
};

class AllocatorStream : public HeaderWrapper<Allocator, AllocatorStream>
{
public:
  AllocatorStream(HeaderStream* header);
  virtual ~AllocatorStream(void);
  void alloc(void);
  void erase(long);
  void remove(void);
  boost::endian::big_int64_buf_at* make(void);
protected:
  void saved(void) {}
friend class StreamWrapper<Allocator, AllocatorStream>;
private:
  HeaderStream* m_header;
};

inline AllocatorStream::AllocatorStream(HeaderStream* header)
                      : HeaderWrapper<Allocator, AllocatorStream>(header)
                      , m_header(header)
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
  }
  else
  {
    long g;
    unsigned int i = 0;
    for(; i < sizeof(m_data.pos); i++)
    {
      if(m_data.pos[i].value() != 0)
      {
        g = m_data.pos[i].value();
        m_data.pos[i] = 0;
        break;
      }
    }
    if(i >= sizeof(m_data.pos))
    {
      if(hasNext())
      {
        next()->alloc();
      }
      else
      {
        m_stream->seekg(0, std::ios::end);
      }
    }
    else
    {
      m_stream->seekg(g, std::ios::end);
    }
  }
}

inline void AllocatorStream::erase(long p)
{
  if(pos() == 0)
  {
    m_pos = p;
    memset(&this->m_data, 0, sizeof(this->m_data));
    save();
    m_header->m_data.m_alloc = p;
    m_header->save(&m_header->m_data.m_alloc);
  }
  else
  {
    unsigned int i = 0;
    for(; i < sizeof(m_data.pos); i++)
    {
      if(m_data.pos[i].value() == 0)
      {
        m_data.pos[i] = p;
        break;
      }
    }
    if(i >= sizeof(m_data.pos))
    {
      next()->erase(p);
    }
  }
}

inline void AllocatorStream::remove(void)
{
  if(this->hasNext())
  {
    this->next()->remove();
  }
  this->getAllocator()->erase(this->pos());
}

inline boost::endian::big_int64_buf_at* AllocatorStream::make(void)
{
  boost::endian::big_int64_buf_at* e_prt = nullptr;
  for(unsigned int i = 0; i < sizeof(m_data.pos); i++)
  {
    if(m_data.pos[i].value() == 0)
    {
      e_prt = m_data.pos + i;
      break;
    }
  }
  if(e_prt == nullptr)
  {
    return next()->make();
  }
  (*e_prt) = m_stream->tellg();
  save(e_prt);
  return e_prt;
}
