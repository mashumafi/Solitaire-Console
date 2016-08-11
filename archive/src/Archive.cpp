#include <Archive.hpp>
#include <Header.hpp>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include <fstream>
#include <iostream>

using namespace std;

Archive::~Archive()
{
}

int Archive::main(const vector<string>&)
{
  fstream myfile;
  myfile.open("example.txt", ios::binary | ios::in);
  Header header;
  std::ofstream ofs("filename");

  if(myfile.is_open())
  {
    //boost::archive::xml_oarchive oa(ofs);
    //oa << header;
    myfile.close();
  }
  else
  {
    cout << "File not found." << endl;
  }
 
  return 0;
}
