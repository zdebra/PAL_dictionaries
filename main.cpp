#include <iostream>

int MAX_INPUT_SIZE = 3000000;

struct Dictionary {

    int words_count; // max 8000
    char** words[20];

};

int main() {

    char input[MAX_INPUT_SIZE];
    std::cin.getline(input, MAX_INPUT_SIZE);



    return 0;
}