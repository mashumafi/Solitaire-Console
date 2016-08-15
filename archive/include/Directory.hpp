#pragma once

#include <Meta.hpp>

#include <string>

struct Directory : Meta
{
  boost::endian::big_int64_buf_at content[64];
  boost::endian::big_int64_buf_at next;
};

class DirectoryStream : public MetaStream<Directory>
{
public:
  DirectoryStream(HeaderStream* header, DirectoryStream* parent = nullptr);
  virtual ~DirectoryStream();
private:
  DirectoryStream* m_next;
  DirectoryStream* next(void) const;
};

#include <Header.hpp>

inline DirectoryStream::DirectoryStream(HeaderStream* header, DirectoryStream* parent)
     : MetaStream<Directory>(header, parent), m_next(nullptr)
{
}

inline DirectoryStream::~DirectoryStream()
{
  if(m_next != nullptr)
  {
    delete m_next;
  }
}

inline DirectoryStream* DirectoryStream::next(void) const
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
