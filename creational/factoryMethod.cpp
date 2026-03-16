#include <iostream>
#include <string>
using namespace std;

class Logistics {
public:
    virtual void send() = 0;
    virtual ~Logistics() {}
};

class Road : public Logistics {
public:
    void send() override {
        cout << "Sending by road logic" << endl;
    }
};

class Air : public Logistics {
public:
    void send() override {
        cout << "Sending by air logic" << endl;
    }
};

class LogisticsService {
private:
    static LogisticsService* instance;

    LogisticsService() {}

public:

    LogisticsService(const LogisticsService&) = delete;
    LogisticsService& operator=(const LogisticsService&) = delete;

    static LogisticsService* getInstance() {
        if (instance == nullptr) {
            instance = new LogisticsService();
        }
        return instance;
    }

    void send(const string& mode) {
        if (mode == "Air") {
            Logistics* logistics = new Air();
            logistics->send();
            delete logistics;
        }
        else if (mode == "Road") {
            Logistics* logistics = new Road();
            logistics->send();
            delete logistics;
        }
    }
};

LogisticsService* LogisticsService::instance = nullptr;

int main() {

    LogisticsService* service = LogisticsService::getInstance();

    service->send("Air");
    service->send("Road");

    return 0;
}