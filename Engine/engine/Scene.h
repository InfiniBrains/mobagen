//
// Created by alexandre on 21/03/18.
//
#pragma once

#include <string>
#include "GameObject.h"

class Scene
{
public:
//  buildIndex	Returns the index of the scene in the Build Settings. Always returns -1 if the scene was loaded through an AssetBundle.
//  isDirty	Returns true if the scene is modifed.
//  isLoaded	Returns true if the scene is loaded.

  /// @brief Returns the name of the scene.
  std::string name;

  //  path	Returns the relative path of the scene. Like: "Assets/MyScenes/MyScene.unity".

  /// @brief The number of root transforms of this scene.
  int rootCount();

  /// @brief Returns all the root game objects in the scene.
  std::vector<std::shared_ptr<GameObject>>* GetRootGameObjects();

  /// @brief Whether this is a valid scene. A scene may be invalid if, for example, you tried to open a scene that does not exist. In this case, the scene returned from EditorSceneManager.OpenScene would return False for IsValid.
  bool IsValid();

private:
  std::vector<std::shared_ptr<GameObject>> rootGameObjects;
};
