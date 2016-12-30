#include <iostream>
#include "LinkedList.h"
#include "FinalState.h"
#include "Dictionary.h"

const int MAX_INPUT_SIZE = 3000000;
const int WORD_SIZE = 20;
const int MAX_DICTIONARY_SIZE = 8000;
const int ALPHABET_SIZE = 26;

bool is_alphabet(int ch);

int main() {

    char input[MAX_INPUT_SIZE];
    std::cin.getline(input, MAX_INPUT_SIZE);

    int dictionaries_count;
    std::cin >> dictionaries_count;

    int max_state_count = dictionaries_count*MAX_DICTIONARY_SIZE*WORD_SIZE;
    int **transition_table = new int*[max_state_count];
    transition_table[0] = new int[ALPHABET_SIZE]();
    FinalState *finalStates = new FinalState[max_state_count];
    int next_state = 1;

    // reading the input, create the automata
    for(int i=0;i<dictionaries_count;i++) {
        int words_count;
        scanf("%d\n", &words_count);

        for(int j=0;j<words_count;j++) {
            int c;
            int cur_state = 0;
            int word_len = 0;
            while(is_alphabet(c = getchar())) {
                int ch_index = c - 97;
                if(transition_table[cur_state][ch_index] == 0) {
                    // create new state
                    transition_table[next_state] = new int[ALPHABET_SIZE]();
                    transition_table[cur_state][ch_index] = next_state;
                    cur_state = next_state;
                    next_state++;
                } else {
                    // climb to existing state
                    cur_state = transition_table[cur_state][ch_index];
                }
                word_len++;
            }
            // end of a word - setting a finish state
            if(finalStates[cur_state].word_length == 0) {
                finalStates[cur_state].word_length = word_len;
                finalStates[cur_state].dictionaries = new bool[dictionaries_count]();
            }

            finalStates[cur_state].dictionaries[i] = true;

        }

    }

    Dictionary *dictionaries = new Dictionary[dictionaries_count]();

    LinkedList *active = new LinkedList(max_state_count);
    LinkedList *new_states = new LinkedList(max_state_count);

    int i = 0;
    bool all_dictionaries = false;
    int total_start = MAX_INPUT_SIZE - 1;
    int total_len = MAX_INPUT_SIZE;
    while(is_alphabet(input[i])) {
        active->push(0);
        // for each active state try to move forward
        int state;
        while((state=active->pop()) != -1) {

            int next = transition_table[state][input[i]-97];
            if(next != 0) {
                // it has next state - add to the next states
                new_states->push(next);

                // check if it is a final state
                if(finalStates[next].word_length > 0) {

                    if(!all_dictionaries) {

                        all_dictionaries = true;
                        // note all dictionaries containing this word
                        for (int j = 0; j < dictionaries_count; j++) {
                            // find all dictionaries containing this word
                            if (finalStates[next].dictionaries[j]) {

                                if (!dictionaries[j].word_found || i > dictionaries[j].start_index) {
                                    dictionaries[j].word_found = true;
                                    dictionaries[j].end_index = i;
                                    dictionaries[j].start_index = i + 1 - finalStates[next].word_length;
                                }

                            }

                            // check if word for all dictionaries was found
                            if (!dictionaries[j].word_found) {
                                all_dictionaries = false;
                            }

                        }

                        // set totals
                        if(all_dictionaries) {
                            // total_start is min of all (last found) words from all dictionaries
                            for(int j=0;j<dictionaries_count;j++) {
                                if(dictionaries[j].start_index < total_start) {
                                    total_start = dictionaries[j].start_index;
                                }
                            }
                            total_len = i - total_start + 1;
                        }

                    } else {

                        // add it to dictionary as a last found word (the word could be in more dictionaries)
                        int possible_new_total_len = 0;
                        for(int j=0;j<dictionaries_count;j++) {
                            if(finalStates[next].dictionaries[j]) {
                                if (i > dictionaries[j].start_index) {
                                    dictionaries[j].start_index = i;
                                    dictionaries[j].end_index = i + finalStates[next].word_length;

                                }
                            }
                            possible_new_total_len += dictionaries[j].end_index - dictionaries[j].start_index + 1;
                        }

                        // check if it doesn't create a new minimum substring
                        if(possible_new_total_len < total_len) {
                            total_len = possible_new_total_len;
                            for(int j=0;j<dictionaries_count;j++) {
                                if(dictionaries[j].start_index < total_start) {
                                    total_start = dictionaries[j].start_index;
                                }
                            }
                        }

                    }


                }

            }

        }

        // copy new states
        // todo rewrite with memcopy
        active->clear();
        int cur;
        while((cur = new_states->pop()) != -1) {
            active->push(cur);
        }

        i++;
    }

    std::cout << total_start << std::endl;
    std::cout << total_len << std::endl;

    // cleanup
    for(int i=0;i<max_state_count;i++) {
        delete [] transition_table[i];
    }

    delete [] transition_table;
    delete [] finalStates;
    delete [] dictionaries;
    delete active;
    delete new_states;

    return 0;
}


bool is_alphabet(int ch) {
    return ch > 96 && ch < 123;
}