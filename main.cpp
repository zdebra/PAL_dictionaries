#include <iostream>
#include "LinkedList.h"

const int MAX_INPUT_SIZE = 3000000;
const int WORD_SIZE = 20;




bool is_alphabet(int ch);

int main() {

    char input[MAX_INPUT_SIZE];
    std::cin.getline(input, MAX_INPUT_SIZE);

    int dictionaries_count;
    std::cin >> dictionaries_count;

    for(int i=0;i<dictionaries_count;i++) {

    }



    return 0;
}


bool is_alphabet(int ch) {
    return ch > 96 && ch < 123;
}