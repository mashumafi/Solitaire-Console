#pragma once

#include <Main.hpp>

#include <Header.hpp>
#include <Allocator.hpp>
#include <Directory.hpp>
#include <File.hpp>

#include <fstream>

#include <boost/static_assert.hpp>

BOOST_STATIC_ASSERT(sizeof(Directory) == sizeof(File));
BOOST_STATIC_ASSERT(sizeof(Allocator) == sizeof(File));
BOOST_STATIC_ASSERT(sizeof(Directory) == sizeof(Allocator));

class Archive : public Main
{
public:
  Archive(const std::string&);
  Archive();
  virtual ~Archive();
  virtual int main(const std::vector<std::string>&) override;
  void close();
private:
  std::fstream m_stream;
  HeaderStream* m_header;
};
