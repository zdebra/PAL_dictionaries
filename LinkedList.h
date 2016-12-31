//
// Created by Zdenek Brabec on 28/12/2016.
//

#ifndef PAL6_LINKEDLIST_H
#define PAL6_LINKEDLIST_H

class LinkedList {
private:
    int *states;
    int max_size;
    int index; // index of next to be added
public:
    LinkedList(int max_size);
    void push(int state);
    int pop();
    void clear();
    void copy(int* new_states, int i);
    int* get_states();
    int get_index();
    ~LinkedList();
};


#endif //PAL6_LINKEDLIST_H
