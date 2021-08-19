#ifndef DATABANK
#define DATABANK 1

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>

struct Word {
    std::string word, definition;
    float cor, incor, icrat;
};


class DataBank {
public:

    int initDatabank();
    int addVocabSet(const std::string & set_file_name);

    int updateScores(std::vector<std::string> & results);
    
    std::vector<std::string> select_vocab(int);
    static bool comparator(Word a, Word b);
    
    static std::vector<Word> str_to_wrd(const std::vector<std::string> &);
    static std::vector<std::string> wrd_to_str(const std::vector<Word> &);
    static std::string get_db_word(const std::string & s);
    static std::string get_db_def(const std::string & s);

    // int checkReps(const std::string & word);
    
    // @TODO:
    // add support for multiple databank files
    // maybe accessing and editing singular entries in the databank...

private:
    const std::string data_file_name = "./Data.csv";
    std::vector<std::string> getAllData();
    std::string getWord(const std::string &);
    std::string getDefinition(const std::string &);
};
#endif