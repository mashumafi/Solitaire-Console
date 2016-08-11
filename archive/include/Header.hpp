#pragma once

#include <boost/serialization/string.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>

class Header
{
  friend class boost::serialization::access;
  template<class Archive>
  void save(Archive& ar, const unsigned int version) const
  {
    ar & root;
  }
  template<class Archive>
  void load(Archive& ar, const unsigned int version)
  {
    ar & root;
  }
  BOOST_SERIALIZATION_SPLIT_MEMBER()
public:
  int root;
  Header();
};

BOOST_CLASS_VERSION(Header, 0)
