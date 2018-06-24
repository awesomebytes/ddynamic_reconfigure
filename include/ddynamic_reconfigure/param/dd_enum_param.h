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
    class DDEnum : public DDInt {
    public:

        bool sameType(Value val);

        bool sameValue(Value val);

        void setValue(Value val);

        DDEnum(const string &name, unsigned int level, int def, const map<string,int> &dictionary);

        DDEnum(const string &name, unsigned int level, const string& def, const map<string,int> &dictionary);

    protected:
        const map<string,int> &dict_;
    };
}

#endif //DDYNAMIC_RECONFIGURE_DD_ENUM_PARAM_H