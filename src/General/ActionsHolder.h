/*
 * ActionsHolder.h
 *
 *  Created on: 13 déc. 2017
 *      Author: anael
 */

#ifndef ACTIONSHOLDER_H_
#define ACTIONSHOLDER_H_

#include <functional>
#include <map>
#include <string>
#include <tuple>
#include <utility>

#include "KeyAction.h"

class ActionsHolder {
//-------------------Attributes
private:
    /**
     * isActive function will define wether or not the action is available depending on the context and type of action
     */
    std::map<char, KeyAction> registeredActions; //tuple contains key, description and isActive function

//-------------------Constructors
public:
    ActionsHolder(std::tuple<std::string, std::string, std::function<bool()>>);
    /**
     *
     * @return a pair which first element is the keyboard key and second is the action's description
     */
    std::pair<std::string, std::string> generateActionLabels();

    virtual ~ActionsHolder();

private:

//-------------------Methods
public:

private:

//-------------------Getters&Setters
public:

private:

};

#endif /* ACTIONSHOLDER_H_ */
