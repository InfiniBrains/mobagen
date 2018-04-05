//
// Created by Alexandre Tolstenko Nogueira on 3/20/18.
//

#include "Object.h"
#include "Error.h"

uint64_t Object::GetInstanceID(){
  return _oid;
}

bool Object::operator==(const Object &other)
{
  // todo: improve this operator with type check, and make it tolerant to any type of object
  return _oid == other._oid;
}

bool Object::operator!=(const Object &other)
{
  // todo: improve this operator with type check, and make it tolerant to any type of object
  return _oid != other._oid;
}

Object::Object() : _oid(++_counter_) {}

Object::~Object() = default;

uint64_t Object::_counter_ = 0;

void Object::Destroy (std::shared_ptr<Object>) {
  throw NotImplementedException("Object Destroy");
}

void Object::DestroyImmediate (std::shared_ptr<Object>) {
  throw NotImplementedException("Object DestroyImmediate");
}

void Object::DontDestroyOnLoad (std::shared_ptr<Object>) {
  throw NotImplementedException("Object DontDestroyOnLoad");
}

template<class T>
std::shared_ptr<T> Object::FindObjectOfType () {
  throw NotImplementedException("Object FindObjectOfType");
  return std::shared_ptr<T>();
}

template<typename T>
std::vector<std::shared_ptr<T>> Object::FindObjectsOfType () {
  throw NotImplementedException("Object FindObjectsOfType");
  return nullptr;
}

template<class T, class... _Types>
std::shared_ptr<T> Object::Instantiate (_Types &&... _Args) {
  auto obj = std::make_shared<T>(_Args...);
  throw NotImplementedException("Object Instantiate");
}

std::unordered_multimap<std::type_index, std::shared_ptr<Object>> Object::objects;