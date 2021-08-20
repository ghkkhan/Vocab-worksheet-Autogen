#include "./../includes/WSGen.hpp"

void createPracticeSheet(DataBank & DB, const int num_of_words) {
    
    // std::vector <std::string> lines = DB.getAllData();
    auto lines = DB.select_vocab(num_of_words);

    if (lines.empty()) {
        std::cerr << "list of vocab is empty ;(" << std::endl;
        return;
    }

    
    // check for existing temp folder
    

    std::ofstream sofs("./temp/wstemplist.csv");
    for (size_t i = 0; i < lines.size(); i++) {
        sofs << lines[i] << std::endl;
    }
    sofs.close();
    std::cout << lines.size() << std::endl;
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
    for (size_t i = 0; i < lines.size(); i++) {

        word = DataBank::get_db_word(lines[i]);
        def = DataBank::get_db_def(lines[i]);
		
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
    tfs << "\\usepackage{setspace}\n";
    tfs << "\\doublespace";

    tfs << "\\renewcommand{\\rubysep}{-0.1ex}";

    tfs << "\\def\\arraystretch{3}%\n";

   // get date from the input file and add it to the tex file's title
    tfs << "\\title{Vocab Test Sheet \\{ " + std::to_string(lines.size()) +" \\}}\n";

    // some more preliminary for the tex file...
    tfs << "\\begin{document}\n";
    tfs << "\\maketitle\n";
    tfs << "\\begin{CJK}{UTF8}{min}\n";

    tfs << "\\hrulefill \\\\ \\\\\n";
    random_shuffle(lines.begin(), lines.end());     // shuffle the vector...
    srand(time(NULL));
    std::string word;

    size_t half_lines = lines.size()/2;

    tfs << "{\\Large Fill in the blanks with the corresponding English translation.\\\\\n}";
    for (size_t i = 0; i < half_lines; i++){
        // japanese to english 
        word = DataBank::get_db_word(lines[i]);
        tfs << "{\\Large " + std::to_string(i + 1) +". " + word +": } \\hrulefill \\\\\n";
    }

    tfs << "{\\\\\n\\Large Fill in the blanks with the corresponding Kanji/Hiragana/Katakana.\\\\\n}";
    for (size_t i = half_lines; i < lines.size(); i++){
        // english to japanese
        word = DataBank::get_db_def(lines[i]);
        tfs << "{\\Large " + std::to_string(i + 1 - half_lines) +". " + word +": } \\hrulefill \\\\\n";
    }

    //close tex file and exit..
    tfs << "\\end{CJK}\n";
    tfs << "\\end{document}";
    tfs.close();
}

std::vector <std::string> begin_score() {
    std::ifstream sifs("./temp/wstemplist.csv");
    
    //ERROR CHECK if file is opened...
    std::string line;
    std::vector <std::string> lines;
    while (std::getline(sifs, line)) {
        lines.push_back(line);
    }

    for (size_t i = 0; i < lines.size(); i++) {
        lines[i] = get_score(lines[i]);
    }
    return lines;
}

std::string get_score(std::string s) {
    std::string word = DataBank::get_db_word(s);
    int b;
    std::cout << "Did you get this word correct: " << word <<"?"<< std::endl;
    std::cin >> b;
    // check if b is either 0 or 1... accept nothing other than 0 for correct and 1 for incorrect...

    return s + std::to_string(b);    
}