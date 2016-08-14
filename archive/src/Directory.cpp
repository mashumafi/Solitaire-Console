#include <Directory.hpp>

using namespace std;

using namespace boost::posix_time;

DirectoryStream::DirectoryStream(std::iostream* is) : MetaStream(is)
{
}

DirectoryStream::~DirectoryStream()
{
}
