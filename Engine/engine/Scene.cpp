//
// Created by alexandre on 21/03/18.
//

#include "Scene.h"
#include "Error.h"

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
