//
// Created by Zdenek Brabec on 28/12/2016.
//

#ifndef PAL6_STATE_H
#define PAL6_STATE_H

#include <iostream>

struct State {
    char value;
    State *next = NULL;
    int dictionary = -1; // -1 means it isn't exit state
};


#endif //PAL6_STATE_H
