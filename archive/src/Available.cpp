#include <Available.hpp>

AvailableStream::AvailableStream(std::iostream* is) : StreamWrapper(is)
{
}

AvailableStream::~AvailableStream()
{
}
