//
// Created by Zdenek Brabec on 28/12/2016.
//

#include "LinkedList.h"

LinkedList::LinkedList(int max_size) {
    this->max_size = max_size;
    this->states = new State*[max_size];
    this->index = 0;
}

void LinkedList::push(State *state) {
    //std::cout << "pushing state " << state->value << std::endl;
    if(index > max_size) {
        throw;
    }
    states[index] = state;
    index++;
}

State *LinkedList::pop() {
    if(index==0) {
        return nullptr;
    }

    index--;
    //std::cout << "poping: " << states[index]->value << std::endl;
    return states[index];
}

LinkedList::~LinkedList() {
    delete [] states;
}