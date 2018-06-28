#include "WebRequest.hpp"

WebRequest::WebRequest() {
#ifndef EMSCRIPTEN

#else
#endif
}

void WebRequest::AddHeader(const std::string &key, const std::string &value)
{
#ifndef EMSCRIPTEN
  m_header[key] = value;
#else
#endif
}

void WebRequest::SetAuth(const std::string &username, const std::string &password)
{
#ifndef EMSCRIPTEN
  m_session.SetAuth(cpr::Authentication(username,password));
#else
#endif
}

void WebRequest::SetUrl(const std::string &url)
{
#ifndef EMSCRIPTEN
  m_session.SetUrl(url);
#else
#endif
}

void WebRequest::SetBody(const std::string& body) {
#ifndef EMSCRIPTEN
  m_session.SetBody(cpr::Body(body));
#else
#endif
}

void WebRequest::AddParameter(const std::string& key, const std::string& value) {
#ifndef EMSCRIPTEN
  m_parameters.AddParameter(cpr::Parameter(key,value));
#else
#endif
}

void WebRequest::AddMultiPart(const std::string &name, const std::string &value, const std::string &content_type)
{
#ifndef EMSCRIPTEN
  m_multipart.parts.emplace_back(cpr::Part(name,value,content_type));
#else
#endif
}

void WebRequest::AddMultiPart(const std::string &name, const std::int32_t &value, const std::string &content_type)
{
#ifndef EMSCRIPTEN
  m_multipart.parts.emplace_back(cpr::Part(name,value,content_type));
#else
#endif
}

void WebRequest::AddMultiPart(const std::string &name, const std::string &filename, const std::string& data, const std::string &content_type) {
#ifndef EMSCRIPTEN
  m_multipart.parts.emplace_back(cpr::Part(name, cpr::Buffer(data.begin(),data.end(),filename), content_type));
#else
#endif
}

void WebRequest::SetCookies(const std::string &key, const std::string &value) {
#ifndef EMSCRIPTEN
  m_cookies[key] = value;
#else
#endif
}

void WebRequest::SetDigest(const std::string& username, const std::string& password) {
#ifndef EMSCRIPTEN
  m_session.SetDigest(cpr::Digest(username,password));
#else
#endif
}

void WebRequest::AddPayload(const std::string &key, const std::string& value) {
#ifndef EMSCRIPTEN
  m_payload.AddPair(cpr::Pair(key,value));
#else
#endif
}

WebResponse WebRequest::Post() {
#ifndef EMSCRIPTEN
  if(m_cookies.GetEncoded().length()!=0)
    m_session.SetCookies(m_cookies);

  if(!m_header.empty())
    m_session.SetHeader(m_header);

  if(!m_parameters.content.empty())
    m_session.SetParameters(m_parameters);

  if(!m_payload.content.empty())
    m_session.SetPayload(m_payload);

  if(m_multipart.parts.size()!=0)
    m_session.SetMultipart(m_multipart);


  // response
  auto resp = m_session.Post();
  //for (auto &it : resp.header) m_response.header[it.first] = it.second;
  //for (auto &it : resp.cookies) m_response.cookies[it.first] = it.second;
  m_response.elapsed = resp.elapsed;
  m_response.error = (WebErrorCode)(int)resp.error.code;
  m_response.status_code = resp.status_code;
  m_response.text = resp.text;
  m_response.url = resp.url;
  return m_response;
#else
  return WebResponse();
#endif
}




