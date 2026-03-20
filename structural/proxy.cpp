#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

using namespace std;

class VideoDownloader {
public:
    virtual ~VideoDownloader() = default;

    virtual string downloadVideo(const string& videoUrl) = 0;
};


class RealVideoDownloader : public VideoDownloader {
public:
    string downloadVideo(const string& videoUrl) override {
        cout << "Downloading video from URL: " << videoUrl << "\n";

        return "Video content from " + videoUrl;
    }
};


class CachedVideoDownloader : public VideoDownloader {
private:
    unique_ptr<RealVideoDownloader> realDownloader;

    unordered_map<string, string> cache;

public:
    CachedVideoDownloader() {
        realDownloader = make_unique<RealVideoDownloader>();
    }

    string downloadVideo(const string& videoUrl) override {
        if (cache.find(videoUrl) != cache.end()) {
            cout << "Returning cached video for: " << videoUrl << "\n";
            return cache[videoUrl];
        }

        cout << "Cache miss. Downloading...\n";
        string content = realDownloader->downloadVideo(videoUrl);

        cache[videoUrl] = content;
        return content;
    }
};

int main() {
    unique_ptr<VideoDownloader> downloader = make_unique<CachedVideoDownloader>();

    cout << "User 1 tries to download the video.\n";
    downloader->downloadVideo("https://video.com/proxy-pattern");

    cout << "\n";
    cout << "User 2 tries to download the same video again.\n";
    downloader->downloadVideo("https://video.com/proxy-pattern");

    return 0;
}