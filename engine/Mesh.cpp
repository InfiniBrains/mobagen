#include "Mesh.hpp"

#include <map>
namespace mobagen {
  std::map<std::string, std::weak_ptr<MeshData>> m_meshCache;

  Mesh::Mesh(std::string identifier, Vertex vertices[], int vertSize, unsigned int indices[], int indexSize) {
    auto it = m_meshCache.find(identifier);

    if (it == m_meshCache.end() || !(m_meshData = it->second.lock())) {
      m_meshData = std::make_shared<MeshData>(vertices, vertSize, indices, indexSize);
      m_meshCache[identifier] = m_meshData;
    }
  }

  void Mesh::reasign(std::string identifier, Vertex vertices[], int vertSize, unsigned int indices[],
                     int indexSize)
  {
    m_meshData = std::make_shared<MeshData>(vertices, vertSize, indices, indexSize);
  }

  Mesh::~Mesh(void) {
  }

  void Mesh::render(void) const {
    m_meshData->render();
  }
}