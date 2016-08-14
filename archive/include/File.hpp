#pragma once

#include <StreamWrapper.hpp>

#include <boost/endian/buffers.hpp>

struct File
{
  boost::endian::big_uint8_buf_at name[256];
};

class FileStream : public StreamWrapper<File>
{
public:
  FileStream(std::istream&);
  virtual ~FileStream();
};
