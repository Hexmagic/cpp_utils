#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class MyEnvironment:public testing::Environment{
    virtual void setUp(){
         std::cout<<"Environment Start"<<std::endl;
    }
    virtual void tearDown(){
        std::cout<<"Environment tear Down"<<std::endl;
    }
};

int main(int argc, char **argv)
{
    testing::AddGlobalTestEnvironment(new MyEnvironment );
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}