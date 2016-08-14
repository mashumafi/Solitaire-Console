#include <Header.hpp>

HeaderStream::HeaderStream(std::istream& is) : StreamWrapper(is)
{
}

HeaderStream::~HeaderStream()
{
}
