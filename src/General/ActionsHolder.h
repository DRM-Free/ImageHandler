/*
 * ActionsHolder.h
 *
 *  Created on: 13 déc. 2017
 *      Author: anael
 */

#ifndef ACTIONSHOLDER_H_
#define ACTIONSHOLDER_H_

#include <any>
#include <functional>
#include <string>
#include <utility>

class CustomWindow;

class ActionsHolder {
//-------------------Attributes
private:
//    std::map<char, KeyAction> registeredActions;
    char key;
    std::string description;
    std::function<bool()> isActive;
    std::function<std::any()> behaviour;

//-------------------Constructors
public:
    /**
     *
     * @param string is the action descrption (1 word or 2)
     * First function is the isActive function that determines when the action is available
     * Second function is the behaviour of hte action (what it does)
     */

    //FIXME Choose whether or not ActionsHolder should contain the keyboard key and adapt accordingly
    ActionsHolder(char key, std::string description,
            std::function<bool()> isActive,
            std::function<std::any()> behaviour);
    std::pair<std::string, std::string> generateActionLabels();

    virtual ~ActionsHolder();

private:

//-------------------Methods
public:
    std::any doBehaviour();
private:

//-------------------Getters&Setters
public:

private:

};

#endif /* ACTIONSHOLDER_H_ */
