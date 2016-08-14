#pragma once

#include <StreamWrapper.hpp>

#include <boost/endian/buffers.hpp>

struct Header
{
  boost::endian::big_uint32_buf_at root;
};

class HeaderStream : public StreamWrapper<Header>
{
public:
  HeaderStream(std::istream&);
  virtual ~HeaderStream();
};
