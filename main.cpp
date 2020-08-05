#include <opencv2/opencv.hpp>
#include <restclient-cpp/restclient.h>
#include <json/json.h>
#include <iostream>
#include <vector>

using namespace std; 
using namespace cv;

// g++ -I /usr/local/restclient-cpp/include -l restclient-cpp `pkg-config --cflags --libs jsoncpp` `pkg-config --cflags --libs opencv4` `pkg-config --cflags --libs libffi` -std=c++11 main.cpp -o main


static const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";


static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}

std::string base64_decode(std::string const& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}


// 2020.08.05 19:14:10
string getCurrTime () {
    time_t timeObj = time(NULL);
	struct  tm* tm = localtime(&timeObj);
    std::string currTime, temp;
    currTime += std::to_string (tm->tm_year+1900);
    currTime += ".";

    temp = std::to_string (tm->tm_mon+1);
    if (temp.length() == 1) temp = "0" + temp;
	currTime += temp;
    currTime += ".";

    temp = std::to_string (tm->tm_mday);
    if (temp.length() == 1) temp = "0" + temp;
    currTime += temp;
    currTime += " ";

	temp = std::to_string (tm->tm_hour);
    if (temp.length() == 1) temp = "0" + temp;
	currTime += temp;
    currTime += ":";

	temp = std::to_string (tm->tm_min);
    if (temp.length() == 1) temp = "0" + temp;
	currTime += temp;
    currTime += ":";

	temp = std::to_string (tm->tm_sec);
    if (temp.length() == 1) temp = "0" + temp;
	currTime += temp;

    return currTime;
}

int main(void) {
    // Json
    Json::StyledWriter writer;
    
    string imagePath;
    cout << "Image file: ";
    cin >> imagePath;

    // Image processing
    Mat img = imread(imagePath, IMREAD_COLOR);
    vector<uchar> buf;
    vector<int> params;
    params.push_back(IMWRITE_JPEG_QUALITY);
    params.push_back(95);
    imencode(".jpeg", img, buf);
    auto *enc_msg = reinterpret_cast<unsigned char*>(buf.data());
    std::string encoded = base64_encode(enc_msg, buf.size());

    int choice;
    while (true) {
        RestClient::Response r;
        cout << "1. GET Setting" << endl;
        cout << "2. POST Roi Image" << endl;
        cout << "3. (Not used) ROI Info" << endl;
        cout << "4. POST New Image" << endl;
        cout << ": ";
        cin >> choice;
        if (choice == 1) {
            r = RestClient::get("58.237.17.126:10051/api/admin/setting");
            if (r.code == 200) {
                // r.body 의 데이터들을 data에 파싱
                Json::Value jsonData;
                Json::Reader reader;
                reader.parse(r.body, jsonData);

                int captureResWidth = jsonData["sizeW"].asInt();
                int captureResHeight = jsonData["sizeH"].asInt();

                cout << endl;
                cout << "Parsed: " << endl;
                cout << " captureResWidth: " << captureResWidth << endl;
                cout << " captureResHeight: " << captureResHeight << endl;
                cout << endl;
            }
        }
        else if (choice == 2) {
            Json::Value dataFirst;
            dataFirst["ip"] = "58.237.17.126";
            dataFirst["image"] = encoded;

            string dataStr = writer.write(dataFirst);
            cout << "willSendData: \n" << dataStr << endl; 
            r = RestClient::post("58.237.17.126:10051/api/admin/roi-image", "application/json", dataStr);
            if (r.code == 201) {
                // r.body 의 데이터들을 data에 파싱
                Json::Value jsonData;
                Json::Reader reader;
                reader.parse(r.body, jsonData);

                int cameraID = jsonData["cameraID"].asInt();
                string originalDate = jsonData["originalDate"].asString();

                cout << endl;
                cout << "Parsed: " << endl;
                cout << " cameraID: " << cameraID << endl;
                cout << " originalDate: " << originalDate << endl;
                cout << endl;
            }
        }
        else if (choice == 3) {
            r = RestClient::get("58.237.17.126:10051/api/admin/roi-info");
            if (r.code == 200) {
                  // r.body 의 데이터들을 data에 파싱
                vector< vector<int> > data (2);
                Json::Value jsonData;
                Json::Reader reader;
                reader.parse(r.body, jsonData);
                Json::ValueIterator it = jsonData.begin(); // 배열을 순회하기위한 이터레이터

                int camID = 1;
                while(it != jsonData.end()) {
                    int camID = (*it)["id"].asInt();
                    data[camID-1].push_back( (*it)["leftX"].asInt() );
                    data[camID-1].push_back( (*it)["leftY"].asInt() );
                    data[camID-1].push_back( (*it)["rightX"].asInt() );
                    data[camID-1].push_back( (*it)["rightY"].asInt() );
                }

                cout << endl;
                cout << "Parsed: " << endl;
                for (int i=0; i<data.size(); i++) {
                    cout << " camID: " << i+1 << endl;
                    cout << "   ";
                    for (int j=0; j<data[i].size(); j++) {
                        cout << data[i][j] << ", ";
                    }
                    cout << endl;
                }
            }
        }
        else if (choice == 4) {
            Json::Value dataFirst;
            dataFirst["cameraID"] = 1;
            dataFirst["originalDate"] = getCurrTime();
            dataFirst["image"] = encoded;

            string dataStr = writer.write(dataFirst);
            cout << "willSendData: \n" << dataStr << endl; 
            r = RestClient::post("58.237.17.126:10051/api/basic/image-info", "application/json", dataStr);

            if (r.code == 201) {
                // r.body 의 데이터들을 data에 파싱
            }
        }
        else break;
        cout << "===============================" << endl;
        cout << "HTTP response code: " << r.code << endl;
        cout << "HTTP response headers: " << endl;
        for (const auto& x: r.headers) {
            cout << x.first << ": " << x.second << endl;
        }
        cout << "HTTP response body: " << r.body << endl;
        cout << "===============================" << endl;
        r.code = 0;
    }
} 