//
// Created by Noam Dori on 19/06/18.
//

#include <ddynamic_reconfigure/param/dd_string_param.h>

namespace ddr {
    string DDStringParam::getName() {
        return name_;
    }

    void DDStringParam::prepGroup(Group &group) {
        ParamDescription desc;
        desc.name  = name_;
        //desc.desc = registered_string_[i].first;
        desc.level = level_;
        desc.type = "string";
        group.parameters.push_back(desc);
    }

    void DDStringParam::prepConfig(Config &conf) {
        StrParameter param;
        param.name = name_;
        param.value = val_;
        conf.strs.push_back(param);
    }

    void DDStringParam::prepConfigDescription(ConfigDescription &conf_desc) {
        StrParameter param;
        param.name = name_;
        param.value = def_;
        conf_desc.dflt.strs.push_back(param);
        param.value = "";
        conf_desc.max.strs.push_back(param);
        param.value = "";
        conf_desc.min.strs.push_back(param);
    }

    int DDStringParam::getLevel() {
        return level_;
    }

    bool DDStringParam::sameType(Value val) {
        return val.getType() == "string";
    }

    bool DDStringParam::sameValue(Value val) {
        return val.getStrVal() == val_;
    }

    void DDStringParam::setValue(Value val) {
        val_ = val.getStrVal();
    }
}
