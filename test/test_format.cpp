#include "format.hpp"
#include <gtest/gtest.h>

TEST(Format, FORMATSTRING)
{
    auto rst = format("%s,%s", "Hello", "World");
    ASSERT_EQ(rst, "Hello,World");
}
TEST(Format, FORMATINT){
    auto rst = format("%d.%d",1,23);
    ASSERT_EQ(rst,"1.23");
}