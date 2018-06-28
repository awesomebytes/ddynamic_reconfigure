//
// Created by Noam Dori on 19/06/18.
//

#ifndef DDYNAMIC_RECONFIGURE_DD_STRING_PARAM_H
#define DDYNAMIC_RECONFIGURE_DD_STRING_PARAM_H

#include "ddynamic_reconfigure/dd_param.h"
#include "ddynamic_reconfigure/ddynamic_reconfigure.h"

namespace ddr {
    /**
     * @brief a string implementation of the parameter.
     * This is used to handle strings of characters of variable length.
     * Like string, each param value can hold up to 2^32-1 characters.
     */
    class DDString : public DDParam {
    public:
        string getName();

        void prepGroup(Group &group);

        void prepConfig(Config &conf);

        void prepConfigDescription(ConfigDescription &conf_desc);

        int getLevel();

        bool sameType(Value val);

        bool sameValue(Value val);

        void setValue(Value val);

        Value getValue();

        /**
         * creates a new string param
         * @param name the name of the parameter
         * @param level the change level
         * @param def the default value
         */
        DDString(const string &name, unsigned int level, const string &def) {
            name_ = name;
            level_ = level;
            def_ = def;
            val_ = def;
        }
    protected:
        /**
         * @brief the level of the parameter:
         * the degree in which things need to be shut down if this param changes
         */
        unsigned int level_;
        /**
         * @brief the default value (def_),
         * and the current value (val_)
         */
        string def_,val_;
        /**
         * @brief the name of the parameter
         */
        string name_;
    };
}


#endif //DDYNAMIC_RECONFIGURE_DD_STRING_PARAM_H
