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
  FileStream(std::iostream* ios) : MetaStream(ios)
  {
  }
  virtual ~FileStream() {}
};
