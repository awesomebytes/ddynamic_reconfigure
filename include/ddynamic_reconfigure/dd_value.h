//
// Created by Noam Dori on 19/06/18.
//
#include <string>
#include <sstream>

#ifndef DDYNAMIC_RECONFIGURE_DD_VALUE_H
#define DDYNAMIC_RECONFIGURE_DD_VALUE_H
using namespace std;
namespace ddr {
    class Value {
    private:
        int int_val_;
        string str_val_, val_type_;
        double do_val_;
        bool bool_val_;
    public:
        inline explicit Value(int val) : do_val_(0.0), bool_val_(false) {
            val_type_ = "int";
            int_val_ = val;
        }

        inline explicit Value(double val) : int_val_(0), bool_val_(false) {
            val_type_ = "double";
            do_val_ = val;
        }

        inline explicit Value(const string &val) : int_val_(0), do_val_(0.0), bool_val_(false) {
            val_type_ = "string";
            str_val_ = val;
        }

        inline explicit Value(bool val) : int_val_(0), do_val_(0.0) {
            val_type_ = "bool";
            bool_val_ = val;
        }

        inline string getType() {
            return val_type_;
        }

        inline int getIntVal() {
            if(val_type_ == "string") { return (int)str_val_.size();}
            else if(val_type_ == "bool") {return bool_val_;}
            else if(val_type_ == "double") {return do_val_ ? 1 : 0;}
            else {return int_val_;}
        }

        inline string getStrVal() {
            std::stringstream ss;
            if(val_type_ == "string") { return str_val_;}
            else if(val_type_ == "bool") {return bool_val_ ? "true" : "false";}
            else if(val_type_ == "double") {ss << do_val_; return ss.str();}
            else {ss << int_val_; return ss.str();}
        }

        inline double getDoubleVal() {
            if(val_type_ == "string") { return str_val_.size();}
            else if(val_type_ == "bool") {return bool_val_ ? 1.0 : 0.0;}
            else if(val_type_ == "double") {return do_val_;}
            else {return int_val_;}
        }

        inline bool getBoolVal() {
            if(val_type_ == "string") { return str_val_.empty();}
            else if(val_type_ == "bool") {return bool_val_;}
            else if(val_type_ == "double") {return do_val_ != 0.0;}
            else {return int_val_ != 0;}
        }
    };
}

#endif //DDYNAMIC_RECONFIGURE_DD_VALUE_H
