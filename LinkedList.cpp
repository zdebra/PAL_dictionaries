//
// Created by Zdenek Brabec on 28/12/2016.
//

#include <cstring>
#include "LinkedList.h"

LinkedList::LinkedList(int max_size) {
    this->max_size = max_size;
    this->states = new int[max_size];
    this->index = 0;
}

void LinkedList::push(int state) {
    if(index > max_size) {
        throw;
    }
    states[index] = state;
    index++;
}

int LinkedList::pop() {
    if(index==0) {
        return -1;
    }

    index--;
    return states[index];
}

LinkedList::~LinkedList() {
    delete [] states;
}

void LinkedList::clear() {
    index = 0;
}

void LinkedList::copy(int *new_states, int i) {
    memcpy(states, new_states, max_size);
    index = i;
}

int *LinkedList::get_states() {
    return states;
}

int LinkedList::get_index() {
    return index;
}
