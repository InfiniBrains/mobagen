#pragma once

#include <memory>

#include "Input.h"
#include "Shader.h"
#include "Entity.h"
#include "Transform.h"
#include <imgui.h>
#include "Object.h"

class Engine;

enum PropertyType {
  FLOAT,
  FLOAT3,
  BOOLEAN,
  ANGLE,
  COLOR
};

struct Property {
  PropertyType type;
  void *p;
  float min;
  float max;
};

class Component
{
public:
  Component();
  ~Component(void) {};

  virtual void updateInput(Input *input, double delta) {};
  virtual void update(double delta) {};
  virtual void render(Shader *shader) {};
  virtual void registerWithEngine(Engine *engine) {};
  virtual void deregisterFromEngine(Engine *engine) {};
  virtual void onGUI(ImGuiContext *context) {};

  virtual const char *getType(void) = 0;

  void setProperty(const char *name, PropertyType type, void *p, float min, float max);
  void setProperty(const char *name, PropertyType type, void *p);

  void setParent(Entity *parentEntity);
  Entity *getParent(void) const;

  Transform* getTransform(void) const;

  std::map<const char *, Property> m_properties;

  Engine * getEngine();
  double getDeltaTime();
protected:
  Entity *m_parentEntity;


//  gameObject	The game object this component is attached to. A component is always attached to a game object.
//  tag	The tag of this game object.
//  transform	The Transform attached to this GameObject.

//  public methods
//  BroadcastMessage	Calls the method named methodName on every MonoBehaviour in this game object or any of its children.
//  CompareTag	Is this game object tagged with tag ?
//  GetComponent	Returns the component of Type type if the game object has one attached, null if it doesn't.
//  GetComponentInChildren	Returns the component of Type type in the GameObject or any of its children using depth first search.
//  GetComponentInParent	Returns the component of Type type in the GameObject or any of its parents.
//  GetComponents	Returns all components of Type type in the GameObject.
//  GetComponentsInChildren	Returns all components of Type type in the GameObject or any of its children.
//  GetComponentsInParent	Returns all components of Type type in the GameObject or any of its parents.
//  SendMessage	Calls the method named methodName on every MonoBehaviour in this game object.
//  SendMessageUpwards	Calls the method named methodName on every MonoBehaviour in this game object and on every ancestor of the behaviour.

};
