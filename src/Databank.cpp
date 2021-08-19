#include "./../includes/Databank.hpp"
// #include "./../includes/heap.hpp"

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

int DataBank::updateScores(std::vector<std::string> & results) {
    std::vector<int> answers;
    for (size_t i = 0; i < results.size(); i++) {
        answers.push_back(results[i].back());
        results[i].pop_back();
    }

    auto words = str_to_wrd(results);
    for (size_t i = 0; i < words.size(); i++) {
        if (answers[i] == 0) { // correct answer:
            words[i].cor++;
            if (words[i].incor == 0) words[i].icrat = words[i].cor;
            else words[i].icrat = words[i].cor / words[i].incor;
        }
        else {
            words[i].incor++;
            words[i].icrat = words[i].cor / words[i].incor;
        }
    }

    auto res = wrd_to_str(words);

    // find the words in the main file and replace them with the updated ones... this will be left to the next generation...
    // NOT COMPLETE FUNCTION...
    return 0;
}

std::vector <std::string> DataBank::select_vocab(int selectNum) {
// std::vector <std::string> & allVocab
    std::vector <std::string> allVocab = getAllData();
    auto words = str_to_wrd(allVocab);
    std::vector <Word> selectedWords;
    sort(words.begin(), words.end(), comparator);
    for (int i = 0; i < selectNum; i++) {
        selectedWords.push_back(words[i]);
    }
    return wrd_to_str(selectedWords);
}

bool DataBank::comparator(Word a, Word b) {
    return (a.icrat < b.icrat);
}

// string extraction functions....
std::vector<Word> DataBank::str_to_wrd(const std::vector<std::string> & lines) {
    std::vector <Word> words;
    for (size_t i = 0; i < lines.size(); i++) {
        std::string s = lines[i];
        Word wrd;

        // find and extract word from the string...
        size_t ocr1 = s.find("\"");
        size_t ocr2 = s.find("\"", ocr1 + 1);
        wrd.word = s.substr(ocr1 + 1, ocr2 - (ocr1 + 1));

        //find and extract the definition from string...
        ocr1 = s.find("\"", ocr2 + 1);
        ocr2 = s.find("\"", ocr1 + 1);
        wrd.definition = s.substr(ocr1 + 1, ocr2 - (ocr1+1));

        ocr1 = s.find(",", ocr2 + 1);
        ocr2 = s.find(",", ocr1 + 1);
        wrd.cor = std::stoi(s.substr(ocr1 + 2, ocr2 - (ocr1 + 2)));

        ocr1 = ocr2;
        ocr2 = s.find(",", ocr1 + 1);
        wrd.incor = std::stoi(s.substr(ocr1 + 2, ocr2 - (ocr1 + 2)));
        
        ocr1 = ocr2;
        wrd.icrat = std::stoi(s.substr(ocr1 + 2));

        words.push_back(wrd);
    }
    return words;
}

std::vector<std::string> DataBank::wrd_to_str(const std::vector<Word> & words) {
    std::vector <std::string> lines;
    for (size_t i = 0; i < words.size(); i++) {
        std::string line = "";
        line += "\"" + words[i].word + "\", ";
        line += "\"" + words[i].definition+ "\", ";
        line += std::to_string(words[i].cor) + ", ";
        line += std::to_string(words[i].incor) + ", ";
        line += std::to_string(words[i].icrat) + "";
        lines.push_back(line);
    }
    return lines;
}

std::string DataBank::getWord(const std::string & s) {
    size_t ocr = s.find(" ");
    return s.substr(0, ocr); 
}

std::string DataBank::getDefinition(const std::string & s) {
    size_t ocr = s.find(" ");
    return s.substr(ocr + 1);
}
std::string DataBank::get_db_word(const std::string & s) {
    size_t ocr = s.find("\""); // find first occurance of quotation mark
    ocr = s.find("\"", ocr + 1); // find second occurance of quotation mark
    return s.substr(0 + 1, ocr - 1);
}
std::string DataBank::get_db_def(const std::string & s) {
    size_t ocr1 = s.find("\"");
    size_t ocr2 = s.find("\"", ocr1 + 1);
    ocr1 = s.find("\"", ocr2 + 1);
    ocr2 = s.find("\"", ocr1 + 1);
    return s.substr(ocr1 + 1, ocr2 - (ocr1+1));
}