#include <ArchiveUtil.hpp>

#include <algorithm>

using namespace std;

void string_to_big(const std::string& src, boost::endian::big_uint8_buf_at* dest, size_t length)
{
  length = min(length - 1, src.length());
  size_t i = 0;
  for(; i < length; i++)
  {
    dest[i] = src[i];
  }
  dest[i] = '\0';
}

void big_to_string(const boost::endian::big_uint8_buf_at* src, std::string& dest, size_t length)
{
  char buf[length];
  for(size_t i = 0; i < length; i++)
  {
    buf[i] = src[i].value();
  }
  dest = string(buf);
}
