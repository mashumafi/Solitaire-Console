#include <File.hpp>

FileStream::FileStream(std::istream& is) : StreamWrapper(is)
{
}

FileStream::~FileStream()
{
}
