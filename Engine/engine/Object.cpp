//
// Created by Alexandre Tolstenko Nogueira on 3/20/18.
//

#include "Object.h"
#include "Error.h"

int Object::GetInstanceID(){
  return m_InstanceID;
}

bool Object::operator==(const Object &other)
{
  // todo: improve this operator with type check, and make it tolerant to any type of object
  return m_InstanceID == other.m_InstanceID;
}

bool Object::operator!=(const Object &other)
{
  // todo: improve this operator with type check, and make it tolerant to any type of object
  return m_InstanceID != other.m_InstanceID;
}

Object::Object(std::string name) {
  this->name = name;
}

Object::~Object() {

}
