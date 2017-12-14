/*
 * keyAction.h
 *
 *  Created on: 14 déc. 2017
 *      Author: anael
 */

#ifndef KEYACTION_H_
#define KEYACTION_H_

#include <any>
#include <functional>
#include <string>

class KeyAction {
//-------------------Attributes
private:
    char key;
    std::string desc;
    std::function<bool()> isActive;
    std::function<std::any()> behaviour;
//-------------------Constructors
public:
    KeyAction(char key, std::string desc, std::function<bool()> isActive,
            std::function<std::any()> behaviour);
    virtual ~KeyAction();

private:

//-------------------Methods
public:

private:

//-------------------Getters&Setters
public:

private:

};

#endif /* KEYACTION_H_ */
