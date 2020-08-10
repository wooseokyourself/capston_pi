#include <iostream>
#include <curl/curl.h>
#include "json/json.h"
#include <string>

using namespace std;

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

int main(int argc, char** argv) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    auto curl = curl_easy_init();
    if (curl) {
        Json::Value jsonData;
        Json::Reader reader;
        curl_easy_setopt(curl, CURLOPT_URL, (URL + "/api/admin/setting").c_str());
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        std::string response_string;
        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        curl_easy_perform(curl);
        cout << response_string;
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        curl = NULL;

        reader.parse(response_string, jsonData);
        cout << "parsed" << endl;
        cout << " Width: " << jsonData["sizeW"].asInt();
        cout << " Height: " << jsonData["sizeH"].asInt();
    }
    return 0;
}


int main(void) {
    string b64encoded = "testencodingimage";
    curl_global_init(CURL_GLOBAL_DEFAULT);
    auto curl = curl_easy_init();
    if (!curl)
        return 0;

    Json::Value sendingData;
    Json::StyledWriter writer;
    sendingData["ip"] = "192.168.0.5";
    sendingData["image"] = b64encoded;
    string dataStr = writer.write(sendingData);

    struct curl_slist *headerlist nullptr
    headerlist = curl_slist_append(headerlist, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_URL, "/api/admin/roi_image");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dataStr.c_str());

    string response_string;
    string header_string;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    curl = NULL;
    cout << response_string << endl;;

    Json::Value jsonData;
    Json::Reader reader;
    reader.parse(chunk.memory, jsonData);
    int cameraID = jsonData["cameraID"].asInt();
    string originalDate = jsonData["originalDate"].asString();

    cout << endl;
    cout << "Parsed: " << endl;
    cout << " cameraID: " << cameraID << endl;
    cout << " originalDate: " << originalDate << endl;
    cout << endl;

    return 0;
}