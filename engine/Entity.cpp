#include "Entity.hpp"

#include "Component.hpp"

#include <algorithm>

namespace mobagen {
  std::map<std::string, std::vector<Entity *>> Entity::taggedEntities;

  Entity::Entity(const std::string &tag) {
    Entity::setTag(this, tag);

    m_tag = tag;
    parentEntity = nullptr;
  }

  Entity::Entity(void) {
    parentEntity = nullptr;
  }

  Entity::~Entity(void) {
    if (!m_tag.empty()) {
      auto taggedEntitiesVec = &Entity::taggedEntities[m_tag];
      taggedEntitiesVec->erase(std::remove(taggedEntitiesVec->begin(), taggedEntitiesVec->end(), this),
                               taggedEntitiesVec->end());
    }
  }

  void Entity::setTag(Entity *entity, const std::string &tag) {
    Entity::taggedEntities[tag].push_back(entity);
  }

  std::vector<Entity *> Entity::findByTag(const std::string &tag) {
    return Entity::taggedEntities[tag];
  }

  void Entity::addChild(std::shared_ptr<Entity> child) {
    child->parentEntity = this;
    children.push_back(child);

    // FIXME: IF MOVING ENTITY TO ANOTHER ENTITY THIS WILL BE AN ISSUE AS WE WILL REREGISTER
    if (m_engine) {
      child->registerWithEngineAll(m_engine);
    }
  }

  void Entity::updateAll(Input *input, std::chrono::microseconds delta) {
    if (parentEntity == nullptr) {
      worldMatrix = transform.getTransformMatrix();
    } else {
      worldMatrix = parentEntity->worldMatrix * transform.getTransformMatrix();
    }

    for (auto component : components) {
      component->update(input, delta);
    }

    for (auto child : children) {
      child->updateAll(input, delta);
    }
  }

  void Entity::renderAll(Shader *shader) const {
    for (auto component : components) {
      component->render(shader);
    }

    for (auto child : children) {
      child->renderAll(shader);
    }
  }

  void Entity::registerWithEngineAll(Engine *engine) {
    m_engine = engine;

    for (auto component : components) {
      component->registerWithEngine(engine);
    }

    for (auto child : children) {
      child->registerWithEngineAll(engine);
    }
  }

  void Entity::deregisterFromEngineAll(void) {
    for (auto component : components) {
      component->deregisterFromEngine(m_engine);
    }

    for (auto child : children) {
      child->deregisterFromEngineAll();
    }

    m_engine = nullptr;
  }

  Entity *Entity::getParent() {
    return parentEntity;
  }

  Transform &Entity::getTransform(void) {
    return transform;
  }

  std::vector<std::shared_ptr<Entity>> Entity::getChildren(void) {
    return children;
  }

  std::vector<std::shared_ptr<Component>> Entity::getComponents(void) {
    return components;
  }

  glm::mat4 &Entity::getWorldMatrix(void) {
    return worldMatrix;
  }

  glm::vec3 Entity::getPosition(void) {
    if (parentEntity == nullptr) {
      return transform.getPosition();
    } else {
      return (parentEntity->worldMatrix * glm::vec4(transform.getPosition(), 1)).xyz();
    }
  }

  glm::vec4 Entity::getDirection(void) {
    if (parentEntity == nullptr) {
      return transform.getDirection();
    } else {
      return glm::normalize(parentEntity->worldMatrix * transform.getDirection());
    }
  }

  Engine *Entity::getEngine() {
    return m_engine;
  }

  Engine *Entity::m_engine;
}