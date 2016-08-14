#include <Header.hpp>

HeaderStream::HeaderStream(std::iostream* is) : StreamWrapper(is)
{
}

HeaderStream::~HeaderStream()
{
}
