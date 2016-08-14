#include <string>

#include <boost/endian/buffers.hpp>

void string_to_big(const std::string&, boost::endian::big_uint8_buf_at*, size_t length);

void big_to_string(const boost::endian::big_uint8_buf_at*, std::string&, size_t length);
