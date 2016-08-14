#pragma once

#include <StreamWrapper.hpp>

#include <boost/endian/buffers.hpp>

struct Available
{
  boost::endian::big_int64_buf_at pos[100];
  boost::endian::big_int64_buf_at next;
};

class AvailableStream : public StreamWrapper<Available>
{
public:
  AvailableStream(std::iostream*);
  virtual ~AvailableStream();
};
