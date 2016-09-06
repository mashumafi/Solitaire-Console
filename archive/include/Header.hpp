#pragma once

#include <StreamWrapper.hpp>
class AllocatorStream;
class DirectoryStream;

#include <boost/endian/buffers.hpp>

struct Header
{
  boost::endian::big_int64_buf_at m_root;
  boost::endian::big_int64_buf_at m_alloc;
};

class HeaderStream : public StreamWrapper<Header, HeaderStream>
{
public:
  HeaderStream(std::fstream*);
  virtual ~HeaderStream(void);
  DirectoryStream* getRoot(void);
protected:
  AllocatorStream* getAllocator(void);
  void saved(void) {}
friend class StreamWrapper<Header, HeaderStream>;
private:
  DirectoryStream* m_root;
  AllocatorStream* m_alloc;
template<class T, class U> friend class HeaderWrapper;
friend class AllocatorStream;
};

#include <Allocator.hpp>
#include <Meta.hpp>

inline HeaderStream::HeaderStream(std::fstream* ios)
                   : StreamWrapper<Header, HeaderStream>(ios)
                   , m_root(nullptr)
                   , m_alloc(nullptr)
{
#ifndef NDEBUG
  std::cout << "Header    m_pos: " << pos() << std::endl;
#endif
  m_data.m_root = 0;
  m_data.m_alloc = 0;
}

inline HeaderStream::~HeaderStream(void)
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
    m_data.m_root = m_stream->tellg();
    save(&m_data.m_root);
    m_stream->seekg(m_data.m_root.value());
    m_root = new DirectoryStream(this);
    m_root->create("root");
    return m_root;
  }
  m_stream->seekg(m_data.m_root.value(), std::ios::beg);
  m_root = new DirectoryStream(this);
  m_root->load();
  return m_root;
}

inline AllocatorStream* HeaderStream::getAllocator(void)
{
  if(m_alloc != nullptr)
  {
    return m_alloc;
  }
  m_stream->seekg(m_data.m_alloc.value() == 0 ? 0 : m_data.m_alloc.value(), std::ios::beg);
  return m_alloc = new AllocatorStream(this);
}
