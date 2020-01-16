#include "web_server.h"
#include <fstream>

void video_handler(const Request & request, Response & response) {
    
    vector<char> bytes;
    response.write_status();
    response.enable_multipart();

    for(int x=0;x<133;++x) {
        int image_number = x%133;
        string image_path = "sample_images/video_left.avi"+to_fixed_width_string(image_number,5,'0')+".jpeg";
        ifstream f;
        f.open(image_path, ifstream::in | ios::binary | ios::ate);
        auto length = f.tellg();
        f.seekg(0);
        bytes.resize(length);
        f.read(&bytes[0],length);


        response.write_content("image/jpeg", &bytes[0], bytes.size());
        //string s = "here is some text";
        //response.write_content("text/plain", s.c_str(), s.size());

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    response.end();
}

void video_page(const Request & request, Response & response) {
    response.write_status();
    string body = "<html><h1>mjpeg-server</h1><image src='video_feed'></image></html>";
    response.write_content("text/html", body.c_str(), body.size());
}

int main(){
    //test_request();
    //return 0;
    try {
        WebServer server;
        server.add_handler("GET", "/", video_page);
        server.add_handler("GET", "/video_feed", video_handler);
        server.add_handler("GET", "/video", video_page);
        server.run(8080);
    } catch (string e) {
        cout << "Error caught in main: " << e << endl;
    }
}
