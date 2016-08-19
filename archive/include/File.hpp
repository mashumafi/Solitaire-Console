#pragma once

#include <Meta.hpp>

class FileStream : public MetaStream
{
public:
  FileStream(HeaderStream* header, DirectoryStream* parent = nullptr);
  virtual ~FileStream(void);
private:
};

inline FileStream::FileStream(HeaderStream* header, DirectoryStream* parent)
                 : MetaStream(header, parent)
{
    std::cout << "File m_pos: " << pos() << std::endl;
}

inline FileStream::~FileStream(void)
{
}
