#pragma once

#include <HeaderWrapper.hpp>

#include <boost/endian/buffers.hpp>

struct Allocator
{
  boost::endian::big_int64_buf_at content[101];
  boost::endian::big_int64_buf_at next;
};

class AllocatorStream : public HeaderWrapper<Allocator, AllocatorStream>
{
public:
  AllocatorStream(HeaderStream* header);
  virtual ~AllocatorStream(void);
  void alloc(void);
  void erase(std::streampos);
  void remove(void);
  unsigned int add(void);
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
#ifndef NDEBUG
  std::cout << "Allocator m_pos: " << pos() << std::endl;
#endif
}

inline AllocatorStream::~AllocatorStream(void)
{
}

inline void AllocatorStream::alloc(void)
{
  if(pos() == std::streampos(0))
  {
    m_stream->seekg(0, std::ios::end);
  }
  else
  {
    std::streampos g;
    unsigned int i = 0;
    for(; i < sizeof(m_data.content); i++)
    {
      if(m_data.content[i].value() != 0)
      {
        g = m_data.content[i].value();
        m_data.content[i] = 0;
        break;
      }
    }
    if(i >= sizeof(m_data.content))
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

inline void AllocatorStream::erase(std::streampos p)
{
  if(pos() == std::streampos(0))
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
    for(; i < sizeof(m_data.content); i++)
    {
      if(m_data.content[i].value() == 0)
      {
        m_data.content[i] = p;
        break;
      }
    }
    if(i >= sizeof(m_data.content))
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

inline unsigned int AllocatorStream::add(void)
{
  boost::endian::big_int64_buf_at* e_prt = nullptr;
  unsigned int i = 0;
  for(; i < sizeof(m_data.content); i++)
  {
    if(m_data.content[i].value() == 0)
    {
      e_prt = m_data.content + i;
      break;
    }
  }
  if(e_prt == nullptr)
  {
    return next()->add();
  }
  else
  {
    (*e_prt) = m_stream->tellg();
    save(e_prt);
    m_stream->seekg(e_prt->value(), std::ios::beg);
    return i;
  }
}
