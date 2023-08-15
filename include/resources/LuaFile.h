#pragma once

#include <Ogre.h>

#include <memory>

class LuaFile {
 public:
  LuaFile(size_t size) : m_data(new char[size + 1]), m_size(size) {
    m_data[size] = 0;
  }
  ~LuaFile() {
    delete[] m_data;
    m_size = 0;
  }

  auto data() { return m_data; }
  auto getSize() const { return m_size; }

 private:
  char* m_data;
  size_t m_size;
};

using LuaFilePtr = std::shared_ptr<LuaFile>;

LuaFilePtr LoadLuaFile(const Ogre::String& filename);
