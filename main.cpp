#include <iostream>

int MAX_INPUT_SIZE = 3000000;

struct Dictionary {

    int words_count; // max 8000
    char** words; // max 20*8000

};

int main() {

    char input[MAX_INPUT_SIZE];
    std::cin.getline(input, MAX_INPUT_SIZE);

    int dictionaries_count;
    std::cin >> dictionaries_count;
    Dictionary *dictionaries = new Dictionary[dictionaries_count];

    std::cout << dictionaries_count << std::endl;

    // reading dictionaries
    for(int i=0; i<dictionaries_count; i++) {

        int words_count;
        std::cin >> words_count;
        std::cout << words_count << std::endl;

        dictionaries[i].words = new char*[words_count];
        dictionaries[i].words_count = words_count;
        for(int j=0;j<words_count;j++) {
            dictionaries[i].words[j] = new char[20];
            scanf("%s",dictionaries[i].words[j]);
            std::cout << dictionaries[i].words[j] << std::endl;
        }


    }





    // clean up
    for(int i=0;i<dictionaries_count;i++) {
        for(int j=0;j<dictionaries[i].words_count;j++) {
            delete [] dictionaries[i].words[j];
        }
    }

    delete [] dictionaries;

    return 0;
}