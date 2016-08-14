#pragma once

#include <StreamWrapper.hpp>

#include <boost/endian/buffers.hpp>

struct Header
{
  boost::endian::big_int64_buf_at root;
  boost::endian::big_int64_buf_at available;
};

class HeaderStream : public StreamWrapper<Header>
{
public:
  HeaderStream(std::iostream*);
  virtual ~HeaderStream();
};
