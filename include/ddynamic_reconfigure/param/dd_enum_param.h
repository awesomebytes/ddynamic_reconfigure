//
// Created by Noam Dori on 20/06/18.
//

#ifndef DDYNAMIC_RECONFIGURE_DD_ENUM_PARAM_H
#define DDYNAMIC_RECONFIGURE_DD_ENUM_PARAM_H

#include "ddynamic_reconfigure/dd_param.h"
#include "ddynamic_reconfigure/ddynamic_reconfigure.h"
#include "dd_int_param.h"
#include <boost/foreach.hpp>

namespace ddr {
    /**
     * @brief an integer enum implementation of the parameter.
     * This is an extension to the int parameter,
     * which allows creating string aliases for certain (if not all) numbers available.
     */
    class DDEnum : public DDInt {
    public:

        bool sameType(Value val);

        bool sameValue(Value val);

        void setValue(Value val);

        /**
         * creates a new int-enum param
         * @param name the name of the parameter
         * @param level the change level
         * @param def the default value in integer form
         * @param description details about the parameter
         * @param dictionary the alias dictionary this enum will use.
         */
        DDEnum(const string &name, unsigned int level, const string &description,
                int def, const map<string,int> &dictionary);

        /**
         * creates a new int-enum param
         * @param name the name of the parameter
         * @param level the change level
         * @param def an alias of the default value
         * @param description details about the parameter
         * @param dictionary the alias dictionary this enum will use.
         */
        DDEnum(const string &name, unsigned int level, const string &description,
                const string& def, const map<string,int> &dictionary);

    protected:
        /** 
         * @brief A dictionary from the string aliases to their integer counterparts.
         * This method of storage allows integers to have multiple aliases.
         */
        const map<string,int> &dict_;
    };
}

#endif //DDYNAMIC_RECONFIGURE_DD_ENUM_PARAM_H