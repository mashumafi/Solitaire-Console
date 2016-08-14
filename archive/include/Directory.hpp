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
  DirectoryStream(std::iostream* ios) : MetaStream(ios)
  {
  }
  virtual ~DirectoryStream() {}
};
