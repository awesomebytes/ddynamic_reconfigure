#include <ros/ros.h>
#include <gtest/gtest.h>
#include <ddynamic_reconfigure/param/dd_double_param.h>

namespace ddr {

    /**
     * @brief preliminary test which makes sure we can use the object.
     */
    TEST(DDDoubleTest, constructorTest) { // NOLINT(cert-err58-cpp,modernize-use-equals-delete)
        DDDouble param1("param1",0,0.5);
        DDDouble param2("",0,1,10);
        DDDouble param3("\000",0, -0, -3.4e100, 43.5e20); // NOLINT(bugprone-string-literal-with-embedded-nul)
    }

    /**
     * @brief a test making sure we can handle all API for handling the values of the param
     */
    TEST(DDDoubleTest, valueTest) { // NOLINT(cert-err58-cpp,modernize-use-equals-delete)
        DDDouble param("dd_param",0,1);
        // we won't do any tests on getLevel or getName, as those are implicit.
        Value v(1.0);
        ASSERT_TRUE(param.sameType(v));
        ASSERT_TRUE(param.sameValue(v));

        v = Value(1);
        ASSERT_FALSE(param.sameType(v));
        ASSERT_TRUE(param.sameValue(v));

        v = Value(2.0);
        ASSERT_TRUE(param.sameType(v));
        ASSERT_FALSE(param.sameValue(v));

        v = Value(2);
        ASSERT_FALSE(param.sameType(v));
        ASSERT_FALSE(param.sameValue(v));

        param.setValue(v);
        v = Value(3);
        ASSERT_FALSE(param.sameValue(v)); // makes sure anti-aliasing happens

        ASSERT_TRUE(param.getValue().getType() == "double");
        ASSERT_TRUE(param.sameValue(Value(2)));
    }
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    srand((unsigned int)random());

    return RUN_ALL_TESTS();
}