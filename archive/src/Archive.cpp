#include <Archive.hpp>
#include <Header.hpp>
#include <File.hpp>
#include <Directory.hpp>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <fstream>
#include <iostream>

using namespace std;

Archive::~Archive()
{
}

int Archive::main(const vector<string>&)
{
  fstream readonly;
  readonly.open("example.ar", ios::binary | ios::in);
  Header header;

  if(readonly.is_open())
  {
    boost::archive::binary_iarchive ia(readonly);
    ia >> header;
    std::cout << header.root << std::endl;
    readonly.close();
  }
  else
  {
    readonly.close();
    readonly.open("example.ar", ios::binary | ios::out);
    boost::archive::binary_oarchive oa(readonly);
    header.root = 50;
    oa << header;
    readonly.close();
  }
 
  return 0;
}
