#pragma once

#ifndef EMSCRIPTEN
#include <cpr/cpr.h>
#include <string>
#endif

class WebRequest {

public:
  WebRequest();

private:
  std::string url;


};

