#pragma once

#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>

class File
{
  friend class boost::serialization::access;
  std::string name;
  template<class Archive>
  void save(Archive & ar, const unsigned int version) const;
  template<class Archive>
  void load(Archive & ar, const unsigned int version);
  BOOST_SERIALIZATION_SPLIT_MEMBER()
public:
  File();
};

BOOST_CLASS_VERSION(File, 0)
