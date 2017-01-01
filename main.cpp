#include <iostream>
#include "LinkedList.h"
#include "FinalState.h"
#include "Dictionary.h"

const int MAX_INPUT_SIZE = 3000000;
const int WORD_SIZE = 20;
const int MAX_DICTIONARY_SIZE = 8000;
const int ALPHABET_SIZE = 26;

bool is_alphabet(int ch);

void create_transition_table(int dictionaries_count, int **transition_table, FinalState *finalStates, int next_state);

void cleanup(int max_state_count, int *const *transition_table, const FinalState *finalStates,
             const Dictionary *dictionaries, const LinkedList *active, const LinkedList *new_states);

void process_automata(const char *input, int dictionaries_count, int max_state_count, int *const *transition_table,
                      const FinalState *finalStates, int &total_start, int &total_len, Dictionary *&dictionaries,
                      LinkedList *&active, LinkedList *&new_states);

void find_first_substring(int dictionaries_count, const FinalState *finalStates, Dictionary *const &dictionaries, int i,
                          int next, int &total_start, int &total_len, bool &all_dictionaries);

void find_best_substring(int dictionaries_count, const FinalState *finalStates, Dictionary *const &dictionaries, int i,
                         int next, int &total_start, int &total_len);

bool is_all_found(int dictionaries_count, Dictionary *const &dictionaries);

int main() {

    char input[MAX_INPUT_SIZE];
    scanf("%s\r\n", input);

    int dictionaries_count;
    scanf("%d\r\n", &dictionaries_count);

    int max_state_count = dictionaries_count * MAX_DICTIONARY_SIZE * WORD_SIZE;
    int **transition_table = new int *[max_state_count];
    transition_table[0] = new int[ALPHABET_SIZE]();
    FinalState *finalStates = new FinalState[max_state_count];
    int next_state = 1;

    // reading the input, create the automata
    create_transition_table(dictionaries_count, transition_table, finalStates, next_state);
    int total_start = MAX_INPUT_SIZE - 1;
    int total_len = MAX_INPUT_SIZE;
    Dictionary *dictionaries;
    LinkedList *active;
    LinkedList *new_states;

    process_automata(input, dictionaries_count, max_state_count, transition_table, finalStates, total_start, total_len,
                     dictionaries, active,
                     new_states);

    std::cout << total_start << std::endl;
    std::cout << total_len << std::endl;

    // cleanup
    cleanup(max_state_count, transition_table, finalStates, dictionaries, active, new_states);

    return 0;
}

void process_automata(const char *input, int dictionaries_count, int max_state_count, int *const *transition_table,
                      const FinalState *finalStates, int &total_start, int &total_len, Dictionary *&dictionaries,
                      LinkedList *&active, LinkedList *&new_states) {

    dictionaries = new Dictionary[dictionaries_count]();
    active = new LinkedList(max_state_count);
    new_states = new LinkedList(max_state_count);
    int i = 0;
    bool all_dictionaries = false;
    while (is_alphabet(input[i])) {
        active->push(0);
        // for each active state try to move forward
        int state;
        while ((state = active->pop()) != -1) {

            int next = transition_table[state][input[i] - 97];
            if (next != 0) {
                // it has next state - add to the next states
                new_states->push(next);

                // check if it is a final state
                if (finalStates[next].word_length > 0) {

                    if (!all_dictionaries) {

                        find_first_substring(dictionaries_count, finalStates, dictionaries, i, next, total_start,
                                             total_len, all_dictionaries);

                    } else {

                        find_best_substring(dictionaries_count, finalStates, dictionaries, i, next, total_start,
                                            total_len);

                    }


                }

            }

        }

        // copy new states
        active->clear();
        int cur;
        while ((cur = new_states->pop()) != -1) {
            active->push(cur);
        }

        i++;
    }

}

void find_best_substring(int dictionaries_count, const FinalState *finalStates, Dictionary *const &dictionaries, int i,
                         int next, int &total_start,
                         int &total_len) {

    // add it to dictionary as a last found word (the word could be in more dictionaries)
    for (int j = 0; j < finalStates[next].dictionaries->get_index(); j++) {
        int d = finalStates[next].dictionaries->get_states()[j];

        if ((i+1-finalStates[next].word_length) > dictionaries[d].start_index) {
            dictionaries[d].end_index = i;
            dictionaries[d].start_index = i + 1 - finalStates[next].word_length;

        }
    }

    // find min and max indexes
    int cur_min_index = MAX_INPUT_SIZE-1;
    int cur_max_index = 0;
    for(int j=0;j<dictionaries_count;j++) {
        cur_min_index = (dictionaries[j].start_index < cur_min_index) ? dictionaries[j].start_index : cur_min_index;
        cur_max_index = (dictionaries[j].end_index > cur_max_index) ? dictionaries[j].end_index : cur_max_index;
    }

    // check if it doesn't create a new minimum substring
    int possible_new_total_len = cur_max_index - cur_min_index + 1;
    if (possible_new_total_len < total_len) {
        total_len = possible_new_total_len;
        total_start = cur_min_index;
    }

}

void find_first_substring(int dictionaries_count, const FinalState *finalStates, Dictionary *const &dictionaries, int i,
                          int next, int &total_start, int &total_len, bool &all_dictionaries) {
    // note all dictionaries containing this word
    for (int j = 0; j < finalStates[next].dictionaries->get_index(); j++) {

        int d = finalStates[next].dictionaries->get_states()[j];

        if (!dictionaries[d].word_found || (i+1-finalStates[next].word_length) > dictionaries[d].start_index) {
            dictionaries[d].word_found = true;
            dictionaries[d].end_index = i;
            dictionaries[d].start_index = i + 1 - finalStates[next].word_length;
        }

    }

    // check if word for all dictionaries was found
    all_dictionaries = is_all_found(dictionaries_count, dictionaries);

    // set totals
    if (all_dictionaries) {
        // total_start is min of all (last found) words from all dictionaries
        for (int j = 0; j < dictionaries_count; j++) {
            if (dictionaries[j].start_index < total_start) {
                total_start = dictionaries[j].start_index;
            }
        }
        total_len = i - total_start + 1;
    }
}

bool is_all_found(int dictionaries_count, Dictionary *const &dictionaries) {
    for(int j=0;j<dictionaries_count;j++) {
        if(!dictionaries[j].word_found) {
            return false;
        }
    }
    return true;
}

void cleanup(int max_state_count, int *const *transition_table, const FinalState *finalStates,
             const Dictionary *dictionaries, const LinkedList *active, const LinkedList *new_states) {

    for (int i = 0; i < max_state_count; i++) {
        delete[] transition_table[i];
    }

    delete[] transition_table;
    delete[] finalStates;
    delete[] dictionaries;
    delete active;
    delete new_states;

}

void create_transition_table(int dictionaries_count, int **transition_table, FinalState *finalStates, int next_state) {
    for (int i = 0; i < dictionaries_count; i++) {
        int words_count;
        scanf("%d\r\n", &words_count);

        for (int j = 0; j < words_count; j++) {

            char word[WORD_SIZE];
            scanf("%s\r\n", word);

            int cur_state = 0;
            int word_len = 0;
            while (is_alphabet(word[word_len])) {
                int ch_index = word[word_len] - 97;
                if (transition_table[cur_state][ch_index] == 0) {
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
            if (finalStates[cur_state].word_length == 0) {
                finalStates[cur_state].word_length = word_len;
                finalStates[cur_state].dictionaries = new LinkedList(dictionaries_count);
            }

            finalStates[cur_state].dictionaries->push(i);

        }

    }
}

bool is_alphabet(int ch) {
    return ch > 96 && ch < 123;
}