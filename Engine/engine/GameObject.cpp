#include "GameObject.h"
#include "Component.h"
#include "Error.h"
GameObject::GameObject(std::string name) : Object() {
  this->name = name;
}

GameObject::~GameObject() {

}

template<class T, class... _Types>
void GameObject::AddComponent(_Types &&... _Args) {
  auto component = std::make_shared<T>(_Args...);
  component->setParent(this);
  throw NotImplementedException("GameObject AddComponent");
//  componentsByTypeid[typeid(T)].push_back(std::dynamic_pointer_cast<Component>(component));
//  components.push_back(component);
}

template<class T>
std::shared_ptr<T> GameObject::GetComponent() {
  throw NotImplementedException("GameObject GetComponent");
  return std::shared_ptr<T>();
}
