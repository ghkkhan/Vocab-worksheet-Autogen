#ifndef DATABANK
#define DATABANK 1

#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

class DataBank {
public:

    int initDatabank();
    int addVocabSet(const std::string & set_file_name);
    std::vector<std::string> getAllData();

    // int updateScores(const std::vector<std::string> & results);
    // int checkReps(const std::string & word);
    
    // @TODO:
    // add support for multiple databank files
    // maybe accessing and editing singular entries in the databank...

private:
    const std::string data_file_name = "./Data.csv";
    std::string getWord(const std::string &);
    std::string getDefinition(const std::string &);

};
#endif