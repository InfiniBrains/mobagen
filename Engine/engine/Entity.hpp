#pragma once

#include <vector>
#include <map>
#include <typeindex>
#include <algorithm>
#include <memory>

#include "Transform.hpp"
#include "Shader.hpp"
#include "Input.hpp"

class Engine;

class Component;

class Entity
{
public:
  Entity(const std::string& tag);
  Entity(void);
  ~Entity(void);

  void addChild(std::shared_ptr<Entity> child);

  template <class T>
  inline void removeComponent(std::shared_ptr<T> component)
  {
    // todo: check if it will remove the component properly
    //component->deregisterFromEngine(m_engine);
    //component->setParent(nullptr);

//    auto f = std::find(componentsByTypeid[typeid(T)].begin(),componentsByTypeid[typeid(T)].end(), component);
//    if(f!=componentsByTypeid[typeid(T)].end())
//      componentsByTypeid[typeid(T)].erase(f);
//
//    auto d = std::find(components.begin(),components.end(), component);
//    if(d!=components.end())
//      components.erase(d);
  }


  template <class T>
  inline void addComponent(std::shared_ptr<T> component)
  {
    component->setParent(this);
    componentsByTypeid[typeid(T)].push_back(component);
    components.push_back(component);
  }

  template <class T, class... _Types>
  inline void addComponent(_Types&&... _Args)
  {
    auto component = std::make_shared<T>(_Args...);
    component->setParent(this);
    componentsByTypeid[typeid(T)].push_back(std::dynamic_pointer_cast<Component>(component));
    components.push_back(component);
  }

  void updateInputAll(Input *input, double delta);
  void updateAll(double delta);
  void renderAll(Shader *shader);
  void registerWithEngineAll(Engine *engine);
  void deregisterFromEngineAll(void);
  Entity* getParent();

  Transform* getTransform(void);

  std::vector<std::shared_ptr<Entity>> getChildren(void);
  std::vector<std::shared_ptr<Component>> getComponents(void);

  glm::mat4& getWorldMatrix(void);

  glm::vec4 getPosition(void);
  glm::vec4 getDirection(void);

  template <class T>
  inline std::vector<std::shared_ptr<T>> getComponentsByType(void)
  {
    auto i = componentsByTypeid.find(typeid(T));
    if (i == componentsByTypeid.end()) {
      return std::vector<std::shared_ptr<T>>();
    } else {
      auto vec = i->second;

      std::vector<std::shared_ptr<T>> target(vec.size());
      std::transform(vec.begin(), vec.end(), target.begin(), [](std::shared_ptr<Component> t) { return std::dynamic_pointer_cast<T>(t); });
      return target;
    }
  }

  template <class T>
  inline std::shared_ptr<T> getComponent(void)
  {
    auto i = componentsByTypeid.find(typeid(T));
    if (i == componentsByTypeid.end()) {
      return nullptr;
    } else {
      auto vec = i->second;
      if (vec.size() > 0) {
        return std::dynamic_pointer_cast<T>(vec[0]);
      } else {
        return nullptr;
      }
    }
  }

  static std::vector<Entity*> findByTag(const std::string& tag);

  Engine * getEngine();

private:
  std::unique_ptr<Transform> transform;

  Entity *parentEntity;

  std::vector<std::shared_ptr<Entity>> children;
  std::vector<std::shared_ptr<Component>> components;

  glm::mat4 worldMatrix;

  std::string m_tag;

  static Engine *m_engine;

  static void setTag(Entity *entity, const std::string& tag);

  static std::map<std::string, std::vector<Entity*> > taggedEntities;

  std::map<std::type_index, std::vector<std::shared_ptr<Component>> > componentsByTypeid;
};
