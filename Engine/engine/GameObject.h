//
// Created by Alexandre Tolstenko Nogueira on 3/20/18.
//
#pragma once

#include "Object.h"
#include "Transform.h"

class GameObject : Object
{
  explicit GameObject(std::string name);
  ~GameObject();

  /// The name of the gameObject.
  std::string name;

  /// Is the GameObject active in the scene?
  bool activeInHierarchy;

//  activeSelf	The local active state of this GameObject. (Read Only)
//  isStatic	Editor only API that specifies if a game object is static.

  /// The layer the game object is in. A layer is in the range [0...31].
  int layer;

//  scene	Scene that the GameObject is part of.
//  tag	The tag of this game object.

  /// The Transform attached to this GameObject.
  Transform transform;

  /// @brief Adds a component class named className to the game object.
  template <class T, class... _Types>
  void AddComponent(_Types&&... _Args);
//  BroadcastMessage	Calls the method named methodName on every MonoBehaviour in this game object or any of its children.
//  CompareTag	Is this game object tagged with tag ?

  /// @brief Returns the component of Type type if the game object has one attached, null if it doesn't.
  template <class T>
  std::shared_ptr<T> GetComponent();
//  GetComponentInChildren	Returns the component of Type type in the GameObject or any of its children using depth first search.
//  GetComponentInParent	Returns the component of Type type in the GameObject or any of its parents.
//  GetComponents	Returns all components of Type type in the GameObject.
//  GetComponentsInChildren	Returns all components of Type type in the GameObject or any of its children.
//  GetComponentsInParent	Returns all components of Type type in the GameObject or any of its parents.
//  SendMessage	Calls the method named methodName on every MonoBehaviour in this game object.
//  SendMessageUpwards	Calls the method named methodName on every MonoBehaviour in this game object and on every ancestor of the behaviour.
//  SetActive	Activates/Deactivates the GameObject.


//  CreatePrimitive	Creates a game object with a primitive mesh renderer and appropriate collider.
//  Find	Finds a GameObject by name and returns it.
//  FindGameObjectsWithTag	Returns a list of active GameObjects tagged tag. Returns empty array if no GameObject was found.
//  FindWithTag	Returns one active GameObject tagged tag. Returns null if no GameObject was found.
};

