//
// Created by Noam Dori on 19/06/18.
//

#ifndef DDYNAMIC_RECONFIGURE_DD_DOUBLE_PARAM_H
#define DDYNAMIC_RECONFIGURE_DD_DOUBLE_PARAM_H

#include "ddynamic_reconfigure/dd_param.h"
#include "ddynamic_reconfigure/ddynamic_reconfigure.h"


namespace ddr {
    typedef numeric_limits<double> d_limit;
    /**
     * @brief a double implementation of the parameter.
     * This is used to handle double-precision floating point numbers,
     * though it can handle single precision as well.
     */
    class DDDouble : public DDParam {
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
         * creates a new double param
         * @param name the name of the parameter
         * @param level the change level
         * @param def the default value
         * @param max the maximum allowed value. Defaults to DBL_MAX
         * @param min the minimum allowed value. Defaults to -DBL_MAX
         */
        DDDouble(const string &name, unsigned int level, double def,
                 double max = d_limit::infinity(), double min = -d_limit::infinity())
                : max_(), min_() {
            name_ = name;
            level_ = level;
            def_ = def;
            val_ = def;
            max_ = max;
            min_ = min;
        }
    protected:
        /**
         * @brief the level of the parameter:
         * the degree in which things need to be shut down if this param changes
         */
        unsigned int level_;
        /**
         * @brief the default value (def_),
         * the current value (val_),
         * the minimum allowed value (min_),
         * and the maximum allowed value (max_)
         */
        double def_,max_,min_,val_;
        /**
         * @brief the name of the parameter
         */
        string name_;
    };
}


#endif //DDYNAMIC_RECONFIGURE_DD_DOUBLE_PARAM_H
