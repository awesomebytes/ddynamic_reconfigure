//
// Created by Noam Dori on 20/06/18.
//

#ifndef DDYNAMIC_RECONFIGURE_DD_ENUM_PARAM_H
#define DDYNAMIC_RECONFIGURE_DD_ENUM_PARAM_H

#include "dd_int_param.h"
#include <boost/foreach.hpp>

namespace ddynamic_reconfigure {
    /**
     * @brief an integer enum implementation of the parameter.
     *        This is an extension to the int parameter,
     *        which allows creating string aliases for certain (if not all) numbers available.
     *
     */
    class DDEnum : public DDInt {
    private:
        /**
         * @brief converts old enum dictionaries to new ones.
         * @param complex the old dictionary
         * @return a dictionary with similar contents but in a new format.
         */
        map<string,int> simplify(pair<map<string,pair<int,string> >,string> complex) {
            map<string,int> ret;
            for(map<string,pair<int,string> >::const_iterator it = complex.first.begin();
                    it != complex.first.end(); ++it) { ret[it->first] = it->second.first; }
            return ret;
        }
    public:

        bool sameType(Value val);

        bool sameValue(Value val);

        void setValue(Value val);

        /**
         * @brief creates a new int-enum param
         * @param name the name of the parameter
         * @param level the change level
         * @param def the default value in integer form
         * @param description details about the parameter
         * @param dictionary the alias dictionary this enum will use.
         */
        DDEnum(const string &name, unsigned int level, const string &description,
                int def, const map<string,int> &dictionary);

        /**
         * @brief creates a new int-enum param
         * @param name the name of the parameter
         * @param level the change level
         * @param def an alias of the default value
         * @param description details about the parameter
         * @param dictionary the alias dictionary this enum will use.
         */
        DDEnum(const string &name, unsigned int level, const string &description,
                const string& def, const map<string,int> &dictionary);

        #pragma clang diagnostic push
        #pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
        /**
         * @brief creates a new int-enum param
         * @param name the name of the parameter
         * @param level the change level
         * @param def the default value in integer form
         * @param description details about the parameter
         * @param dictionary the alias dictionary this enum will use.
         * @note since ROS cannot send the enum and const descriptions, this method is useless.
         *       Please use the constructor which takes a map<string,int> instead.
         * @deprecated see note. This is not tested, so it may fail.
         */
        DDEnum(const string &name, unsigned int level, const string &description,
               int def, const pair<map<string,pair<int,string> >,string> &dictionary);

        /**
         * @brief creates a new int-enum param
         * @param name the name of the parameter
         * @param level the change level
         * @param def an alias of the default value
         * @param description details about the parameter
         * @param dictionary the alias dictionary this enum will use.
         * @note since ROS cannot send the enum and const descriptions, this method is useless.
         *       Please use the constructor which takes a map<string,int> instead.
         * @deprecated see note. This is not tested, so it may fail.
         */
        DDEnum(const string &name, unsigned int level, const string &description,
               const string& def, const pair<map<string,pair<int,string> >,string>  &dictionary);
        #pragma clang diagnostic pop

    protected:
        /** 
         * @brief A dictionary from the string aliases to their integer counterparts.
         * This method of storage allows integers to have multiple aliases.
         */
        const map<string,int> &dict_;
    };
}

#endif //DDYNAMIC_RECONFIGURE_DD_ENUM_PARAM_H