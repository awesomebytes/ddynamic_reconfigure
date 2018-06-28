//
// Created by Noam Dori on 19/06/18.
//
#include <string>
#include <sstream>
#include <cstdio>
#include <boost/functional/hash.hpp>

#ifndef DDYNAMIC_RECONFIGURE_DD_VALUE_H
#define DDYNAMIC_RECONFIGURE_DD_VALUE_H
using namespace std;
using namespace boost;
namespace ddr {
    /**
     * @brief an object wrapper capable of storing an explicit value and its original type.
     * Can convert into other types, and provides API to do so and to lookup everything about it.
     */
    class Value {
    private:
        int int_val_;
        string str_val_, type_;
        double double_val_;
        bool bool_val_;
    public:
        /**
         * creates an integer value wrapper
         * @param val the int to wrap
         */
        inline explicit Value(int val) : double_val_(0.0), bool_val_(false) {
            type_ = "int";
            int_val_ = val;
        }

        /**
         * creates an double value wrapper
         * @param val the double to wrap
         */
        inline explicit Value(double val) : int_val_(0), bool_val_(false) {
            type_ = "double";
            double_val_ = val;
        }

        /**
         * creates an integer value wrapper
         * @param val the int to wrap
         */
        inline explicit Value(const string &val) : int_val_(0), double_val_(0.0), bool_val_(false) {
            type_ = "string";
            str_val_ = val;
        }

        /**
         * creates an integer value wrapper
         * @param val the int to wrap
         */
        inline explicit Value(bool val) : int_val_(0), double_val_(0.0) {
            type_ = "bool";
            bool_val_ = val;
        }

        /**
         * gets the type this value wrapper stores
         * @return a string containing the type: one of {"int","double","bool","string"}
         */
        inline string getType() {
            return type_;
        }

        /**
         * converts the stored value into an integer.
         * @return for native integers: returns itself
         *         for native doubles: returns a casted integer
         *         for native booleans: returns 1 if true, 0 if false.
         *         for native strings: if the string contains an integer value (for example "1" contains the int '1' in it),
         *                             it will return the integer interpretation of that string.
         *                             Otherwise, returns the hash value of the string.
         */
        inline int toInt() {
            if (type_ == "string") {
                int i;
                if (sscanf(str_val_.c_str(), "%d", &i) == 0) {
                    return (int) hash<string>()(str_val_);
                }
                return i;
            } else if (type_ == "bool") { return bool_val_ ? 1 : 0; }
            else if (type_ == "double") { return (int) double_val_; }
            else { return int_val_; }
        }

        inline string toString() {
            stringstream ss;
            if(type_ == "string") { return str_val_;}
            else if(type_ == "bool") {return bool_val_ ? "true" : "false";}
            else if(type_ == "double") {ss << double_val_; return ss.str();}
            else {ss << int_val_; return ss.str();}
        }

        inline double toDouble() {
            if(type_ == "string") {
                double f;
                if(sscanf(str_val_.c_str(), "%lf", &f) == 0) {
                    return hash<string>()(str_val_);
                }
                return f;
            } else if(type_ == "bool") {return bool_val_ ? 1.0 : 0.0;}
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
