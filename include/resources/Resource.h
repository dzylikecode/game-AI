#pragma once
#include "utils/type.h"

class Resource {
 public:
  Resource() {}
  virtual ~Resource() {}
  virtual void load() = 0;
  virtual void unload() = 0;

 public:
  const String& getName() const { return m_name; }
  void reload() {
    unload();
    load();
  }

 protected:
  String m_name;
};