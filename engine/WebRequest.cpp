#include <utility>

#include "WebRequest.hpp"

namespace mobagen {
  const std::string WebRequest::kHttpVerbCREATE = "CREATE";
  const std::string WebRequest::kHttpVerbDELETE = "DELETE";
  const std::string WebRequest::kHttpVerbGET = "GET";
  const std::string WebRequest::kHttpVerbHEAD	= "HEAD";
  const std::string WebRequest::kHttpVerbPOST = "POST";
  const std::string WebRequest::kHttpVerbPUT = "PUT";

  WebRequest::WebRequest() {

    method = &kHttpVerbGET;
#ifdef APPLE
#ifdef USE_CURL
    easyhandle = nullptr;
    curl_global_init(CURL_GLOBAL_ALL);
#endif
#else
#endif
  }

  WebRequest::WebRequest(std::string url) {
    
    method = &kHttpVerbGET;
    this->url = std::move(url);
#ifdef APPLE
#ifdef USE_CURL
    curl_global_init(CURL_GLOBAL_ALL);
    easyhandle = nullptr;
#endif
#else
#endif
  }

  WebRequest::~WebRequest() {
#ifdef APPLE
#ifdef USE_CURL
    if(easyhandle!=nullptr)
      curl_easy_cleanup(easyhandle);
    easyhandle = nullptr;
    curl_global_cleanup(); // TODO: inspect if this is necessary
#endif
#endif
  }

  std::shared_ptr<WebRequest> WebRequest::Get(std::string url) {
    std::shared_ptr<WebRequest> req = std::make_shared<WebRequest>();

    req->method = &kHttpVerbGET;
    req->url = std::move(url);
    return req;
  }

  std::string WebRequest::GetRequestHeader(std::string name) {
    return requestHeaders[name];
  }

  std::string WebRequest::GetResponseHeader(std::string name) {
    return responseHeaders[name];
  }

  std::map<std::string, std::string> WebRequest::GetResponseHeaders() {
    return responseHeaders;
  }

  void WebRequest::SetRequestHeader(std::string name, std::string value) {
    requestHeaders[name] = value;
  }

  void WebRequest::SendWebRequest() {
    // TODO: implement this
  }
}
