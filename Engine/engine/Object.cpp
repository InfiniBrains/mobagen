//
// Created by Alexandre Tolstenko Nogueira on 3/20/18.
//

#include "Object.h"
#include "Error.h"

int Object::GetInstanceID(){
  return m_InstanceID;
}

void Object::Destroy(std::shared_ptr<Object>) {
  throw NotImplementedException();
}

void Object::DestroyImmediate(std::shared_ptr<Object>) {
  throw NotImplementedException();
}

void Object::DontDestroyOnLoad(std::shared_ptr<Object>) {
  throw NotImplementedException();
}

template<class T>
std::shared_ptr<T> Object::FindObjectOfType(void) {
  throw NotImplementedException();
  return std::shared_ptr<T>();
}

template<class T>
std::vector<std::shared_ptr<T>> Object::FindObjectsOfType() {
  throw NotImplementedException();
  return std::vector<std::shared_ptr<T>>();
}

template<class T, class... _Types>
std::shared_ptr<T> Object::Instantiate(_Types &&... _Args) {
  auto obj = std::make_shared<T>(_Args...);
  throw NotImplementedException();
  return std::shared_ptr<T>();
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
