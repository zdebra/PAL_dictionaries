#include <iostream>

const int MAX_INPUT_SIZE = 3000000;
const int WORD_SIZE = 20;

struct Occurrence {
    int position = 0;
    Occurrence *next;
};

struct Word {
    char *word;
    Occurrence *occurrence;
};

struct Dictionary {

    int words_count; // max 8000
    Word *words; // max 20*8000
    //char** words; // max 20*8000

};

void read_dictionaries(int dictionaries_count, Dictionary *dictionaries);

void cleanup(int dictionaries_count, Dictionary *dictionaries);

int main() {

    char input[MAX_INPUT_SIZE];
    std::cin.getline(input, MAX_INPUT_SIZE);

    int dictionaries_count;
    std::cin >> dictionaries_count;
    Dictionary *dictionaries = new Dictionary[dictionaries_count];

    // reading dictionaries
    read_dictionaries(dictionaries_count, dictionaries);





    // clean up
    cleanup(dictionaries_count, dictionaries);

    delete [] dictionaries;

    return 0;
}

void cleanup(int dictionaries_count, Dictionary *dictionaries) {
    for(int i=0; i < dictionaries_count; i++) {
        for(int j=0;j<dictionaries[i].words_count;j++) {
            delete [] dictionaries[i].words[j].word;
        }
    }
}

void read_dictionaries(int dictionaries_count, Dictionary *dictionaries) {
    for(int i=0; i < dictionaries_count; i++) {

        int words_count;
        std::cin >> words_count;

        dictionaries[i].words = new Word[words_count];
        dictionaries[i].words_count = words_count;
        for(int j=0;j<words_count;j++) {
            dictionaries[i].words[j].word = new char[20];
            scanf("%s",dictionaries[i].words[j].word);
        }


    }
}