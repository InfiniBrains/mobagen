#include "Scene.hpp"
#include "Error.hpp"

int Scene::rootCount () {
  throw NotImplementedException("SCENE rootCount");
  return 0;
}

void Scene::GetRootGameObjects (std::vector<std::shared_ptr<GameObject>> * objs) {
  objs = &rootGameObjects;
}

bool Scene::IsValid () {
  throw NotImplementedException("SCENE IsValid");
  return false;
}
