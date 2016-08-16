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
  virtual ~DirectoryStream(void);
private:
};

inline DirectoryStream::DirectoryStream(HeaderStream* header, DirectoryStream* parent)
     : MetaStream<Directory>(header, parent)
{
    std::cout << "Directory m_pos: " << pos() << std::endl;
}

inline DirectoryStream::~DirectoryStream(void)
{
}
