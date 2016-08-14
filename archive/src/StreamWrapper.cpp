#include <StreamWrapper.hpp>

using namespace std;

template<class T> StreamWrapper<T>::StreamWrapper(iostream* ios) : m_stream(ios), m_pos(ios->tellg())
{
}

template<class T> StreamWrapper<T>::~StreamWrapper()
{
}

template<class T> void StreamWrapper<T>::save(void) const
{
  m_stream->seekg(m_pos);
  m_stream->write(static_cast<const char*>(m_data), sizeof(T));
}

template<class T> void StreamWrapper<T>::load(void)
{
  m_stream->seekp(m_pos);
  m_stream->read(static_cast<char*>(m_data), sizeof(T)); 
}
