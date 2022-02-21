#include <gtest/gtest.h>
#include "loguru.hpp"

TEST(TESTSAMPLE, LOGFILE){
    loguru::add_file("app.log",loguru::Append,loguru::Verbosity_MAX);
}
TEST(TESTSAMPLE,LOGLEVEL){
    LOG_F(INFO,"INFO");
    LOG_F(WARNING,"WARNING");
    LOG_F(ERROR,"ERROR");
}