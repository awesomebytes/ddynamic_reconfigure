//
// Created by Noam Dori on 19/06/18.
//

#include <ddynamic_reconfigure/param/dd_bool_param.h>

namespace ddr {
    string DDBoolParam::getName() {
        return name_;
    }

    void DDBoolParam::prepGroup(Group &group) {
        ParamDescription desc;
        desc.name  = name_;
        //desc.desc = registered_bool_[i].first;
        desc.level = level_;
        desc.type = "bool";
        group.parameters.push_back(desc);
    }

    void DDBoolParam::prepConfig(Config &conf) {
        BoolParameter param;
        param.name = name_;
        param.value = (unsigned char)val_;
        conf.bools.push_back(param);
    }

    void DDBoolParam::prepConfigDescription(ConfigDescription &conf_desc) {
        BoolParameter param;
        param.name = name_;
        param.value = (unsigned char)def_;
        conf_desc.dflt.bools.push_back(param);
        param.value = (unsigned char)true;
        conf_desc.max.bools.push_back(param);
        param.value = (unsigned char)false;
        conf_desc.min.bools.push_back(param);
    }

    int DDBoolParam::getLevel() {
        return level_;
    }

    bool DDBoolParam::sameType(Value val) {
        return val.getType() == "bool";
    }

    bool DDBoolParam::sameValue(Value val) {
        return val.getBoolVal() == val_;
    }

    void DDBoolParam::setValue(Value val) {
        val_ = val.getBoolVal();
    }
}
