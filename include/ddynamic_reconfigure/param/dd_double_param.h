//
// Created by Noam Dori on 19/06/18.
//

#ifndef DDYNAMIC_RECONFIGURE_DD_DOUBLE_PARAM_H
#define DDYNAMIC_RECONFIGURE_DD_DOUBLE_PARAM_H

#include "ddynamic_reconfigure/dd_param.h"
#include "ddynamic_reconfigure/ddynamic_reconfigure.h"

namespace ddr {
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

        DDDouble(const string &name, unsigned int level, double def, double max = DBL_MAX, double min = -DBL_MAX) {
            name_ = name;
            level_ = level;
            def_ = def;
            val_ = def;
            max_ = max;
            min_ = min;
        }
    protected:
        unsigned int level_;
        double def_,max_,min_,val_;
        string name_;
    };
}


#endif //DDYNAMIC_RECONFIGURE_DD_DOUBLE_PARAM_H
