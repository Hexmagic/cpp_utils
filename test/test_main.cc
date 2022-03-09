
#include <iostream>
#include <vector>
#include <string>
#include "gtest/gtest.h"
#include "loguru.hpp"
#include "csv.hpp"

using namespace std;

TEST(TESTSAMPLE, LOGFILE)
{
    loguru::add_file("app.log", loguru::Append, loguru::Verbosity_MAX);
}
TEST(TESTSAMPLE, LOGLEVEL)
{
    LOG_F(INFO, "LOGURU INFO Test");
    LOG_F(WARNING, "LOGURU WARNING");
    LOG_F(ERROR, "LOGURU ERROR");
}
TEST(TESTCSV, CSVWRITE)
{
    CSV c1("test.csv", "Name,Age");
    c1 << "Lee," << 12 << std::endl;
    c1.write("%s,%d\n", "Mix", 12);
    string name = "LiLei";
    c1.write("%s,%d\n", name.c_str(), 18);
}

class MyEnvironment : public testing::Environment
{
    virtual void setUp()
    {
        std::cout << "Environment Start" << std::endl;
    }
    virtual void tearDown()
    {
        std::cout << "Environment tear Down" << std::endl;
    }
};

int main(int argc, char **argv)
{
    testing::AddGlobalTestEnvironment(new MyEnvironment);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}