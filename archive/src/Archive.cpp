#include <Archive.hpp>
#include <Header.hpp>
#include <File.hpp>
#include <Directory.hpp>

#include <fstream>

using namespace std;

Archive::Archive()
{
}

Archive::Archive(const string& filename)
{
  fstream test;
  test.open(filename, ios::binary | ios::in);

  if(test.is_open()) // the file exists
  {
    m_header = new HeaderStream(test);
  }
  else
  {
    test.close();
  }
}

Archive::Archive(iostream* ios) : m_stream(ios)
{
}

Archive::~Archive()
{
}

int Archive::main(const vector<string>&)
{
 
  return 0;
}
