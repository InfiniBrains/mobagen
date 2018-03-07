#pragma once

#include <memory>

#include "Input.h"
#include "Shader.h"
#include "Entity.h"
#include "Transform.h"
#include <imgui.h>

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
  virtual ~Component(void) {};

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

  Transform& getTransform(void) const;

  std::map<const char *, Property> m_properties;

  Engine * getEngine();
  double getDeltaTime();
protected:
  Entity *m_parentEntity;
};
