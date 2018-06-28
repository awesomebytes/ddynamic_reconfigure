#include <ros/ros.h>
#include <gtest/gtest.h>
#include <ddynamic_reconfigure/param/dd_string_param.h>

namespace ddr {

    /**
     * @brief preliminary test which makes sure we can use the object.
     */
    TEST(DDStringTest, constructorTest) { // NOLINT(cert-err58-cpp,modernize-use-equals-delete)
        DDString param1("param1",0,"Hello World");
        DDString param2("",0,"");
        DDString param3("\000",0,"\000"); // NOLINT(bugprone-string-literal-with-embedded-nul)
    }

    /**
     * @brief a test making sure we can handle all API for handling the values of the param
     */
    TEST(DDStringTest, valueTest) { // NOLINT(cert-err58-cpp,modernize-use-equals-delete)
        DDString param("dd_param",0,"1");
        // we won't do any tests on getLevel or getName, as those are implicit.
        Value v(string("1"));
        ASSERT_TRUE(param.sameType(v));
        ASSERT_TRUE(param.sameValue(v));

        v = Value(1);
        ASSERT_FALSE(param.sameType(v));
        ASSERT_TRUE(param.sameValue(v));

        v = Value(string("2"));
        ASSERT_TRUE(param.sameType(v));
        ASSERT_FALSE(param.sameValue(v));

        v = Value(2);
        ASSERT_FALSE(param.sameType(v));
        ASSERT_FALSE(param.sameValue(v));

        param.setValue(v);
        v = Value(string("3"));
        ASSERT_FALSE(param.sameValue(v)); // makes sure anti-aliasing happens

        ASSERT_TRUE(param.getValue().getType() == "string");
        ASSERT_TRUE(param.sameValue(Value(string("2"))));
    }
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    srand((unsigned int)random());

    return RUN_ALL_TESTS();
}