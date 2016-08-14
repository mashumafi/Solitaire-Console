#pragma once

#include <StreamWrapper.hpp>

#include <boost/endian/buffers.hpp>

struct Directory
{
  boost::endian::big_uint8_buf_at name[256];
};

class DirectoryStream : public StreamWrapper<Directory>
{
public:
  DirectoryStream(std::istream&);
  virtual ~DirectoryStream();
};
