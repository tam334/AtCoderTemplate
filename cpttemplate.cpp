#include <gtest/gtest.h>
#include "{@insert target_module}.h"
#include <string>
#include <vector>
#include <fstream>

struct ABCParams
{
public:
    int n;
    ABCParams(int n) : n(n)
    {
    }
};

class MyTest : public testing::TestWithParam<ABCParams>
{
};

TEST_P(MyTest, Sub)
{
    const ABCParams p = GetParam();
    std::vector<std::string> inputs;
    std::string output;
    std::ifstream ifile("testcase_{@insert target_module}.txt");
    int cnt = 0;
    std::string buf;
    while(std::getline(ifile, buf))
    {
        if(buf.length() >= 2 && buf.substr(0, 2) == "\\i")
        {
            cnt += 1;
            if(cnt > p.n)
            {
                break;
            }
        }
    }
    while(std::getline(ifile, buf))
    {
        if(buf.length() >= 2 && buf.substr(0, 2) == "\\o")
        {
            break;
        }
        else
        {
            inputs.push_back(buf);
        }
    }
    while(std::getline(ifile, buf))
    {
        if(buf.length() >= 2 && buf.substr(0, 2) == "\\i")
        {
            break;
        }
        else
        {
            output += buf + "\n";
        }
    }
    EXPECT_EQ(Impl_{@insert target_module}(inputs), output);
}

{@insert parameters}

