#include <iostream>
#include <vector>
#include <algorithm>
#include "./../includes/Databank.hpp"

struct Word {
    std::string word, definition;
    int cor, incor, icrat;
};

std::vector<std::string> select_vocab(std::vector<std::string> &, int);
bool comparator(Word a, Word b);
std::vector<Word> str_to_wrd(const std::vector<std::string> &);
std::vector<std::string> wrd_to_str(const std::vector<Word> &);