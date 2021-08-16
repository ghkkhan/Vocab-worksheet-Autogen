#include "./../includes/WSGen.hpp"

void createPracticeSheet(DataBank & DB, const int num_of_words) {
    
    std::vector <std::string> lines = DB.getAllData();
    // lines = select_vocab(lines, num_of_words);

    if (lines.empty()) {
        std::cerr << "list of vocab is empty ;(" << std::endl;
        return;
    }

    std::ofstream sofs("./temp/wstemplist.csv");
    for (size_t i = 0; i < lines.size(); i++) {
        sofs << lines[i] << std::endl;
    }
    sofs.close();

    std::ofstream ofs("worksheet.tex");

    // adds some headers to the tex file...
    ofs << "\\documentclass{article}\n";
    ofs << "\\usepackage{array}\n";
    ofs << "\\usepackage[a4paper, left=2cm, right=2cm, top=2.5cm, bottom=2.5cm]{geometry}";
    ofs << "\\usepackage{CJKutf8}\n";
    ofs << "\\usepackage[overlap, CJK]{ruby}\n";
    ofs << "\\usepackage{CJKulem}\n";
    ofs << "\\renewcommand{\\rubysep}{-0.1ex}";
    ofs << "\\def\\arraystretch{2}%\n";

    // get date from the lines vector and add it to the tex file's title
    ofs << "\\title{Vocab Practice Sheet \\{ " + std::to_string(num_of_words) + " \\}}\n";

    // some more preliminary for the tex file...
    ofs << "\\begin{document}\n";
    ofs << "\\maketitle\n";
    ofs << "\\begin{CJK}{UTF8}{min}\n";
    ofs << "\\begin{center}\n";


    std::string word, def;

    //this is where the main loop begins, going through the file and adding into the tex file simultaneously
    for (size_t i = 1; i < lines.size(); i++) {

        word = getWord(lines[i]);
        def = getDefinition(lines[i]);
		
		ofs << "\\begin{tabular}{|p{4.0cm}| p{2.5cm} | p{2.5cm}| p{2.5cm} | p{2.5cm} |}\n";
        ofs << "\\hline\n";

        ofs << word + " : " + def + " & & & & \\\\\n";
        ofs << "\\hline\n";
        ofs << " & & & & \\\\\n";
        ofs << "\\hline\n";

        ofs << "\\end{tabular}\n";
    }
    // the main loop has ended... just adding some closing brackets...
    ofs << "\\end{center}\n";
    ofs << "\\end{CJK}\n";
    ofs << "\\end{document}";
    ofs.close();
}

void createTestSheet() {

    std::ifstream sifs("./temp/wstemplist.csv");
    std::string line;
    std::vector <std::string> lines;
    while (std::getline(sifs, line)) {
        lines.push_back(line);
    }

    std::ofstream tfs("testsheet.tex");
    tfs << "\\documentclass{article}\n";
    tfs << "\\usepackage{array}\n";
    tfs << "\\usepackage[a4paper, left=2cm, right=2cm, top=2.5cm, bottom=2.5cm]{geometry}";
    tfs << "\\usepackage{CJKutf8}\n";
    tfs << "\\usepackage[overlap, CJK]{ruby}\n";
    tfs << "\\usepackage{CJKulem}\n";
    tfs << "\\renewcommand{\\rubysep}{-0.1ex}";

    tfs << "\\def\\arraystretch{3}%\n";

   // get date from the input file and add it to the tex file's title
    tfs << "\\title{Vocab Test Sheet \\{ " + std::to_string(lines.size()) +" \\}}\n";

    // some more preliminary for the tex file...
    tfs << "\\begin{document}\n";
    tfs << "\\maketitle\n";
    tfs << "\\begin{CJK}{UTF8}{min}\n";
    tfs << "\\begin{center}\n";
    tfs << "{\\Large Fill in the blanks with the corresponding Kanji/Hiragana/Katakana}";
    tfs << "\\end{center}\n";
    tfs << "\\hrulefill \\\\ \\\\\n";

    random_shuffle(lines.begin(), lines.end());     // shuffle the vector...

    srand(time(NULL));
    std::string word;
    for (size_t i = 0; i < lines.size(); i++){
        //toss a coin... randomize japanese and english...
        if(rand() % 100 < 50) word = getWord(lines[i]);
        else word = getDefinition(lines[i]);

        tfs << "{\\Large " + std::to_string(i + 1) +". " + word +": } \\hrulefill \\\\\n";
    }
    //close tex file and exit..
    tfs << "\\end{CJK}\n";
    tfs << "\\end{document}";
    tfs.close();
}

std::string getWord(const std::string & s) {
    size_t ocr = s.find("\""); // find first occurance of quotation mark
    ocr = s.find("\"", ocr + 1); // find second occurance of quotation mark
    return s.substr(0 + 1, ocr);
}
std::string getDefinition(const std::string & s) {
    size_t ocr1 = s.find("\"");
    size_t ocr2 = s.find("\"", ocr1 + 1);
    ocr1 = s.find("\"", ocr2 + 1);
    ocr2 = s.find("\"", ocr1 + 1);
    return s.substr(ocr1 + 1, ocr2 - (ocr1+1));
}
