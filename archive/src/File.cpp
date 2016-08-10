#include <File.hpp>

File::File()
{
}

template<class Archive>
void File::save(Archive & ar, const unsigned int version) const
{
  ar & name;
}

template<class Archive>
void File::load(Archive & ar, const unsigned int version)
{
  ar & name;
}