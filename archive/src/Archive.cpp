#include <Archive.hpp>
#include <Header.hpp>
#include <File.hpp>
#include <Directory.hpp>

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
    readonly.close();
  }
  else
  {
    readonly.close();
  }
 
  return 0;
}
