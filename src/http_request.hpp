#ifndef HTTP_REQUEST
#define HTTP_REQUEST

#include <iostream>
#include <utility>

#include <curl/curl.h>
#include <jsoncpp/json/json.h>

#include "date.hpp"

using namespace std; 

size_t writeFunction(void* ptr, size_t size, size_t nmemb, string* data);
pair<int, int> get_setting(const string& URL);
pair<int, Date> post_roi_image(const string& URL, const string& b64encoded);
Date post_image(const string& URL, const string& b64encode, const Date& originalDate, const int& cameraID, pair<int, int>& size);

#endif