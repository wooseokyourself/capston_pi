#include "http_request.hpp"

pair<int, int> get_setting(const string& URL) {
    RestClient::Response r;
    r = RestClient::get(URL_GET_SETTING);
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

        return make_pair(captureResWidth, captureResHeight);
    }
    else {
        return make_pair(-1, -1);
    }
}

pair<int, Date> post_roi_image(const string& URL, const string& b64encoded) {
    Json::Value sendingData;
    Json::StyledWriter writer;
    sendingData["ip"] = "58.237.17.126";
    sendingData["image"] = b64encoded;
    string dataStr = writer.write(sendingData);

    RestClient::Response r;
    r = RestClient::post(URL, "application/json", dataStr);
    if (r.code == 201) {
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

        return make_pair(cameraID, Date(originalDate));
    }
    else {
        return make_pair(-1, Date(-1));
    }
}

Date post_image(const string& URL, const string& b64encode, const Date& originalDate, const int& cameraID) {
    Json::Value sendingData;
    Json::StyledWriter writer;
    sendingData["cameraID"] = cameraID;
    sendingData["originalDate"] = originalDate.form;
    sendingData["image"] = b64encode;
    string dataStr = writer.write(sendingDate);
    
    RestClient::Response r;
    r = RestClient::post(URL, "application/json", dataStr);

    if (r.code == 201) {
        Json::Value jsonData;
        Json::Reader reader;
        reader.parse(r.body, jsonData);

        string nextCaptureTime = jsonData["originalDate"].asString();

        cout << endl;
        cout << "Parsed: " << endl;
        cout << " originalDate: " << originalDate << endl;
        cout << endl;

        return Date(nextCaptureTime);
    }
    else {
        return Date(-1);
    }
}