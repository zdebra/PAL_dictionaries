//
// Created by Zdenek Brabec on 28/12/2016.
//

#ifndef PAL6_LINKEDLIST_H
#define PAL6_LINKEDLIST_H

#import "State.h"

class LinkedList {
private:
    State **states;
    int max_size;
    int index; // index of next to be added
public:
    LinkedList(int max_size);
    void push(State *state);
    State* pop();
    ~LinkedList();
};


#endif //PAL6_LINKEDLIST_H
