#include <Archive.hpp>

#include <fstream>

using namespace std;

Archive::Archive(void)
{
}

Archive::Archive(const string& filename) : m_header(nullptr)
{
  fstream test;
  test.open(filename, ios::binary | ios::in);
  if(!test.is_open()) // create the file
  {
    test.open(filename, ios::binary | ios::out);
    m_header = new HeaderStream(&test);
    m_header->save();
    delete m_header;
  }
  test.close();
  m_stream.open(filename, ios::binary | ios::in | ios::out);
  if(m_stream.is_open())
  {
    m_header = new HeaderStream(&m_stream);
    m_header->load();
  }
}

Archive::~Archive(void)
{
  delete m_header;
  close();
}

int Archive::main(const vector<string>&)
{
  Archive archive("test.db");
  if(archive.m_stream.is_open())
  {
    DirectoryStream* ds = archive.m_header->getRoot();
    ds->create("Hello world");
    ds->save();
    archive.close();
  }
  return 0;
}

void Archive::close(void)
{
  m_stream.close();
}
