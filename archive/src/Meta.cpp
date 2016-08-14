#include <File.hpp>

#include <ArchiveUtil.hpp>

using namespace std;

using namespace boost::posix_time;

template<class T> MetaStream<T>::MetaStream(std::iostream* is) : StreamWrapper<T>(is)
{
}

template<class T> MetaStream<T>::~MetaStream()
{
}

template<class T> ptime MetaStream<T>::created(void) const
{
  std::string iso;
  big_to_string(this->m_data.created, iso, sizeof(this->m_data.created));
  return from_iso_string(iso);
}

template<class T> void MetaStream<T>::created(void)
{
  string_to_big(to_iso_string(second_clock::local_time()), this->data.created, sizeof(this->m_data.created));
}

template<class T> ptime MetaStream<T>::changed(void) const
{
  std::string iso;
  big_to_string(this->m_data.changed, iso, sizeof(this->m_data.changed));
  return from_iso_string(iso);
  
}

template<class T> void MetaStream<T>::changed(void)
{
  string_to_big(to_iso_string(second_clock::local_time()), this->m_data.changed, sizeof(this->m_data.changed));
}

template<class T> std::string MetaStream<T>::name() const
{
  string ret;
  string_to_big(ret, this->m_data, sizeof(this->m_data));
  return ret;
}

template<class T> void MetaStream<T>::name(const std::string& s)
{
  big_to_string(this->data, s, sizeof(this->data));
  save(this->data.name);
}

template<class T> void MetaStream<T>::load(void)
{
  StreamWrapper<T>::load();
  
}

template<class T> void MetaStream<T>::create(const string& n)
{
  created();
  name(n);
  changed();
}
