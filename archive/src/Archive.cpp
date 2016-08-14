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
  fstream* test = new fstream;
  test->open(filename, ios::binary | ios::in);

  if(!test->is_open()) // create the file
  {
    test->open(filename, ios::binary | ios::out);
    m_header = new HeaderStream(test);
    m_header->save();
  }
  test->open(filename, ios::binary | ios::in | ios::out);
  if(m_header != nullptr)
  {
    delete m_header;
  }
  m_header = new HeaderStream(test);
  m_header->load();
  m_stream = test;
}

Archive::Archive(iostream* ios) : m_stream(ios)
{
}

Archive::~Archive()
{
}

int Archive::main(const vector<string>&)
{
  Archive archive("test.db");
  archive.close();
  return 0;
}

void Archive::close()
{
  if(fstream* fs = dynamic_cast<fstream*>(m_stream))
  {
    fs->close();
  }
}
