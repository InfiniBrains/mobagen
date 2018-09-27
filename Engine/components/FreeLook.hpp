#pragma once
#include "Component.hpp"

namespace mobagen {
  class FreeLook : public Component {
  public:
    FreeLook(float speed = 0.001f);

    ~FreeLook(void);

    virtual void updateInput(Input *input, double delta);

    inline virtual const char *getType(void) { return "FREE_LOOK"; }

  private:
    float m_speed;
  };
}