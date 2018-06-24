#include <ddynamic_reconfigure/ddynamic_reconfigure.h>
#include <gtest/gtest.h>
#include <dynamic_reconfigure/Reconfigure.h>
#include <ddynamic_reconfigure/param/dd_all_params.h>
#include <exception>

using namespace std;
namespace ddr {

    void basicCallback(const DDMap& map, int, bool *flag) {
        *flag = true;
    }

    /**
     * @brief preliminary test which makes sure we can use callbacks
     */
    TEST(DDynamicReconfigureTest, basicCallbackTest) { // NOLINT(cert-err58-cpp,modernize-use-equals-delete)
        ros::NodeHandle nh("~");
        DDynamicReconfigure dd(nh); // gets our main class running

        bool flag = false;
        DDFunc callback = bind(&basicCallback,_1,_2,&flag);
        dd.start(callback);

        ros::AsyncSpinner spinner(1);
        spinner.start();

        dynamic_reconfigure::Reconfigure srv;

        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_TRUE(flag);
    }

    void intCallback(const DDMap& map, int, int *flag) {
        EXPECT_EQ("int",map.find("int_param")->second->getValue().getType());
        *flag = map.find("int_param")->second->getValue().toInt();
    }

    TEST(DDynamicReconfigureTest, intTest) { // NOLINT(cert-err58-cpp,modernize-use-equals-delete)
        ros::NodeHandle nh("~");
        int flag = 0;
        DDFunc callback = bind(&intCallback,_1,_2,&flag);

        DDynamicReconfigure dd(nh);
        dd.add(new DDInt("int_param", 0, 0));
        dd.start(callback);

        ros::AsyncSpinner spinner(1);
        spinner.start();

        dynamic_reconfigure::Reconfigure srv;
        dynamic_reconfigure::IntParameter int_param;
        int_param.name = "int_param";

        int_param.value = (int)random();
        srv.request.config.ints.push_back(int_param);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(int_param.value, flag);

        int_param.value = INT32_MAX;
        srv.request.config.ints.push_back(int_param);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(int_param.value, flag);

        int_param.value = INT32_MIN;
        srv.request.config.ints.push_back(int_param);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(int_param.value, flag);
    }

    void doubleCallback(const DDMap& map, int, double *flag) {
        EXPECT_EQ("double",map.find("double_param")->second->getValue().getType());
        *flag = map.find("double_param")->second->getValue().toDouble();
    }

    TEST(DDynamicReconfigureTest, doubleTest) { // NOLINT(cert-err58-cpp,modernize-use-equals-delete)
        ros::NodeHandle nh("~");
        double flag = 0;
        DDFunc callback = bind(&doubleCallback,_1,_2,&flag);

        DDynamicReconfigure dd(nh);
        dd.add(new DDDouble("double_param", 0, 0));
        dd.start(callback);

        ros::AsyncSpinner spinner(1);
        spinner.start();

        dynamic_reconfigure::Reconfigure srv;
        dynamic_reconfigure::DoubleParameter double_param;
        double_param.name = "double_param";

        double_param.value = (double)random();
        srv.request.config.doubles.push_back(double_param);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(double_param.value, flag);

        double_param.value = DBL_MAX;
        srv.request.config.doubles.push_back(double_param);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(double_param.value, flag);

        double_param.value = DBL_MIN;
        srv.request.config.doubles.push_back(double_param);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(double_param.value, flag);

        double_param.value = -DBL_MAX;
        srv.request.config.doubles.push_back(double_param);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(double_param.value, flag);

        double_param.value = -DBL_MIN;
        srv.request.config.doubles.push_back(double_param);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(double_param.value, flag);
    }

    void boolCallback(const DDMap& map, int, bool *flag) {
        EXPECT_EQ("bool",map.find("bool_param")->second->getValue().getType());
        *flag = map.find("bool_param")->second->getValue().toBool();
    }

    TEST(DDynamicReconfigureTest, boolTest) { // NOLINT(cert-err58-cpp,modernize-use-equals-delete)
        ros::NodeHandle nh("~");
        bool flag = true;
        DDFunc callback = bind(&boolCallback,_1,_2,&flag);

        DDynamicReconfigure dd(nh);
        dd.add(new DDBool("bool_param", 0, false));
        dd.start(callback);

        ros::AsyncSpinner spinner(1);
        spinner.start();

        dynamic_reconfigure::Reconfigure srv;
        dynamic_reconfigure::BoolParameter bool_param;
        bool_param.name = "bool_param";

        bool_param.value = (unsigned char)false;
        srv.request.config.bools.push_back(bool_param);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ((bool)bool_param.value, flag);

        flag = false;

        bool_param.value = (unsigned char)true;
        srv.request.config.bools.push_back(bool_param);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ((bool)bool_param.value, flag);
    }

    void strCallback(const DDMap& map, int, string *flag) {
        EXPECT_EQ("string",map.find("string_param")->second->getValue().getType());
        *flag = map.find("string_param")->second->getValue().toString();
    }

    TEST(DDynamicReconfigureTest, stringTest) { // NOLINT(cert-err58-cpp,modernize-use-equals-delete)
        ros::NodeHandle nh("~");
        string flag = "YOU SHOULDN'T RECEIVE THIS";
        DDFunc callback = bind(&strCallback,_1,_2,&flag);

        DDynamicReconfigure dd(nh);
        dd.add(new DDString("string_param", 0, ""));
        dd.start(callback);

        ros::AsyncSpinner spinner(1);
        spinner.start();

        dynamic_reconfigure::Reconfigure srv;
        dynamic_reconfigure::StrParameter string_param;
        string_param.name = "string_param";

        string_param.value = string("\000"); // NOLINT(bugprone-string-literal-with-embedded-nul)
        srv.request.config.strs.push_back(string_param);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(string_param.value, flag);

        string_param.value = "";
        srv.request.config.strs.push_back(string_param);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(string_param.value, flag);

        string_param.value = "Hello World";
        srv.request.config.strs.push_back(string_param);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(string_param.value, flag);
    }

    void enumCallback(const DDMap& map, int, int *flag) {
        EXPECT_EQ("int",map.find("enum_param")->second->getValue().getType());
        *flag = map.find("enum_param")->second->getValue().toInt();
    }

    TEST(DDynamicReconfigureTest, enumTest) { // NOLINT(cert-err58-cpp,modernize-use-equals-delete)
        ros::NodeHandle nh("~");
        int flag = 0;
        DDFunc callback = bind(&enumCallback,_1,_2,&flag);

        map<string,int> dict;
        dict["ONE"] = 1;
        dict["NEG-ONE"] = -1;
        dict["TEN"] = 10;

        DDynamicReconfigure dd(nh);
        dd.add(new DDEnum("enum_param", 0, "ONE", dict));
        dd.start(callback);

        ros::AsyncSpinner spinner(1);
        spinner.start();

        dynamic_reconfigure::Reconfigure srv;


        dynamic_reconfigure::IntParameter int_enum;
        int_enum.name = "enum_param";

        int_enum.value = 1;
        srv.request.config.ints.push_back(int_enum);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(int_enum.value, flag);

        int_enum.value = 10;
        srv.request.config.ints.push_back(int_enum);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(int_enum.value, flag);

        int_enum.value = -1;
        srv.request.config.ints.push_back(int_enum);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(int_enum.value, flag);

        srv.request.config.ints.clear();
        dynamic_reconfigure::StrParameter str_enum;
        str_enum.name = "enum_param";

        str_enum.value = "ONE";
        srv.request.config.strs.push_back(str_enum);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(dict[str_enum.value], flag);

        str_enum.value = "TEN";
        srv.request.config.strs.push_back(str_enum);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(dict[str_enum.value], flag);

        str_enum.value = "NEG-ONE";
        srv.request.config.strs.push_back(str_enum);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(dict[str_enum.value], flag);
    }

    void complexCallback(const DDMap& map, int level) {
        EXPECT_EQ(0, level);
        EXPECT_EQ(1, map.at("int_param")->getValue().toInt());
        EXPECT_EQ(0.6, map.at("double_param")->getValue().toDouble());
        EXPECT_EQ("Goodbye Home", map.at("str_param")->getValue().toString());
        EXPECT_EQ(false, map.at("bool_param")->getValue().toBool());
        EXPECT_EQ(3, map.at("enum_param")->getValue().toInt());
    }

    TEST(DDynamicReconfigureTest, callbackTest) { // NOLINT(cert-err58-cpp,modernize-use-equals-delete)
        ros::NodeHandle nh("~");
        DDynamicReconfigure dd(nh); // gets our main class running
        dd.add(new DDInt("int_param", 0, 0, 50, 100));
        dd.add(new DDDouble("double_param", 0, .5, 0, 1));
        dd.add(new DDString("str_param", 0, "Hello World"));
        dd.add(new DDBool("bool_param", 0, true));
        map<string, int> dict; {
            dict["Small"] = 0;
            dict["Medium"] = 1;
            dict["Large"] = 2;
            dict["ExtraLarge"] = 3;
        }
        dd.add(new DDEnum("enum_param", 0, 0, dict));
        dd.start(complexCallback);

        ros::AsyncSpinner spinner(1);
        spinner.start();

        dynamic_reconfigure::Reconfigure srv;

        dynamic_reconfigure::IntParameter int_param;
        int_param.name = "int_param";
        int_param.value = 1;
        srv.request.config.ints.push_back(int_param);

        dynamic_reconfigure::DoubleParameter double_param;
        double_param.name = "double_param";
        double_param.value = 0.6;
        srv.request.config.doubles.push_back(double_param);

        dynamic_reconfigure::BoolParameter bool_param;
        bool_param.name = "bool_param";
        bool_param.value = (unsigned char) false;
        srv.request.config.bools.push_back(bool_param);

        dynamic_reconfigure::StrParameter string_param;
        string_param.name = "str_param";
        string_param.value = "Goodbye Home";
        srv.request.config.strs.push_back(string_param);

        dynamic_reconfigure::StrParameter enum_param;
        enum_param.name = "enum_param";
        enum_param.value = "ExtraLarge";
        srv.request.config.strs.push_back(enum_param);

        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));

        bool flag = false;
        DDFunc callback = bind(&basicCallback,_1,_2,&flag);
        dd.setCallback(callback);
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_TRUE(flag);

        flag = false;
        dd.clearCallback();
        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_FALSE(flag);
    }

    class InternalClass {
    public:
        inline void internalCallback(const DDMap& map, int level) {}
    };

    TEST(DDynamicReconfigureTest, staticCallbackTest) { // NOLINT(cert-err58-cpp,modernize-use-equals-delete)
        ros::NodeHandle nh("~");
        DDynamicReconfigure dd(nh); // gets our main class running

        dd.start(&InternalClass::internalCallback,new InternalClass);

        ros::AsyncSpinner spinner(1);
        spinner.start();

        dynamic_reconfigure::Reconfigure srv;

        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
    }

    void levelCallback(const DDMap&, int level, int *flag) {
        *flag = level;
    }

    TEST(DDynamicReconfigureTest, levelTest) { // NOLINT(cert-err58-cpp,modernize-use-equals-delete)
        ros::NodeHandle nh("~");
        int flag = 0;
        DDFunc callback = bind(&levelCallback, _1, _2, &flag);

        DDynamicReconfigure dd(nh);
        int top = (int) random() % 5 + 5;
        unsigned int or_sum = 0, next;
        for (int i = 1; i < top; i++) {
            next = (unsigned int) random();
            or_sum |= next;
            dd.add(new DDInt((format("param_%d") % i).str(), next, 0));
        }
        dd.start(callback);

        ros::AsyncSpinner spinner(1);
        spinner.start();

        dynamic_reconfigure::Reconfigure srv;
        dynamic_reconfigure::IntParameter int_param;
        for (int i = 1; i < top; i++) {
            int_param.name = (format("param_%d") % i).str();
            int_param.value = 1;
            srv.request.config.ints.push_back(int_param);
        }

        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(or_sum, flag);

        dd.add(new DDInt("unchanged_param", 1, 0)); //u-int max means everything is 1, so the result must also be that.
        dynamic_reconfigure::IntParameter unchanged_param;
        unchanged_param.name = "unchanged_param";
        unchanged_param.value = 1;
        srv.request.config.ints.push_back(unchanged_param);

        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(1, flag);

        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        EXPECT_EQ(0, flag);
    }

    void badCallback(const DDMap&, int) {
        std::exception e;
        throw e; // NOLINT(cert-err09-cpp,cert-err61-cpp,misc-throw-by-value-catch-by-reference)
    }

    TEST(DDynamicReconfigureTest, badCallbackTest) { // NOLINT(cert-err58-cpp,modernize-use-equals-delete)
        ros::NodeHandle nh("~");
        DDynamicReconfigure dd(nh); // gets our main class running
        dd.start(badCallback);

        ros::AsyncSpinner spinner(1);
        spinner.start();

        dynamic_reconfigure::Reconfigure srv;

        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
        // this is the best way to see exceptions doesn't make the whole thing tumble
    }

    void missingCallback(const DDMap& map, int) {
        EXPECT_EQ(map.end(),map.find("int_param"));
        EXPECT_EQ(map.end(),map.find("double_param"));
        EXPECT_EQ(map.end(),map.find("bool_param"));
        EXPECT_EQ(map.end(),map.find("str_param"));
        EXPECT_EQ(map.end(),map.find("enum_param"));
    }

    TEST(DDynamicReconfigureTest, unknownParamTest) { // NOLINT(cert-err58-cpp,modernize-use-equals-delete)
        ros::NodeHandle nh("~");
        DDynamicReconfigure dd(nh); // gets our main class running
        dd.start(missingCallback);

        ros::AsyncSpinner spinner(1);
        spinner.start();

        dynamic_reconfigure::Reconfigure srv;

        dynamic_reconfigure::IntParameter int_param;
        int_param.name = "int_param";
        int_param.value = 1;
        srv.request.config.ints.push_back(int_param);

        dynamic_reconfigure::DoubleParameter double_param;
        double_param.name = "double_param";
        double_param.value = 0.6;
        srv.request.config.doubles.push_back(double_param);

        dynamic_reconfigure::BoolParameter bool_param;
        bool_param.name = "bool_param";
        bool_param.value = (unsigned char) false;
        srv.request.config.bools.push_back(bool_param);

        dynamic_reconfigure::StrParameter string_param;
        string_param.name = "str_param";
        string_param.value = "Goodbye Home";
        srv.request.config.strs.push_back(string_param);

        dynamic_reconfigure::StrParameter enum_param;
        enum_param.name = "enum_param";
        enum_param.value = "ExtraLarge";
        srv.request.config.strs.push_back(enum_param);

        EXPECT_TRUE(ros::service::call(nh.getNamespace() + "/set_parameters", srv));
    }
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    ros::init(argc, argv, "ddynamic_reconfigure_test");

    srand((unsigned int)random());

    return RUN_ALL_TESTS();
}