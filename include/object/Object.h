#pragma once

class Object {
 public:
  enum ObjectType { AGENT, SANDBOX, SANDBOX_OBJECT };

  Object(const unsigned int objectId, const ObjectType type);

  Object(const Object& object);

  virtual ~Object();

  unsigned int getId() const;

  ObjectType getType() const;

 private:
  const unsigned int m_objectId;
  const ObjectType m_objectType;

  Object& operator=(Object& object);
};
