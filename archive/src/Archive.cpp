#include <Archive.hpp>

#include <fstream>

using namespace std;

Archive::Archive(void) : m_header(nullptr)
{
}

Archive::Archive(const string& filename) : Archive()
{
  fstream test;
  test.open(filename, ios::binary | ios::in);
  if(!test.is_open()) // create the file
  {
    test.open(filename, ios::binary | ios::out);
    m_header = new HeaderStream(&test);
    m_header->save();
    delete m_header;
    m_header = nullptr;
  }
  test.close();
  m_stream.open(filename, ios::binary | ios::in | ios::out);
  if(m_stream.is_open())
  {
    m_header = new HeaderStream(&m_stream);
    m_header->load();
  }
}

DirectoryStream* Archive::getRoot(void) const
{
  return m_header->getRoot();
}

Archive::~Archive(void)
{
  if(m_header != nullptr)
  {
    delete m_header;
  }
  close();
}

int Archive::main(const vector<string>&)
{
  Archive oarchive("test.db");
  if(oarchive.m_stream.is_open())
  {
    DirectoryStream* root = oarchive.m_header->getRoot();
    cout << root->name();
  }
  return 0;
}

void Archive::close(void)
{
  m_stream.close();
}
