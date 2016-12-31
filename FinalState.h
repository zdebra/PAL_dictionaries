//
// Created by Zdenek Brabec on 28/12/2016.
//

#ifndef PAL6_STATE_H
#define PAL6_STATE_H

#include "LinkedList.h"

struct FinalState {
    int word_length = 0;
    LinkedList *dictionaries;
};


#endif //PAL6_STATE_H
