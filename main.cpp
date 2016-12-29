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

    int **transition_table = new int*[dictionaries_count*MAX_DICTIONARY_SIZE*WORD_SIZE];
    transition_table[0] = new int[ALPHABET_SIZE]();
    FinalState *finalStates = new FinalState[dictionaries_count*MAX_DICTIONARY_SIZE*WORD_SIZE];
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

    std::cout << "Transition table" << std::endl;
    for(int i=0;i<next_state;i++) {
        std::cout << i << ": ";
        for(int j=0;j<ALPHABET_SIZE;j++) {
            if(transition_table[i][j] != 0) {
                std::cout << (char) (j + 97) << "("<< transition_table[i][j] <<")" << " ";
            }
            else {
                std::cout << " - ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "Final states" << std::endl;

    for(int i=0; i<next_state; i++) {
        std::cout << i << ": " << finalStates[i].word_length << std::endl;
    }



    // cleanup
    for(int i=0;i<dictionaries_count*MAX_DICTIONARY_SIZE*WORD_SIZE;i++) {
        delete [] transition_table[i];
    }

    delete [] transition_table;
    delete [] finalStates;
    delete [] dictionaries;

    return 0;
}


bool is_alphabet(int ch) {
    return ch > 96 && ch < 123;
}