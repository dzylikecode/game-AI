#pragma once
#include <fstream>
#include <vector>

#include "resources/Resource.h"
#include "utils/type.h"

class ResourceManager {
 public:
  static ResourceManager& getInstance() {
    static ResourceManager instance;
    return instance;
  }

 private:
  ResourceManager() {}
  ResourceManager(ResourceManager const&) = delete;
  void operator=(ResourceManager const&) = delete;

 public:
  void addLocation(const String& location) { m_locations.push_back(location); }

 private:
  std::vector<String> m_locations;
};