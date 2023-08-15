#include "resources/LuaFile.h"

LuaFilePtr LoadLuaFile(const Ogre::String& filename) {
  static std::map<Ogre::String, LuaFilePtr> m_luaFiles;
  if (m_luaFiles.find(filename) != m_luaFiles.end()) {
    return m_luaFiles[filename];
  }
  auto stream = Ogre::ResourceGroupManager::getSingleton().openResource(
      filename, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  auto dataSize = stream->size();
  if (dataSize == 0) return nullptr;
  auto luaFile = std::make_shared<LuaFile>(dataSize);
  stream->read(luaFile->data(), dataSize);
  m_luaFiles[filename] = luaFile;
  return luaFile;
}
