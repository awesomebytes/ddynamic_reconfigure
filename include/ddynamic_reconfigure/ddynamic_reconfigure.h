//
// Created by Noam Dori on 18/06/18.
//
//include space, written in C++03
#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>

#include <string>
#include <vector>
#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "dd_param.h"
using namespace std;
using namespace boost;
using namespace dynamic_reconfigure;

#ifndef DDYNAMIC_RECONFIGURE_DDYNAMIC_RECONFIGURE_H
#define DDYNAMIC_RECONFIGURE_DDYNAMIC_RECONFIGURE_H
namespace ddr {
    // this is the pointer to any type of Dynamic Dynamic parameter.
    typedef shared_ptr<DDParam> DDPtr;
    // this is a map from the DDParam name to the object. Acts like a set with a search function.
    typedef map<string,DDPtr> DDMap;
    // the function you will use a lot
    typedef function<void(const DDMap&,int)> DDFunc;

    /**
     * @brief This class is the actual top-level API that manages the dynamic configuration of the files of d-reconfig.
     */
    class DDynamicReconfigure {
    public:
        /**
         * @brief creates the most basic instance of a 2d-conf object.
         * @param nh the node handler of the node this is placed at.
         */
        DDynamicReconfigure(ros::NodeHandle nh);

        /**
         * @brief adds a parameter to the list, allowing it to be generated.
         * @param param the pointer to the 2d-param to add to the list.
         */
        void add(DDPtr param);

        /**
         * @brief adds a parameter to the list, allowing it to be generated.
         * @param param the pointer to the 2d-param to add to the list.
         */
        void add(DDParam *param);

        /**
         * @brief sets the callback to this.
         * @param callback a boost function with the method to use when values are updated.
         */
        void setCallback(DDFunc callback);

        /**
         * @brief sets the callback to be empty.
         */
        void clearCallback();

        /**
         * @brief starts the server and config, without having any callback.
         */
        void start();

        /**
         * @brief starts the server, using the given callback in function form.
         * @param callback a boost function with the method to use when values are updated.
         */
        void start(DDFunc callback);

        /**
         * @brief starts the server, using the given callback in method form.
         * @param callback a void pointer accepting a callback type with the method to use when values are updated.
         */
        void start(void(*callback)(const DDMap&, int));

        /**
         * @brief starts the server, using the given callback in class-wise static method form.
         * @param callback a class void pointer accepting a callback type with the method to use when values are updated.
         * @param obj the object used for reference in the class void
         * @tparam T the class of the object.
         */
        template<class T> void start(void(T::*callback)(const DDMap&, int), T *obj) {
            DDFunc f = bind(callback,obj,_1,_2);
            start();
        }

        /**
         * @brief reassigns a value to the internal map assuming it is registered.
         * @param map the map that is being edited
         * @param name the name of the parameter to test
         * @param value the value of the new parameter
         * @tparam T the type of value
         * @return -1 if the value could not be reassigned,
         *          0 if the value was not changed,
         *          otherwise the level of the parameter changed.
         */
         template <class T>
        static int reassign(DDMap& map, const string &name, T value);
    private:

        /**
         * @brief calls the internal callback for the low-level service, not exposed to us.
         * @param obj the object we are using for its callback.
         * @param req ----(ROS)
         * @param rsp ----(ROS)
         * @return -------(ROS)
         */
        static bool internalCallback(DDynamicReconfigure *obj, Reconfigure::Request &req, Reconfigure::Response &rsp);

        /**
         * @brief makes the config descriptions for publishing
         * @return a ROS message of type ConfigDescription
         */
        ConfigDescription makeDescription() const;

        /**
         * @brief makes the config update for publishing
         * @return a ROS message of type Config
         */
        Config makeConfig() const;

        /**
         * @brief gets the updates and assigns them to DDMap
         * @param req the ROS request holding info about the new map
         * @param config the map to update
         * @return the level of change (integer)
         */
        int getUpdates(const Reconfigure::Request &req, DDMap &config);

        DDMap params_;
        shared_ptr<function<void(const DDMap&, int)> > callback_;
        ros::NodeHandle nh_;
        ros::Publisher desc_pub_, update_pub_;
        #pragma clang diagnostic push // CLion suppressor
        #pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
        ros::ServiceServer set_service_;
        #pragma clang diagnostic pop
    };
}
#endif //DDYNAMIC_RECONFIGURE_DDYNAMIC_RECONFIGURE_H