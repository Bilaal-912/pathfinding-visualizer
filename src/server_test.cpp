#include "httplib.h"
#include <iostream>
using namespace std;

int main() {
    httplib::Server svr;

    svr.Get("/ping", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("pong", "text/plain");
    });

    cout << "Server starting on http://localhost:8080" << endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}