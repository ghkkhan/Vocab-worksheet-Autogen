#include "./../includes/heap.hpp"

std::vector <std::string> select_vocab(std::vector <std::string> & allVocab, int selectNum) {

    auto words = str_to_wrd(allVocab);
    std::vector <Word> selectedWords;
    sort(words.begin(), words.end(), comparator);
    for (int i = 0; i < selectNum; i++) {
        selectedWords.push_back(words[i]);
    }
    return wrd_to_str(selectedWords);
}

bool comparator(Word a, Word b) {
    return (a.icrat < b.icrat);
}
std::vector<Word> str_to_wrd(const std::vector<std::string> & lines) {
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

std::vector <std::string> wrd_to_str(const std::vector<Word> & words) {
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