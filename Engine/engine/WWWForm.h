#pragma once

#include <vector>
#include <string>
#include <map>


class WWWForm {
public:
  WWWForm();

//  data	(Read Only) The raw data to pass as the POST request body when sending the form.
//  headers	(Read Only) Returns the correct request headers for posting the form using the WWW class.

  /// @brief Add binary data to the form.
  void AddBinaryData(std::string fieldName, std::vector<char> contents, std::string fileName="", std::string mimeType="");
/// @brief Add a simple field to the form.
  void AddField(std::string fieldName, std::string value);

  // TODO: Support other Encodings
  /// @brief Add a simple field to the form.
  //public void AddField(string fieldName, string value, Encoding e);

  std::map<std::string,std::string>* headers();

  std::vector<char> data();

private:
  bool containsFiles = false;
  std::vector<std::vector<char>> formData;
  std::vector<std::string> fieldNames;
  std::vector<std::string> fileNames;
  std::vector<std::string> types;
  std::string boundary;

  std::map<std::string, std::string> m_headers;
};
