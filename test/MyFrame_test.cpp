#include <gtest/gtest.h>
#include "MyFrame.h"
#include "MyLog.h"
#include "MyApp.h"

TEST(MyFrame, mod_load)
{
    MyApp app;
    bool ret = app.CreateContext("../CXXService/", "libtest_service.so", nullptr);
    EXPECT_EQ(true, ret);
}
