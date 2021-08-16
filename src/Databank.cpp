#include "./../includes/Databank.hpp"

int DataBank::addVocabSet(const std::string & set_file_name) {
    std::ifstream ifs(set_file_name);
    std::ofstream ofs(data_file_name, std::ofstream::app);
    if (!ifs.is_open() || !ofs.is_open()) {
        std::cerr << "Error in opening file. Please try again." << std::endl;
        return 1;
    }

    std::string str, word, def;
    int num_of_words_added = 0;
    while ( std::getline(ifs, str) ) {
        word = getWord(str);
        def = getDefinition(str);
        // format for line is : "word", "definition", #ofTimesCorrect, #ofTimesIncorrect, Correct-Incorrect (CI) Ratio 
        str = "\"" + word + "\", \"" + def + "\", 0, 0, 0";
        ofs << str << std::endl;
        num_of_words_added++;
    }
    ofs.close();
    ifs.close();
    return num_of_words_added;
}

std::string DataBank::getWord(const std::string & s) {
    size_t ocr = s.find(" ");
    return s.substr(0, ocr); 
}

std::string DataBank::getDefinition(const std::string & s) {
    size_t ocr = s.find(" ");
    return s.substr(ocr + 1);
}

std::vector<std::string> DataBank::getAllData() {
    std::ifstream ifs (data_file_name, std::fstream::in);

    if (!ifs.is_open()) {
        std::cerr << "Error in opening file. Please try again." << std::endl;
        return {};
    }

    std::string str;
    std::vector < std::string > V;
    while ( std::getline(ifs, str) ) {
        V.push_back(str);
    }
    return V;
}


// int DataBank::updateScores(const std::string & results) {
//     return 0;
// // }

// int main() {
//     DataBank DB;
//     // DB.addVocabSet("set1");
//     std::vector < std::string > V = DB.getAllData();
//     if (V.empty()) {
//         std::cout << "V is empty... file didn't open" << std::endl;
//     }
//     else {
//         std::cout << V[0] << " - "<< V.size() << std::endl;
//     }
//     return 1;
// }
