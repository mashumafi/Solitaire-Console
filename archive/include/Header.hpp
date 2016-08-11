#pragma once

#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>

class Header
{
  friend class boost::serialization::access;
  std::string name;
  template<class Archive>
  void save(Archive & ar, const unsigned int version) const;
  template<class Archive>
  void load(Archive & ar, const unsigned int version);
  BOOST_SERIALIZATION_SPLIT_MEMBER()
public:
  Header();
};

BOOST_CLASS_VERSION(Header, 0)
