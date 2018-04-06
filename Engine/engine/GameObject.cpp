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
  auto component = new T(_Args...);
  GameComponent * go = dynamic_cast<GameComponent*>(component);
  if(go== nullptr)
    throw GenericException();

  //go->transform()
  throw NotImplementedException("GameObject AddComponent");
//  componentsByTypeid[typeid(T)].push_back(std::dynamic_pointer_cast<Component>(component));
//  components.push_back(component);
}

void GameObject::BroadcastMessage(std::string methodName, void *parameter, SendMessageOptions options) {
  throw NotImplementedException(typeid(this).name());
}

void GameObject::BroadcastMessage(std::string methodName, SendMessageOptions options) {
  throw NotImplementedException(typeid(this).name());
}

template<typename T>
T* GameObject::GetComponent() {
  throw NotImplementedException("GameObject GetComponent");
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

