#pragma once

#include "resources/ResourceManager.h"
#include "utils/type.h"

class LuaFilePtr;

/**
 * @brief The LuaFileManager class is a singleton class that manages the Lua
 *
 */
class LuaFileManager {
 public:
  static LuaFileManager &getInstance() {
    static LuaFileManager instance;
    return instance;
  }

 public:
  virtual LuaFilePtr load(const String &resourceName, const String &group);

 private:
  LuaFileManager() {}
  LuaFileManager(LuaFileManager const &) = delete;
  void operator=(LuaFileManager const &) = delete;
};