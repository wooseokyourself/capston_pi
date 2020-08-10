#include "http_request.hpp"

size_t writeFunction(void* ptr, size_t size, size_t nmemb, string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

pair<int, int> get_setting(const string& URL) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    auto curl = curl_easy_init();
    if (!curl)
        return make_pair(-1, -1);
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

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
    reader.parse(response_string, jsonData);
    int width = jsonData["sizeW"].asInt();
    int height = jsonData["sizeH"].asInt();
    return pair<width, height>;
}

pair<int, Date> post_roi_image(const string& URL, const string& b64encoded) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    auto curl = curl_easy_init();
    if (!curl)
        return make_pair(-1, Date(-1));

    Json::Value sendingData;
    Json::StyledWriter writer;
    sendingData["ip"] = "192.168.0.5";
    sendingData["image"] = b64encoded;
    string dataStr = writer.write(sendingData);

    struct curl_slist *headerlist = nullptr;
    headerlist = curl_slist_append(headerlist, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
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
    reader.parse(response_string, jsonData);
    int cameraID = jsonData["cameraID"].asInt();
    string originalDate = jsonData["originalDate"].asString();

    cout << endl;
    cout << "Parsed: " << endl;
    cout << " cameraID: " << cameraID << endl;
    cout << " originalDate: " << originalDate << endl;
    cout << endl;

    return make_pair(cameraID, Date(originalDate));
}

Date post_image(const string& URL, const string& b64encode, const Date& originalDate, const int& cameraID) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    auto curl = curl_easy_init();
    if (!curl)
        return Date(-1);
    
    Json::Value sendingData;
    Json::StyledWriter writer;
    sendingData["cameraID"] = cameraID;
    sendingData["originalDate"] = originalDate.form;
    sendingData["image"] = b64encode;
    string dataStr = writer.write(sendingDate);

    struct curl_slist *headerlist = nullptr;
    headerlist = curl_slist_append(headerlist, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
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
    reader.parse(response_string, jsonData);
    string nextCaptureTime = jsonData["originalDate"].asString();
    return Date(nextCaptureTime);
}