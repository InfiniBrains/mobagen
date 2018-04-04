//
// Created by Alexandre Tolstenko Nogueira on 3/20/18.
//

#include "Object.h"
#include "Error.h"

uint64_t Object::GetInstanceID(){
  return _id;
}

bool Object::operator==(const Object &other)
{
  // todo: improve this operator with type check, and make it tolerant to any type of object
  return _id == other._id;
}

bool Object::operator!=(const Object &other)
{
  // todo: improve this operator with type check, and make it tolerant to any type of object
  return _id != other._id;
}

Object::Object() : _id(++_counter_) {}

Object::~Object() = default;

uint64_t Object::_counter_ = 0;
std::unordered_multimap<size_t, std::unique_ptr<Object>> Object::objects;