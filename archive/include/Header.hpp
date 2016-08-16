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

class HeaderStream : public StreamWrapper<Header>
{
public:
  HeaderStream(std::fstream*);
  virtual ~HeaderStream(void);
  DirectoryStream* getRoot(void);
protected:
  AllocatorStream* getAllocator(void);
private:
  DirectoryStream* m_root;
  AllocatorStream* m_alloc;
template<class T> friend class HeaderWrapper;
};

#include <Allocator.hpp>
#include <Directory.hpp>

inline HeaderStream::HeaderStream(std::fstream* ios) : StreamWrapper<Header>(ios), m_root(nullptr), m_alloc(nullptr)
{
  std::cout << "Header    m_pos: " << pos() << std::endl;
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
  }
  else
  {
    m_stream->seekg(m_data.m_root.value());
  }
  m_data.m_root = m_stream->tellg();
  save(&m_data.m_root);
  return m_root = new DirectoryStream(this);
}

inline AllocatorStream* HeaderStream::getAllocator(void)
{
  if(m_alloc != nullptr)
  {
    return m_alloc;
  }
  m_stream->seekg(m_data.m_alloc.value() == 0 ? 0 : m_data.m_alloc.value());
  m_data.m_alloc = m_stream->tellg();
  save(&m_data.m_alloc);
  return m_alloc = new AllocatorStream(this);
}
