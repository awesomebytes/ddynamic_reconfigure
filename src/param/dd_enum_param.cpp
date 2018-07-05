#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "modernize-loop-convert"
#pragma ide diagnostic ignored "modernize-use-auto"
//
// Created by Noam Dori on 20/06/18.
//

#include <ddynamic_reconfigure/param/dd_enum_param.h>

#include "ddynamic_reconfigure/param/dd_enum_param.h"

namespace ddynamic_reconfigure {

    bool DDEnum::sameType(Value val) {
        return val.getType() == "int" || val.getType() == "string";
    }

    bool DDEnum::sameValue(Value val) {
        if(val.getType() == "string" && dict_.find(val.toString())->second == val_) {
            return true;
        } else {
            return val.toInt() == val_;
        }
    }

    void DDEnum::setValue(Value val) {
        if(val.getType() == "string" && dict_.find(val.toString()) != dict_.end()) {
            val_ = dict_.find(val.toString())->second;
        } else {
            val_ = val.toInt();
        }
    }

    DDEnum::DDEnum(const string &name, unsigned int level, const string &description,
            int def, const map<string, int> &dictionary) :
            DDInt(name,level,description,def),
            dict_(dictionary) {
        max_ = def;
        min_ = def;
        for(map<string,int>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++) {
            if(it->second > max_) {max_ = it->second;}
            if(it->second < min_) {min_ = it->second;}
        };
    }

    DDEnum::DDEnum(const string &name, unsigned int level, const string &description,
            const string &def, const map<string, int> &dictionary) :
            DDInt(name,level,description,dictionary.find(def)->second),
            dict_(dictionary) {
        max_ = def_;
        min_ = def_;
        for(map<string,int>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++) {
            if(it->second > max_) {max_ = it->second;}
            if(it->second < min_) {min_ = it->second;}
        };
    }

    DDEnum::DDEnum(const string &name, unsigned int level, const string &description, int def,
                   const pair<map<string, pair<int, string> >, string> &dictionary) :
                   DDInt(name,level,description,def),
                   dict_(simplify(dictionary)) {
        max_ = def;
        min_ = def;
        for(map<string,int>::const_iterator it = dict_.begin(); it != dict_.end(); it++) {
            if(it->second > max_) {max_ = it->second;}
            if(it->second < min_) {min_ = it->second;}
        };
    }

    DDEnum::DDEnum(const string &name, unsigned int level, const string &description, const string &def,
                   const pair<map<string, pair<int, string> >, string> &dictionary) :
                   DDInt(name,level,description,dictionary.first.find(def)->second.first),
                   dict_(simplify(dictionary)){
        max_ = def_;
        min_ = def_;
        for(map<string,int>::const_iterator it = dict_.begin(); it != dict_.end(); it++) {
            if(it->second > max_) {max_ = it->second;}
            if(it->second < min_) {min_ = it->second;}
        };
    }
}
#pragma clang diagnostic pop