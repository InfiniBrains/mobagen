#pragma once

#include "../Component.h"
#include "../Mesh.h"
#include "../Material.h"

class MeshRenderer : public Component
{
public:
  MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
  virtual ~MeshRenderer(void);

  virtual void update(double delta);
  virtual void render(Shader *shader);

  void setMaterial(std::shared_ptr<Material> material);
  std::shared_ptr<Material> getMaterial();

  void setMesh(std::shared_ptr<Mesh> mesh);
  std::shared_ptr<Mesh> getMesh();

  inline virtual const char *getType(void) { return "MESH_RENDERER"; }

protected:
  std::shared_ptr<Mesh> m_mesh;
  std::shared_ptr<Material> m_material;
};
