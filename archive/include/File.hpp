#pragma once

#include <Meta.hpp>

struct File : Meta
{
  boost::endian::big_int64_buf_at length;
  boost::endian::big_int8_buf_at content[504];
  boost::endian::big_int64_buf_at next;
};

class FileStream : public MetaStream<File>
{
public:
  FileStream(HeaderStream* header, DirectoryStream* parent = nullptr);
  virtual ~FileStream(void);
private:
};

inline FileStream::FileStream(HeaderStream* header, DirectoryStream* parent) : MetaStream(header, parent)
{
    std::cout << "File m_pos: " << pos() << std::endl;
}

inline FileStream::~FileStream(void)
{
}
