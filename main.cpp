#include <iostream>

const int MAX_INPUT_SIZE = 3000000;
const int WORD_SIZE = 20;

struct Occurrence {
    int position = 0;
    Occurrence *next = NULL;
};

struct Word {
    char *word;
    int length = 0;
    Occurrence *occurrence = NULL;
};

struct Dictionary {

    int words_count; // max 8000
    Word *words; // max 20*8000

};

void read_dictionaries(int dictionaries_count, Dictionary *dictionaries, char *input);
void cleanup(int dictionaries_count, Dictionary *dictionaries);
void find_occurrences(Word &word, char *input, int len);
bool is_alphabet(int ch);
bool is_same(Word &word, int pos, char *input);

int main() {

    char input[MAX_INPUT_SIZE];
    std::cin.getline(input, MAX_INPUT_SIZE);

    int dictionaries_count;
    std::cin >> dictionaries_count;
    Dictionary *dictionaries = new Dictionary[dictionaries_count];

    // reading dictionaries
    read_dictionaries(dictionaries_count, dictionaries, input);





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

void read_dictionaries(int dictionaries_count, Dictionary *dictionaries, char *input) {
    for(int i=0; i < dictionaries_count; i++) {

        int words_count;
        std::cin >> words_count;
        int ch = getchar();
        if(is_alphabet(ch)) {
            ungetc(ch, stdin);
        }

        dictionaries[i].words = new Word[words_count];
        dictionaries[i].words_count = words_count;
        for(int j=0;j<words_count;j++) {
            dictionaries[i].words[j].word = new char[WORD_SIZE];

            while(is_alphabet(dictionaries[i].words[j].word[dictionaries[i].words[j].length]= (char) getchar())) {
                dictionaries[i].words[j].length++;
            }

            find_occurrences(dictionaries[i].words[j], input, MAX_INPUT_SIZE);

           /* std::cout << dictionaries[i].words[j].word << ", " << dictionaries[i].words[j].length << ", ";
            Word word = dictionaries[i].words[j];
            Occurrence *cur = dictionaries[i].words[j].occurrence;
            while(cur != NULL) {
                std::cout << cur->position << ", ";
                cur = cur->next;
            }
            std::cout << std::endl;
            */
        }


    }
}

void find_occurrences(Word &word, char *input, int len) {

    Occurrence *cur = NULL;
    int i = word.length-1;
    while(is_alphabet(input[i]) && i < len) {
        if(is_same(word, i, input)) {
            // set occurrence
            if(cur == NULL) {
                cur = new Occurrence;
                cur->position = i+1-word.length;
                word.occurrence = cur;
            } else {
                cur->next = new Occurrence;
                cur = cur->next;
                cur->position = i+1-word.length;
            }
        }
        i++;
    }

}

bool is_same(Word &word, int pos, char *input) {
    for(int j= word.length - 1; j >= 0; j--) {
        if(word.word[j] != input[pos-word.length+1+j]) {
            return false;
        }
    }
    return true;
}

bool is_alphabet(int ch) {
    return ch > 96 && ch < 123;
}