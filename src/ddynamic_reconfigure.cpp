//
// Created by Noam Dori on 18/06/18.
//
#include <ddynamic_reconfigure/ddynamic_reconfigure.h>
#include <ddynamic_reconfigure/dd_value.h>

using namespace boost;
namespace ddr {
    // this is the pointer to any type of Dynamic Dynamic parameter.
    typedef shared_ptr<DDParam> DDPtr;
    // this is a map from the DDParam name to the object. Acts like a set with a search function.
    typedef map<string,DDPtr> DDMap;

    DDynamicReconfigure::DDynamicReconfigure(ros::NodeHandle nh) : DDynamicReconfigure(nh, ros::this_node::getName() + "_dyn_rec") {};

    DDynamicReconfigure::DDynamicReconfigure(ros::NodeHandle nh, string name) : callback_() {
        conf_name_ = name;
        nh_ = nh;
    };

    void DDynamicReconfigure::addVariable(DDPtr param) {
        params_[param->getName()] = param;
    };

    void DDynamicReconfigure::start() {
        ConfigDescription conf_desc = makeDescription(); // registers defaults and max/min descriptions.
        Config conf = makeConfig(); // the actual config file in C++ form.

        // publishes Config and ConfigDescription.
        set_service_ = nh_.advertiseService("set_parameters", &internalCallback); // this allows changes to the parameters

        // this makes the parameter descriptions
        desc_pub_ = nh_.advertise<ConfigDescription>("parameter_descriptions", 1, true);
        desc_pub_.publish(conf_desc);

        // this creates the type/level of everything
        update_pub_ = nh_.advertise<Config>("parameter_updates", 1, true);
        update_pub_.publish(conf);
    }

    Config DDynamicReconfigure::makeConfig() const {
        Config conf;
        GroupState group_state; // I dunno, but its important?

        // action 3 - prepping the GroupState msg for all params
        group_state.name = "Default";
        group_state.state = (unsigned char)true;

        // action 4 - prepping the Config msg for all params
        conf.groups.push_back(group_state);
        for (const auto &param : params_) { param.second->prepConfig(conf);}
        return conf;
    }

    ConfigDescription DDynamicReconfigure::makeDescription() const {
        ConfigDescription conf_desc;
        Group group; // registers level and type.

        // action 1 - prepping the Group msg for all params
        group.name = "default";
        for (const auto &param : params_) { param.second->prepGroup(group);}

        // action 2 - prepping the ConfigDescription msg for all params
        for (const auto &param : params_) { param.second->prepConfigDescription(conf_desc);}
        conf_desc.groups.push_back(group);
        return conf_desc;
    };

    void DDynamicReconfigure::start(function<void(DDMap,int)>& callback) {
        start();
        setCallback(callback);
    };

    void DDynamicReconfigure::start(void(*callback)(DDMap,int)) {
        function<void(DDMap,int)> f(callback);
        start(f);
    };

    template <class T> void DDynamicReconfigure::start(void(T::*callback)(DDMap,int), T* obj) {

        function<void(DDMap,int)> f = bind(callback,obj,_1);
        start();
    }

    void DDynamicReconfigure::setCallback(function<void(DDMap,int)>& callback) {
        callback_ = callback;
    };

    void DDynamicReconfigure::clearCallback() {
        callback_;
    };

    // Private function: internal callback used by the service to call our lovely callback.
    bool DDynamicReconfigure::internalCallback(Reconfigure::Request& req, Reconfigure::Response& rsp) {
        ROS_DEBUG_STREAM("Called config callback of ddynamic_reconfigure");

        int level = getUpdates(req, params_);

        if (callback_) {
            try {
                callback_(params_,level);
            } catch (exception &e) {
                ROS_WARN("Reconfigure callback failed with exception %s: ", e.what());
            } catch (...) {
                ROS_WARN("Reconfigure callback failed with unprintable exception.");
            }
        }

        update_pub_.publish(makeConfig()); // updates the config

        return true;
    }

    int DDynamicReconfigure::getUpdates(const Reconfigure::Request &req, DDMap &config) {
        int level = 0;
        // the ugly part of the code, since ROS does not provide a nice generic message. Oh well...
        for (auto &i : req.config.ints) {
            int new_level = reassign(config, i.name, i.value);
            if(new_level == -1) {
                ROS_ERROR_STREAM("Variable [" << i.name << "] is not registered");
            } else {
                level |= new_level;
            }
        }
        for (auto &i : req.config.doubles) {
            int new_level = reassign(config, i.name, i.value);
            if(new_level == -1) {
                ROS_ERROR_STREAM("Variable [" << i.name << "] is not registered");
            } else {
                level |= new_level;
            }
        }
        for (auto &i : req.config.bools) {
            int new_level = reassign(config, i.name, i.value);
            if(new_level == -1) {
                ROS_ERROR_STREAM("Variable [" << i.name << "] is not registered");
            } else {
                level |= new_level;
            }
        }
        for (auto &i : req.config.strs) {
            int new_level = reassign(config, i.name, i.value);
            if(new_level == -1) {
                ROS_ERROR_STREAM("Variable [" << i.name << "] is not registered");
            } else {
                level |= new_level;
            }
        }
        return level;
    }

    template <class T>
    int DDynamicReconfigure::reassign(DDMap& map, const string &name, T value) {
        Value val(value); // abusing C++ against generic types here.
        if(map.find(name) != map.end() && map[name]->sameType(val)) {
            DDPtr old = map[name]; // this is the old map which might be updated.
            if(old->sameValue(val)) { return 0;} else {
                DDParam param; param.sameValue(val);
                old->setValue(val);
                return old->getLevel();
            }
        } else {
            return -1;
        }
    }
}