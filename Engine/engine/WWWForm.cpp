#include <sstream>
#include "WWWForm.h"
#include "Random.h"

WWWForm::WWWForm() {
  formData.clear();
  fieldNames.clear();
  fileNames.clear();
  types.clear();
  boundary.clear();

  for (int index = 0; index < 40; ++index)
  {
    int num = Random::Range(48, 110);
    if (num > 57)
      num += 7;
    if (num > 90)
      num += 6;
    boundary += (char) num;
  }
  boundary += " ";
}

void WWWForm::AddField(std::string fieldName, std::string value) {
  fieldNames.push_back(fieldName);
  fileNames.emplace_back(nullptr);
  // todo: deal with another encodings
  formData.emplace_back(value.begin(),value.end());
  types.emplace_back("text/plain; charset=\"UTF-8\"");
}

void WWWForm::AddBinaryData(std::string fieldName, std::vector<char> contents, std::string fileName, std::string mimeType) {
  containsFiles = true;
  bool flag = contents.size() > 8 && (int) contents[0] == 137 && ((int) contents[1] == 80 && (int) contents[2] == 78) && ((int) contents[3] == 71 && (int) contents[4] == 13 && ((int) contents[5] == 10 && (int) contents[6] == 26)) && (int) contents[7] == 10;
  if (fileName.empty())
    fileName = fieldName + (!flag ? ".dat" : ".png");
  if (mimeType.empty())
    mimeType = !flag ? "application/octet-stream" : "image/png";
  fieldNames.push_back(fieldName);
  fileNames.push_back(fileName);
  formData.push_back(contents);
  types.push_back(mimeType);
}

std::map<std::string, std::string>* WWWForm::headers()
{
  m_headers["Content-Type"] = !containsFiles ? "application/x-www-form-urlencoded" : "multipart/form-data; boundary=\"" + boundary + "\"";
  return &m_headers;
}

std::vector<char> WWWForm::data() {
  std::stringstream data;

  if (containsFiles)
  {
    std::string bytes1 = "--";
    std::string bytes2 = "\r\n";
    std::string bytes3 = "Content-Type: ";
    std::string bytes4 = "Content-disposition: form-data; name=\"";
    std::string bytes5 = "\"";
    std::string bytes6 = "; filename=\"";

    for (int index = 0; index < formData.size(); ++index)
    {
      data << bytes2;
      data << bytes1;
      data << boundary;
      data << bytes2;
      data << bytes3;
      data << types[index];
      data << bytes2;
      data << bytes4;
      std::string headerName = "utf-8";
      data << "=?" << headerName << "?Q?" << fieldNames[index] << "?=";
      data << bytes5;
      if (!fileNames[index].empty())
      {
        data << bytes6;
        data << "=?" << headerName << "?Q?" << fileNames[index] << "?=";
        data << bytes5;
      }
      data << bytes2;
      data << bytes2;
      data.write(formData[index].data(), formData[index].size());
    }
    data << bytes2;
    data << bytes1;
    data << boundary;
    data << bytes1;
    data << bytes2;

    data.seekg(0, data.end);
    auto length = data.tellg();
    data.seekg (0, data.beg);
    char buff[(int)length];
    data.read(buff,length);
    return std::vector<char>(buff, buff + length);
  }
  else
  {
    std::string bytes1 = "&";
    std::string bytes2 = "=";

    for (int index = 0; index < formData.size(); ++index) {
      if (index > 0)
        data << bytes1;
      data << fieldNames[index];
      data << bytes2;
      data.write(formData[index].data(),formData[index].size());
    }

    data.seekg(0, data.end);
    auto length = data.tellg();
    data.seekg (0, data.beg);
    char buff[(int)length];
    data.read(buff,length);
    return std::vector<char>(buff, buff + length);
  }
}






