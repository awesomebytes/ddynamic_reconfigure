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
        string str_val_, type_;
        double double_val_;
        bool bool_val_;
    public:
        inline explicit Value(int val) : double_val_(0.0), bool_val_(false) {
            type_ = "int";
            int_val_ = val;
        }

        inline explicit Value(double val) : int_val_(0), bool_val_(false) {
            type_ = "double";
            double_val_ = val;
        }

        inline explicit Value(const string &val) : int_val_(0), double_val_(0.0), bool_val_(false) {
            type_ = "string";
            str_val_ = val;
        }

        inline explicit Value(bool val) : int_val_(0), double_val_(0.0) {
            type_ = "bool";
            bool_val_ = val;
        }

        inline string getType() {
            return type_;
        }

        inline int toInt() {
            if(type_ == "string") { return (int)str_val_.size();}
            else if(type_ == "bool") {return bool_val_;}
            else if(type_ == "double") {return double_val_ ? 1 : 0;}
            else {return int_val_;}
        }

        inline string toString() {
            std::stringstream ss;
            if(type_ == "string") { return str_val_;}
            else if(type_ == "bool") {return bool_val_ ? "true" : "false";}
            else if(type_ == "double") {ss << double_val_; return ss.str();}
            else {ss << int_val_; return ss.str();}
        }

        inline double toDouble() {
            if(type_ == "string") { return str_val_.size();}
            else if(type_ == "bool") {return bool_val_ ? 1.0 : 0.0;}
            else if(type_ == "double") {return double_val_;}
            else {return int_val_;}
        }

        inline bool toBool() {
            if(type_ == "string") { return str_val_.empty();}
            else if(type_ == "bool") {return bool_val_;}
            else if(type_ == "double") {return double_val_ != 0.0;}
            else {return int_val_ != 0;}
        }
    };
}

#endif //DDYNAMIC_RECONFIGURE_DD_VALUE_H
