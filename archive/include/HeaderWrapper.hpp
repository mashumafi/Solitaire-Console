#pragma once

#include <StreamWrapper.hpp>

class HeaderStream;
class AllocatorStream;

template<class T, class U> class HeaderWrapper : public StreamWrapper<T, U>
{
public:
  HeaderWrapper(HeaderStream*);
  virtual ~HeaderWrapper(void);
  bool hasNext(void) const;
  AllocatorStream* next(void);
  boost::endian::big_int8_buf_at getByte(int i);
protected:
  HeaderStream* m_header;
  AllocatorStream* getAllocator(void);
private:
  AllocatorStream* m_next;
};

#include <Header.hpp>
#include <Allocator.hpp>

template<class T, class U> inline HeaderWrapper<T, U>::HeaderWrapper(HeaderStream* header)
                                                     : StreamWrapper<T, U>(header->m_stream)
                                                     , m_header(header)
                                                     , m_next(nullptr)
{
}

template<class T, class U> inline HeaderWrapper<T, U>::~HeaderWrapper(void)
{
  if(m_next != nullptr)
  {
    delete m_next;
  }
}

template<class T, class U> inline bool HeaderWrapper<T, U>::hasNext(void) const
{
  return m_next != nullptr;
}

template<class T, class U> inline AllocatorStream* HeaderWrapper<T, U>::next(void)
{
  if(m_next != nullptr)
  {
    return m_next;
  }
  if(this->m_data.next.value() == 0)
  {
    this->m_header->getAllocator()->alloc();
    this->m_data.next = this->m_stream->tellg();
  }
  else
  {
  }
  return nullptr;
}

template<class T, class U> inline boost::endian::big_int8_buf_at HeaderWrapper<T, U>::getByte(int i)
{
  if(i > sizeof(this->m_data.content)*8)
  {
    next()->getByte(i - sizeof(this->m_data.content)*8);
  }
  else
  {
    return static_cast<boost::endian::big_int8_buf_at*>(this->m_data.content)[i];
  }
}

template<class T, class U> inline AllocatorStream* HeaderWrapper<T, U>::getAllocator(void)
{
  return m_header->getAllocator();
}
