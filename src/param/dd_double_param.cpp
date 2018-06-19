//
// Created by Noam Dori on 19/06/18.
//

#include <ddynamic_reconfigure/param/dd_double_param.h>

namespace ddr {
    string DDDoubleParam::getName() {
        return name_;
    }

    void DDDoubleParam::prepGroup(Group &group) {
        ParamDescription desc;
        desc.name  = name_;
        //desc.desc = registered_double_[i].first;
        desc.level = level_;
        desc.type = "double";
        group.parameters.push_back(desc);
    }

    void DDDoubleParam::prepConfig(Config &conf) {
        DoubleParameter param;
        param.name = name_;
        param.value = val_;
        conf.doubles.push_back(param);
    }

    void DDDoubleParam::prepConfigDescription(ConfigDescription &conf_desc) {
        DoubleParameter param;
        param.name = name_;
        param.value = def_;
        conf_desc.dflt.doubles.push_back(param);
        param.value = max_;
        conf_desc.max.doubles.push_back(param);
        param.value = min_;
        conf_desc.min.doubles.push_back(param);
    }

    int DDDoubleParam::getLevel() {
        return level_;
    }

    bool DDDoubleParam::sameType(Value val) {
        return val.getType() == "double";
    }

    bool DDDoubleParam::sameValue(Value val) {
        return val.getDoubleVal() == val_;
    }

    void DDDoubleParam::setValue(Value val) {
        val_ = val.getDoubleVal();
    }
}
