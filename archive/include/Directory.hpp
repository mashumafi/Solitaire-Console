#pragma once

#include <Meta.hpp>
class FileStream;

#include <string>

struct Directory : Meta
{
  boost::endian::big_int64_buf_at content[64];
  boost::endian::big_int64_buf_at next;
};

class DirectoryStream : public MetaStream<Directory, DirectoryStream>
{
public:
  DirectoryStream(HeaderStream* header, DirectoryStream* parent = nullptr);
  virtual ~DirectoryStream(void);
  DirectoryStream* make(void);
  FileStream* touch(void);
private:
  MetaStream** m_meta;
};

#include <File.hpp>

inline DirectoryStream::DirectoryStream(HeaderStream* header, DirectoryStream* parent)
                      : MetaStream<Directory, DirectoryStream>(header, parent)
                      , m_meta(new MetaStream*[sizeof(m_data.content)]())
{
    std::cout << "Directory m_pos: " << pos() << std::endl;
}

inline DirectoryStream::~DirectoryStream(void)
{
}

inline DirectoryStream* DirectoryStream::make(void)
{
  boost::endian::big_int64_buf_at* e_prt = nullptr;
  for(unsigned int i = 0; i < sizeof(m_data.content); i++)
  {
    if(m_data.content[i].value() == 0)
    {
      e_prt = m_data.content + i;
      break;
    }
  }
  getAllocator()->alloc();
  if(e_prt == nullptr)
  {
    e_prt = next()->make();
  }
  else
  {
    (*e_prt) = m_stream->tellg();
    save(e_prt);
  }
  return new DirectoryStream(m_header, this);
}

inline FileStream* DirectoryStream::touch(void)
{
  getAllocator()->alloc();
  // TODO: add to content
  FileStream* fs = new FileStream(m_header, this);
  return fs;
}
