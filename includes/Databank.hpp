#ifndef DATABANK
#define DATABANK 1

#include <vector>
#include <iostream>
#include <fstream>

class DataBank {
public:

    int initDatabank();
    int addVocabSet(const std::string & set_file_name);
    std::vector<std::string> getAllData();
    int updateScores(const std::string & results);

    // @TODO:
    // add support for multiple databank files
    // maybe accessing and editing singular entries in the databank...

private:
    const std::string data_file_name = "./databank/Data.csv";
};
#endif