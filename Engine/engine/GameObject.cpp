#include "GameObject.h"
#include "Error.h"
#include "GameComponent.h"
#include "Error.h"

GameObject::GameObject(std::string name) : Object() {
  this->name = std::move(name);
}

GameObject::~GameObject() = default;

template<class T, class... _Types>
void GameObject::AddComponent(_Types &&... _Args) {
  // todo: insert safety checks
  auto newcomp = new T(_Args...);
  GameComponent * gc = dynamic_cast<GameComponent*>(newcomp);
  if(gc == nullptr)
    throw GenericException("Type must be Component");

  gc->gameObject = this;

  m_components.push_back(gc);
}

void GameObject::BroadcastMessage(std::string methodName, void *parameter, SendMessageOptions options) {
  throw NotImplementedException(typeid(this).name());
}

void GameObject::BroadcastMessage(std::string methodName, SendMessageOptions options) {
  throw NotImplementedException(typeid(this).name());
}

template<typename T>
T* GameObject::GetComponent() {
  // todo: improve velocity
  for(auto c:m_components)
  {
    T * gc = dynamic_cast<T*>(c);
    if(gc != nullptr)
      return gc;
  }

  return nullptr;
}

template<typename T>
T *GameObject::GetComponentInChildren() {
  throw NotImplementedException("GameObject GetComponentInChildren");
}

template<typename T>
std::vector<T*> GameObject::GetComponents() {
  throw NotImplementedException("GameObject GetComponents");
}

template<typename T>
std::vector<T *> GameObject::GetComponentsInChildren() {
  throw NotImplementedException("GameObject GetComponents");
}

template<typename T>
std::vector<T *> GameObject::GetComponentsInParent () {
  throw NotImplementedException("GameObject GetComponentsInParent");
}


void GameObject::SendMessage(std::string methodName) {
  throw NotImplementedException("GameObject SendMessage");
}

void GameObject::SendMessage(std::string methodName, void *value) {
  throw NotImplementedException("GameObject SendMessage");
}

void GameObject::SendMessage(std::string methodName, void *value, SendMessageOptions options) {
  throw NotImplementedException("GameObject SendMessage");
}

void GameObject::SendMessage(std::string methodName, SendMessageOptions options) {
  throw NotImplementedException("GameObject SendMessage");
}

void GameObject::SendMessageUpwards(std::string methodName, SendMessageOptions options) {
  throw NotImplementedException("GameObject SendMessageUpwards");
}

void GameObject::SendMessageUpwards(std::string methodName, void *value, SendMessageOptions options) {
  throw NotImplementedException("GameObject SendMessageUpwards");
}

void GameObject::SetActive(bool value) {
  throw NotImplementedException("GameObject SetActive");
}

GameObject* GameObject::CreatePrimitive(PrimitiveType type) {
  throw NotImplementedException("GameObject CreatePrimitive");
}

GameObject* GameObject::Find(std::string name) {
  throw NotImplementedException("GameObject Find");
}

std::vector<GameObject *> GameObject::FindGameObjectsWithTag(std::string tag) {
  throw NotImplementedException("GameObject FindGameObjectsWithTag");
}

GameObject *GameObject::FindWithTag(std::string tag) {
  throw NotImplementedException("GameObject FindWithTag");
}

template<typename T>
T *GameObject::GetComponentInParent() {
  throw NotImplementedException("GameObject GetComponentInParent");
}

std::vector<GameComponent*> GameObject::m_components;