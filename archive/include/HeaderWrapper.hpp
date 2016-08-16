#pragma once

#include <StreamWrapper.hpp>

class HeaderStream;
class AllocatorStream;

template<class T> class HeaderWrapper : public StreamWrapper<T>
{
public:
  HeaderWrapper(HeaderStream*);
  virtual ~HeaderWrapper(void);
  bool hasNext(void) const;
  AllocatorStream* next(void);
protected:
  HeaderStream* m_header;
  AllocatorStream* getAllocator(void);
private:
  AllocatorStream* m_next;
};

#include <Header.hpp>
#include <Allocator.hpp>

template<class T> inline HeaderWrapper<T>::HeaderWrapper(HeaderStream* header)
                                      : StreamWrapper<T>(header->m_stream), m_header(header), m_next(nullptr)
{
}

template<class T> inline HeaderWrapper<T>::~HeaderWrapper(void)
{
  if(m_next != nullptr)
  {
    delete m_next;
  }
}

template<class T> inline bool HeaderWrapper<T>::hasNext(void) const
{
  return m_next != nullptr;
}

template<class T> inline AllocatorStream* HeaderWrapper<T>::next(void)
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

template<class T> inline AllocatorStream* HeaderWrapper<T>::getAllocator(void)
{
  return m_header->getAllocator();
}
