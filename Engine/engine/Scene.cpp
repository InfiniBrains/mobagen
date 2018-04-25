//
// Created by alexandre on 21/03/18.
//

#include "Scene.hpp"
#include "Error.hpp"

int Scene::rootCount () {
  throw NotImplementedException("SCENE rootCount");
  return 0;
}

std::vector<std::shared_ptr<GameObject>> *Scene::GetRootGameObjects () {
  return &rootGameObjects;
}

bool Scene::IsValid () {
  throw NotImplementedException("SCENE IsValid");
  return false;
}
