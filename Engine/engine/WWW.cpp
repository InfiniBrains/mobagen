#include "WWW.h"
#ifndef EMSCRIPTEN
#include <curl/curl.h>
#endif
#include <sstream>

WWW::WWW(std::string url) {
  this->url = url;
}

WWW::WWW(std::string url, WWWForm *form) {
  this->url = url;
  this->form = form;
}

size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata) {
  auto data = (std::vector<char> *)userdata;
  size_t count = size * nmemb;

  data->insert(data->end(), ptr, ptr + count);
  return static_cast<int>(count);
}

int WWW::fetch() {

#ifndef EMSCRIPTEN
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

    if(form!= nullptr) {
      struct curl_slist *chunk = nullptr;

      for(auto it : *(form->headers()))
      {
        std::string entry = it.first + ": " + it.second;
        chunk = curl_slist_append(chunk, entry.c_str());
      }

      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

      auto x = form->data();

      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, &x[0]);
    }

    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
      error = std::string(curl_easy_strerror(res));

    curl_easy_cleanup(curl);
    curl = nullptr;

    isDone = true;
    return res;
  } else
    return CURLE_FAILED_INIT;
#else

#endif
}

std::string WWW::Error() {
  return error;
}

std::string WWW::Text() {
  return std::string (data.begin(),data.end());
}

std::string WWW::Url() {
  return url;
}

bool WWW::IsDone() {
  return isDone;
}





//curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/repos/whoshuu/cpr/contributors?anon=true&key=value");
//curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
//curl_easy_setopt(curl, CURLOPT_USERPWD, "user:pass");
//curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
//curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
//curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
//
//std::string response_string;
//std::string header_string;
//curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
//curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
//curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
//
//char* url;
//long response_code;
//double elapsed;
//curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
//curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
//curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
//
//curl_easy_perform(curl);
//curl_easy_cleanup(curl);
//curl = NULL;


/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
/* <DESC>
 * Shows how the write callback function can be used to download data into a
 * chunk of memory instead of storing it in a file.
 * </DESC>
 */
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#include <curl/curl.h>
//
//struct MemoryStruct {
//  char *memory;
//  size_t size;
//};
//
//static size_t
//WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
//{
//  size_t realsize = size * nmemb;
//  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
//
//  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
//  if(mem->memory == NULL) {
//    /* out of memory! */
//    printf("not enough memory (realloc returned NULL)\n");
//    return 0;
//  }
//
//  memcpy(&(mem->memory[mem->size]), contents, realsize);
//  mem->size += realsize;
//  mem->memory[mem->size] = 0;
//
//  return realsize;
//}
//
//int main(void)
//{
//  CURL *curl_handle;
//  CURLcode res;
//
//  struct MemoryStruct chunk;
//
//  chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
//  chunk.size = 0;    /* no data at this point */
//
//  curl_global_init(CURL_GLOBAL_ALL);
//
//  /* init the curl session */
//  curl_handle = curl_easy_init();
//
//  /* specify URL to get */
//  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://www.example.com/");
//
//  /* send all data to this function  */
//  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
//
//  /* we pass our 'chunk' struct to the callback function */
//  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
//
//  /* some servers don't like requests that are made without a user-agent
//     field, so we provide one */
//  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
//
//  /* get it! */
//  res = curl_easy_perform(curl_handle);
//
//  /* check for errors */
//  if(res != CURLE_OK) {
//    fprintf(stderr, "curl_easy_perform() failed: %s\n",
//            curl_easy_strerror(res));
//  }
//  else {
//    /*
//     * Now, our chunk.memory points to a memory block that is chunk.size
//     * bytes big and contains the remote file.
//     *
//     * Do something nice with it!
//     */
//
//    printf("%lu bytes retrieved\n", chunk.size);
//  }
//
//  /* cleanup curl stuff */
//  curl_easy_cleanup(curl_handle);
//
//  free(chunk.memory);
//
//  /* we're done with libcurl, so clean it up */
//  curl_global_cleanup();
//
//  return 0;
//}