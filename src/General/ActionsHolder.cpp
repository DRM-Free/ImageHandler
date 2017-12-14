/*
 * ActionsHolder.cpp
 *
 *  Created on: 13 déc. 2017
 *      Author: anael
 */

#include "ActionsHolder.h"

ActionsHolder::ActionsHolder(
        std::tuple<std::string, std::string, std::function<bool()>> tuple) {
}

ActionsHolder::~ActionsHolder() {
}

std::pair<std::string, std::string> ActionsHolder::generateActionLabels() {
    return std::make_pair(std::get<0>(keyDescrAct), std::get<1>(keyDescrAct));
}
