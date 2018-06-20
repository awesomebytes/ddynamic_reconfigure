#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-loop-convert"
#pragma ide diagnostic ignored "modernize-use-auto"
//
// Created by Noam Dori on 20/06/18.
//

#include "ddynamic_reconfigure/param/dd_enum_param.h"

namespace ddr {

    bool DDEnumParam::sameType(Value val) {
        return val.getType() == "int" || val.getType() == "string";
    }

    bool DDEnumParam::sameValue(Value val) {
        if(val.getType() == "string") {
            return dict_.find(val.getStrVal()) != dict_.end();
        } else {
            return val.getIntVal() == val_;
        }
    }

    void DDEnumParam::setValue(Value val) {
        if(val.getType() == "string" && dict_.find(val.getStrVal()) != dict_.end()) {
            val_ = dict_.find(val.getStrVal())->second;
        } else {
            val_ = val.getIntVal();
        }
    }

    DDEnumParam::DDEnumParam(const string &name, unsigned int level, int def, const map<string, int> &dictionary) :
            DDIntParam(name,level,def),
            dict_(dictionary) {
        max_ = def;
        min_ = def;
        for(map<string,int>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++) {
            if(it->second > max_) {max_ = it->second;}
            if(it->second < min_) {min_ = it->second;}
        };
    }
}
#pragma clang diagnostic pop