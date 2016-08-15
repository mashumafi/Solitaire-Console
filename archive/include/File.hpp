#pragma once

#include <Meta.hpp>

struct File : Meta
{
  boost::endian::big_int8_buf_at content[512];
  boost::endian::big_int64_buf_at next;
};

class FileStream : public MetaStream<File>
{
public:
  FileStream(HeaderStream* header) : MetaStream(header), m_next(nullptr)
  {
  }
  virtual ~FileStream() {}
private:
  FileStream* m_next;
  FileStream* next(void) const
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
