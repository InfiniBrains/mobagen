#pragma once
#include "Entity.hpp"
#include <string>

#include <assimp/scene.h>

namespace mobagen {
  class MeshLoader {
  public:
    MeshLoader(const std::string file);

    ~MeshLoader(void);

    std::shared_ptr<Entity> getEntity(void) const;

  protected:
    void loadScene(const aiScene *scene);

    std::string m_fileName;

    std::shared_ptr<Entity> m_entity;
  };
}