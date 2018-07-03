//
// Created by Noam Dori on 18/06/18.
//

#ifndef DDYNAMIC_RECONFIGURE_DD_PARAM_H
#define DDYNAMIC_RECONFIGURE_DD_PARAM_H

#include <string>
#include <dynamic_reconfigure/Group.h>
#include <dynamic_reconfigure/Config.h>
#include <dynamic_reconfigure/ConfigDescription.h>
#include "dd_value.h"

using namespace dynamic_reconfigure;
using namespace std;
namespace ddynamic_reconfigure {
    /**
     * @brief This class is the generic parameter class. It is the physical parameter, and assumes nothing else.
     * this class should contain everything needed to generate/implement a dynamic server.
     * Since a lot of 1d-conf is written in python, perhaps it should generate the files?
     * this class is abstract and should implement almost nothing on its own.
     */
    class DDParam {
    public:

        /**
         * @brief gets the name of the parameter, that is, the ID used in the program when requesting it.
         * @return the unique string name of the parameter.
         */
        virtual string getName() const = 0;

        /**
         * @brief fetches the level of the parameter
         * @return the level of the param.
         */
        virtual int getLevel() const = 0;

        /**
         * @brief gets the value of this parameter.
         * @return the value stored in this param.
         */
        virtual Value getValue() const = 0;
        
        /**
         * @brief checks if this parameter is the same type as the value.
         * @param val the value to test
         * @return true is this parameter can handle the original value, false otherwise.
         */
        virtual bool sameType(Value val) = 0;
        
        /**
         * @brief checks if this parameter has the same value as the value.
         * @param val the value to test
         * @return true is this parameter can is the same as the original value, false otherwise.
         */
        virtual bool sameValue(Value val) = 0;

        /**
         * @brief sets the value of this parameter as this one.
         * @param val the value to use
         */
        virtual void setValue(Value val) = 0;

        /**
         * @brief updates a group message according to this param's info.
         * @param group the group to update.
         * @note this is an internal method. It is recommended not to use it.
         */
        virtual void prepGroup(Group &group) = 0;

        /**
         * @brief updates a config message according to this param's info.
         * @param conf the group to update.
         * @note this is an internal method. It is recommended not to use it.
         */
        virtual void prepConfig(Config &conf) = 0;

        /**
         * @brief updates a config description message according to this param's info.
         * @param conf_desc the config description to update.
         * @note this is an internal method. It is recommended not to use it.
         */
        virtual void prepConfigDescription(ConfigDescription &conf_desc) = 0;

        /**
         * @brief the operator taking care of streaming the param values
         * @param os the stream to place the param into
         * @param param the param you want to place into the stream
         * @return os, but with param added.
         */
        friend ostream& operator<<(ostream& os, const DDParam &param);
    };
}
#endif //DDYNAMIC_RECONFIGURE_DD_PARAM_H
