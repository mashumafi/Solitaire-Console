#include <Directory.hpp>

DirectoryStream::DirectoryStream(std::istream& is) : StreamWrapper(is)
{
}

DirectoryStream::~DirectoryStream()
{
}
