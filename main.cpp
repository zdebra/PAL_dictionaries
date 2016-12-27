#include <iostream>

const int MAX_INPUT_SIZE = 3000000;
const int WORD_SIZE = 20;
int MIN_LEN = MAX_INPUT_SIZE;
int dictionaries_count;

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

Dictionary *dictionaries;

void read_dictionaries(int dictionaries_count, Dictionary *dictionaries, char *input);
void cleanup(int dictionaries_count, Dictionary *dictionaries);
void find_occurrences(Word &word, char *input, int len);
bool is_alphabet(int ch);
bool is_same(Word &word, int pos, char *input);
void create_combination(int dictionary, int start, int length);

int main() {

    char input[MAX_INPUT_SIZE];
    std::cin.getline(input, MAX_INPUT_SIZE);

    std::cin >> dictionaries_count;
    dictionaries = new Dictionary[dictionaries_count];

    // reading dictionaries
    read_dictionaries(dictionaries_count, dictionaries, input);

    // start recursion for each word occurrence in first dictionary
    for(int i=0; i<dictionaries[0].words_count; i++) {
        Occurrence *cur = dictionaries[0].words[i].occurrence;
        while(cur!=NULL) {
            create_combination(1, cur->position, dictionaries[0].words[i].length);
            cur = cur->next;
        }
    }

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

void create_combination(int dictionary, int start, int length) {

    for(int i=0; i<dictionaries[dictionary].words_count;i++) {
        Occurrence *cur = dictionaries[dictionary].words[i].occurrence;
        int w_len = dictionaries[dictionary].words[i].length;
        while(cur!=NULL) {
            int w_start = cur->position;

            // add it
            if(start > w_start + w_len) {
                // the word is before substring
                int new_len = length + (start-w_start);
                if(new_len > MIN_LEN) {
                    return;
                }
                create_combination(dictionary+1, w_start, new_len);
            }

            else if(start > w_start && start < (w_start+w_len)) {

                int new_len = length + (start-w_start);
                if(new_len > MIN_LEN) {
                    return;
                }
                create_combination(dictionary+1, w_start, new_len);

            }

            else if(start <= w_start && )

            cur = cur->next;
        }
    }



    if(dictionary == dictionaries_count-1) {


    }

}
