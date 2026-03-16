#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct EmailStyle {
    string font;
    int fontSize;

    EmailStyle(const string& f, int s) : font(f), fontSize(s) {}
};

class EmailTemplate {
public:
    virtual ~EmailTemplate() = default;

    virtual unique_ptr<EmailTemplate> clone() const = 0;

    virtual void setContent(const string& content) = 0;
    virtual void send(const string& to) const = 0;
};

class WelcomeEmail : public EmailTemplate {
private:
    string subject;
    string content;

    vector<string> templateTokens;

    shared_ptr<EmailStyle> style;

public:
    WelcomeEmail() {
        subject = "Welcome to TUF+";

        content = "Hi there! Thanks for joining us.";

        templateTokens = {"{name}", "{plan}", "{cta_link}"};

        style = make_shared<EmailStyle>("Inter", 14);
    }

    WelcomeEmail(const WelcomeEmail& other) {
        subject = other.subject;
        content = other.content;

        templateTokens = other.templateTokens;

        style = make_shared<EmailStyle>(*other.style);
    }

    unique_ptr<EmailTemplate> clone() const override {
        return make_unique<WelcomeEmail>(*this);
    }

    void setContent(const string& newContent) override {
        content = newContent;
    }

    void send(const string& to) const override {
        cout << "Sending to " << to << ": [" << subject << "] " << content << "\n";
        cout << "Style: font=" << style->font << ", size=" << style->fontSize << "\n";
    }
};

class EmailTemplateRegistry {
private:
    unordered_map<string, unique_ptr<EmailTemplate>> templates;

public:
    void registerTemplate(const string& type, unique_ptr<EmailTemplate> prototype) {
        templates[type] = move(prototype);
    }

    unique_ptr<EmailTemplate> getTemplate(const string& type) const {
        auto it = templates.find(type);

        if (it == templates.end()) {
            return nullptr;
        }

        return it->second->clone();
    }
};

int main() {
    EmailTemplateRegistry registry;

    registry.registerTemplate("welcome", make_unique<WelcomeEmail>());

    auto email1 = registry.getTemplate("welcome");
    if (email1) {
        email1->setContent("Hi Alice, welcome to TUF Premium!");
        email1->send("alice@example.com");
    }

    cout << "---\n";

    auto email2 = registry.getTemplate("welcome");
    if (email2) {
        email2->setContent("Hi Bob, thanks for joining!");
        email2->send("bob@example.com");
    }

    return 0;
}