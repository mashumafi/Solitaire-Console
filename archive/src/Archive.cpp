#include <Archive.hpp>

#include <fstream>
#include <iostream>

using namespace std;

Archive::~Archive()
{
}

int Archive::main(const vector<string>&)
{
  fstream myfile;
  myfile.open("example.txt", ios::binary | ios::in | ios::out);

  if(myfile.is_open())
  {
    myfile << "Writing this to a file.";
    myfile << 123;
    myfile.close();
  }
  else
  {
    cout << "File not found." << endl;
  }
 
  return 0;
}
