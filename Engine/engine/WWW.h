#pragma once
#ifndef EMSCRIPTEN
#include <curl/curl.h>
#endif
#include <string>
#include <vector>

class WWW {
public:
  WWW(std::string url);

  CURLcode fetch();

  void fetchAsync();

//  assetBundle	Streams an AssetBundle that can contain any kind of asset from the project folder.
//  bytes	Returns the contents of the fetched web page as a byte array (Read Only).
//  bytesDownloaded	The number of bytes downloaded by this WWW query (read only).
  /// @brief Returns an error message if there was an error during the download (Read Only).
  std::string Error();

  ///@brief  Is the download already finished? (Read Only)
  bool IsDone();
//  progress	How far has the download progressed (Read Only).
//  responseHeaders	Dictionary of headers returned by the request.
  /// @brief 	Returns the contents of the fetched web page as a string (Read Only).
  std::string Text();
//  texture	Returns a Texture2D generated from the downloaded data (Read Only).
//  textureNonReadable	Returns a non-readable Texture2D generated from the downloaded data (Read Only).
//  threadPriority	Obsolete, has no effect.
//  uploadProgress	How far has the upload progressed (Read Only).
//  url	The URL of this WWW request (Read Only).

//  Dispose	Disposes of an existing WWW object.
//  GetAudioClip	Returns an AudioClip generated from the downloaded data (Read Only).
//  GetAudioClipCompressed	Returns an AudioClip generated from the downloaded data that is compressed in memory (Read Only).
//  GetMovieTexture	Returns a MovieTexture generated from the downloaded data (Read Only).
//  LoadImageIntoTexture	Replaces the contents of an existing Texture2D with an image from the downloaded data.


//  EscapeURL	Escapes characters in a string to ensure they are URL-friendly.
//  LoadFromCacheOrDownload	Loads an AssetBundle with the specified version number from the cache. If the AssetBundle is not currently cached, it will automatically be downloaded and stored in the cache for future retrieval from local storage.
//  UnEscapeURL	Converts URL-friendly escape sequences back to normal text.


//  keepWaiting	Indicates if coroutine should be kept suspended.
private:
  std::string url;
  bool isDone = false;
  std::string error;
  std::vector<char> data;


};
