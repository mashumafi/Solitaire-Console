#pragma once

#include <StreamWrapper.hpp>
#include <Directory.hpp>
#include <File.hpp>

#include <boost/endian/buffers.hpp>

struct Header
{
  boost::endian::big_int64_buf_at m_root;
  boost::endian::big_int64_buf_at m_available;
};

class HeaderStream : public StreamWrapper<Header>
{
public:
  HeaderStream(std::iostream* ios) : StreamWrapper<Header>(ios)
  {
    m_data.m_root = 0;
    m_data.m_available = 0;
  }
  virtual ~HeaderStream() {}
  DirectoryStream* getRoot(void);
  AvailableStream* getAvailable(void);
};
