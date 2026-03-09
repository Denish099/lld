#include <iostream>
using namespace std;

class JudgeAnalytics
{
private:
    static JudgeAnalytics instance; // eager loading
    int count = 10;
    int submit = 5;

    JudgeAnalytics() {}

    ~JudgeAnalytics() {
    }

public:
    // 3. Delete copy constructor and assignment operator to prevent cloning
    JudgeAnalytics(const JudgeAnalytics&) = delete;
    JudgeAnalytics& operator=(const JudgeAnalytics&) = delete;

    static JudgeAnalytics& getInstance()
    {
        // static JudgeAnalytics instance; lazy loading
        return instance;
    }

    int getCount()
    {
        return count;
    }

    int getSubmit()
    {
        return submit;
    }
};

int main()
{
    // Access it using a reference
    JudgeAnalytics& judgeAnalytics = JudgeAnalytics::getInstance();

    cout << judgeAnalytics.getCount() << endl;
    cout << judgeAnalytics.getSubmit() << endl;

    return 0;
}