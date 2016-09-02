#pragma once

#include <Main.hpp>

#include <Header.hpp>

#include <fstream>

#include <boost/static_assert.hpp>

BOOST_STATIC_ASSERT(sizeof(Meta) == sizeof(Allocator));

class Archive : public Main
{
public:
  Archive(const std::string&);
  Archive(void);
  virtual ~Archive(void);
  using Main::main;
  virtual int main(const std::vector<std::string>&) override;
  DirectoryStream* getRoot(void) const;
  void close(void);
private:
  std::fstream m_stream;
  HeaderStream* m_header;
};
