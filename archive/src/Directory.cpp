#include <Directory.hpp>

Directory::Directory()
{
}

template<class Archive>
void Directory::save(Archive & ar, const unsigned int version) const
{
  ar & name;
}

template<class Archive>
void Directory::load(Archive & ar, const unsigned int version)
{
  ar & name;
}