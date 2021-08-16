#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "./../includes/Databank.hpp"
#include "./../includes/heap.hpp"



void createPracticeSheet(DataBank &, const int);
void createTestSheet();
std::string getWord(const std::string &);
std::string getDefinition(const std::string &);
