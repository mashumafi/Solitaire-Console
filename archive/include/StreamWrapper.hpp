#pragma once

#include <fstream>
#include <iostream>

template<class T>
class StreamWrapper
{
public:
  StreamWrapper(std::fstream* ios) : m_stream(ios), m_pos(ios->tellg()) {
    std::cout << "m_pos: " << m_pos << std::endl;
  }
  virtual ~StreamWrapper()
  {
  }
  void save(void) const
  {
    m_stream->seekg(m_pos);
    m_stream->write(reinterpret_cast<const char*>(&m_data), sizeof(T));
  }
  virtual void load(void)
  {
    m_stream->seekp(m_pos);
    m_stream->read(reinterpret_cast<char*>(&m_data), sizeof(T)); 
  }
  long pos(void) const
  {
    return m_pos;
  }
protected:
  T m_data;
  std::fstream* m_stream;
  template<class U> void save(const U& var) const
  {
    m_stream->seekg(m_pos + (&var - &m_data));
    m_stream->write(static_cast<const char*>(var), sizeof(U));
  }
  virtual void saved(void)
  {
  }
private:
  long m_pos;
};
