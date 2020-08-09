#ifndef HTTP_REQUEST
#include HTTP_REQUEST

#include <iostream>
#include <utility>

#include <restclient-cpp/restclient.h>
#include <json/json.h>

#include "date.hpp"

using namespace std; 

pair<int, int> get_setting(const string& URL);
pair<int, Date> post_roi_image(const string& URL, const string& b64encoded);
Date post_image(const string& URL, const string& b64encode, const Date& originalDate, const int& cameraID);

#endif