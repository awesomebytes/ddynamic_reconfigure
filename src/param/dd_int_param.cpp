//
// Created by Noam Dori on 19/06/18.
//

#include <ddynamic_reconfigure/param/dd_int_param.h>

namespace ddr {
    string DDIntParam::getName() {
        return name_;
    }

    void DDIntParam::prepGroup(Group &group) {
        ParamDescription desc;
        desc.name  = name_;
        //desc.desc = registered_int_[i].first;
        desc.level = level_;
        desc.type = "int";
        group.parameters.push_back(desc);
    }

    void DDIntParam::prepConfig(Config &conf) {
        IntParameter param;
        param.name = name_;
        param.value = val_;
        conf.ints.push_back(param);
    }

    void DDIntParam::prepConfigDescription(ConfigDescription &conf_desc) {
        IntParameter param;
        param.name = name_;
        param.value = def_;
        conf_desc.dflt.ints.push_back(param);
        param.value = max_;
        conf_desc.max.ints.push_back(param);
        param.value = min_;
        conf_desc.min.ints.push_back(param);
    }

    int DDIntParam::getLevel() {
        return level_;
    }

    bool DDIntParam::sameType(Value val) {
        return val.getType() == "int";
    }

    bool DDIntParam::sameValue(Value val) {
        return val.getIntVal() == val_;
    }

    void DDIntParam::setValue(Value val) {
        val_ = val.getIntVal();
    }
}
