#pragma once

class Object {
 public:
  enum ObjectType { AGENT, SANDBOX, SANDBOX_OBJECT };

  Object(const unsigned int objectId, const ObjectType type)
      : m_objectId(objectId), m_objectType(type) {}

  Object(const Object& object)
      : m_objectId(object.m_objectId), m_objectType(object.m_objectType) {}

  virtual ~Object() {}

  unsigned int getId() const { return m_objectId; }

  ObjectType getType() const { return m_objectType; }

 private:
  const unsigned int m_objectId;
  const ObjectType m_objectType;

  Object& operator=(Object& object);
};
