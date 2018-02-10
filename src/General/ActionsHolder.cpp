/*
 * ActionsHolder.cpp
 *
 *  Created on: 13 déc. 2017
 *      Author: anael
 */

#include "ActionsHolder.h"
#include <iostream>
#include <wx/dialog.h>
/**
 *
 * @param key
 * @param description
 * @param isActive
 * @param behaviour
 */
ActionsHolder::ActionsHolder(char key, std::string description,
        std::string const& inactiveMsg, std::function<bool()> isActive,
        std::function<std::any()> behaviour) :
        key(key), description(description), inactiveMsg(inactiveMsg), isActive(
                isActive), behaviour(behaviour) {
}

ActionsHolder::~ActionsHolder() {
}

std::pair<std::string, std::string> ActionsHolder::generateActionLabels() {
    if (key == '\0') {
        return std::make_pair("N/A", description);
    }
    if (key == WXK_ESCAPE) {
        return std::make_pair("Esc", description);
    }
    return std::make_pair(std::string(1, key), description);
}

std::any ActionsHolder::doBehaviour() {
    if (isActive()) {

        if (key != '\0') {
            behaviour();
            return 1;
        } else {
            std::cerr
                    << "An action with no key assigned was called, this is not supposed to happen !\n";
            return 1;
        }
    } else {
        wxMessageDialog dia(nullptr, "Unavailable Action :\n" + inactiveMsg,
                "Ok");
        dia.ShowModal();
    }
}

bool ActionsHolder::checkActive() {
    return isActive();
}

char ActionsHolder::getKey() {
    return key;
}

void ActionsHolder::setKey(char c) {
    key = c;
}

