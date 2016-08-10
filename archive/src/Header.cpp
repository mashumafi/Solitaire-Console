#include <Header.hpp>

Header::Header()
{
}

template<class Archive>
void Header::save(Archive & ar, const unsigned int version) const
{
  ar & name;
}

template<class Archive>
void Header::load(Archive & ar, const unsigned int version)
{
  ar & name;
}