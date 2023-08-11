#include "object/Object.h"

Object::Object(const unsigned int objectId, const ObjectType type)
    : m_objectId(objectId), m_objectType(type) {}

Object::Object(const Object& object)
    : m_objectId(object.m_objectId), m_objectType(object.m_objectType) {}

Object::~Object() {}

unsigned int Object::getId() const { return m_objectId; }

Object::ObjectType Object::getType() const { return m_objectType; }