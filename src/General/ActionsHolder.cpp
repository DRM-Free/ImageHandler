/*
 * ActionsHolder.cpp
 *
 *  Created on: 13 déc. 2017
 *      Author: anael
 */

#include "ActionsHolder.h"
#include <iostream>
/**
 *
 * @param key
 * @param description
 * @param isActive
 * @param behaviour
 */
ActionsHolder::ActionsHolder(char key, std::string description,
        std::function<bool()> isActive, std::function<std::any()> behaviour) :
        key(key), description(description), isActive(isActive), behaviour(
                behaviour) {
}

ActionsHolder::~ActionsHolder() {
}

std::pair<std::string, std::string> ActionsHolder::generateActionLabels() {
if (key != '\0') {return std::make_pair(std::any_cast<std::string>(key), description);}
//TODO specify user the requirements to meet to make action available
    else
        return std::make_pair("N/A", description);
}

std::any ActionsHolder::doBehaviour() {
    if (key != '\0') {
        return behaviour();
    } else {
        std::cerr
                << "An action with no key assigned was called, this is not supposed to happen !\n";
        return 1;
    }
}
