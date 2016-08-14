#include <File.hpp>

#include <algorithm>

using namespace std;

using namespace boost::posix_time;

FileStream::FileStream(std::iostream* is) : MetaStream(is)
{
}

FileStream::~FileStream()
{
}
