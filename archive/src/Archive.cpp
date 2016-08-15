#include <Archive.hpp>

#include <fstream>

using namespace std;

Archive::Archive()
{
}

Archive::Archive(const string& filename) : m_header(nullptr)
{
  m_stream.open(filename, ios::binary | ios::in);

  if(!m_stream.is_open()) // create the file
  {
    m_stream.open(filename, ios::binary | ios::out);
    m_header = new HeaderStream(&m_stream);
    m_header->save();
  }
  m_stream.open(filename, ios::binary | ios::in | ios::out);
  if(m_header != nullptr)
  {
    delete m_header;
  }
  m_header = new HeaderStream(&m_stream);
  m_header->load();
}

Archive::~Archive()
{
  delete m_header;
  close();
}

int Archive::main(const vector<string>&)
{
  Archive archive("test.db");
  archive.close();
  return 0;
}

void Archive::close()
{
  m_stream.close();
}
