#pragma once

#include "EngineIOStream.hpp"

namespace mobagen {
  class Asset {
  public:
    Asset(const std::string &fileName);

    ~Asset(void);

    const char *read(void) const;

    EngineIOStream *getIOStream(void) const;

  private:
    char *m_buffer;
    EngineIOStream *m_ioStream;
    size_t m_fileSize;
  };
}