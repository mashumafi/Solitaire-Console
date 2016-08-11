#pragma once

#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>

class Directory
{
  friend class boost::serialization::access;
  std::string name;
  template<class Archive>
  void save(Archive & ar, const unsigned int version) const
  {
    ar & name;
  }
  template<class Archive>
  void load(Archive & ar, const unsigned int version)
  {
    ar & name;
  }
  BOOST_SERIALIZATION_SPLIT_MEMBER()
public:
  Directory();
};

BOOST_CLASS_VERSION(Directory, 0)
