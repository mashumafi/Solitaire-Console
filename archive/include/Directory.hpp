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
  DirectoryStream* make(std::string);
  FileStream* touch(std::string);
  DirectoryStream* getAbsDir(unsigned long);
private:
  MetaStream** m_meta;
  void addMeta(void);
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

inline void DirectoryStream::addMeta(void)
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
    next()->add();
  }
  else
  {
    (*e_prt) = m_stream->tellg();
    save(e_prt);
    m_stream->seekg(e_prt->value(), std::ios::beg);
  }
}

inline DirectoryStream* DirectoryStream::make(std::string)
{
  addMeta();
  DirectoryStream* child = new DirectoryStream(m_header, this);
  child->create("child");
  return child;
}

inline FileStream* DirectoryStream::touch(std::string)
{
  addMeta();
  FileStream* child = new FileStream(m_header, this);
  child->create("child");
  return child;
}

inline DirectoryStream* DirectoryStream::getAbsDir(unsigned long i)
{
  if(m_meta[i] != nullptr)
  {
    return dynamic_cast<DirectoryStream*>(m_meta[i]);
  }
  AllocatorStream* alloc = nullptr;
  if(i >= sizeof(m_data.content))
  {
    i -= sizeof(Allocator::content);
    if(hasNext())
    {
      alloc = next();
    }
    else
    {
      return nullptr;
    }
    while(i >= sizeof(m_data.content))
    {
      i -= sizeof(m_data.content);
      if(hasNext())
      {
        alloc = next();
      }
      else
      {
        return nullptr;
      }
    }
  }
  if(alloc != nullptr)
  {
    
  }
  else
  {
    
  }
  if(m_data.content[i].value() != 0)
  {
    m_stream->seekg(m_data.content[i].value(), std::ios::beg);
    m_meta[i] = new DirectoryStream(m_header, this);
    m_meta[i]->load();
    return dynamic_cast<DirectoryStream*>(m_meta[i]);
  }
  return nullptr;
}
