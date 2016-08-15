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
  DirectoryStream(HeaderStream* header) : MetaStream(header), m_next(nullptr)
  {
  }
  virtual ~DirectoryStream() {}
private:
  DirectoryStream* m_next;
  DirectoryStream* next(void) const
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
};
