/*
It is a stuructural design pattern that decomples an abstraction from its implementation
so that they can vary independently
*/
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class VideoQuality {
public:
    virtual ~VideoQuality() = default;

    virtual void load(const string& title) = 0;
};

class SDQuality : public VideoQuality {
public:
    void load(const string& title) override {
        cout << "Streaming " << title << " in SD Quality\n";
    }
};

class HDQuality : public VideoQuality {
public:
    void load(const string& title) override {
        cout << "Streaming " << title << " in HD Quality\n";
    }
};

class UltraHDQuality : public VideoQuality {
public:
    void load(const string& title) override {
        cout << "Streaming " << title << " in 4K Ultra HD Quality\n";
    }
};

class VideoPlayer {
protected:
    shared_ptr<VideoQuality> quality;

public:
    explicit VideoPlayer(shared_ptr<VideoQuality> q) : quality(std::move(q)) {}

    virtual ~VideoPlayer() = default;

    virtual void play(const string& title) = 0;
};

class WebPlayer : public VideoPlayer {
public:
    explicit WebPlayer(shared_ptr<VideoQuality> q) : VideoPlayer(std::move(q)) {}

    void play(const string& title) override {
        cout << "Web Platform:\n";
        quality->load(title);
    }
};

class MobilePlayer : public VideoPlayer {
public:
    explicit MobilePlayer(shared_ptr<VideoQuality> q) : VideoPlayer(std::move(q)) {}

    void play(const string& title) override {
        cout << "Mobile Platform:\n";
        quality->load(title);
    }
};

int main() {
    WebPlayer player1(make_shared<HDQuality>());
    player1.play("Interstellar");

    cout << "\n";

    MobilePlayer player2(make_shared<UltraHDQuality>());
    player2.play("Inception");

    cout << "\n";

    WebPlayer player3(make_shared<SDQuality>());
    player3.play("The Dark Knight");

    return 0;
}