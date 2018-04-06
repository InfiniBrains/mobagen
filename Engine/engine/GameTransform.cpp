#include "GameTransform.h"

void GameTransform::SetParent (GameTransform *parent) {
  if(m_parent != nullptr) {
    // todo: add to root
    //auto it = m_parent->m_children
  }
}

void GameTransform::DetachChildren () {
  m_children.clear();
}
