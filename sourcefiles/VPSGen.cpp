#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int main(int argc, char * argv[]) {
    vector<string> words;
    if (argc < 2) {
        cerr << "missing file name. Use: ./KPSGen /path/to/file" << endl;
        return 1;
    }
    string filename = argv[1];
    ifstream ifs;
    ifs.open(filename);
    if (!ifs.is_open()) {
        cerr << "File could not be opened. Please check file name and try again :)" << endl;
        return 1;
    }

    // get number of kanjis in the file...
    string line;
    getline(ifs, line);
    int count = stoi(line);
    string setNumber;
    // create the tex file to be used. same name as source file, just with a tex extension
    ofstream ofs(filename + ".tex");

    // adds some headers to the tex file...
    ofs << "\\documentclass{article}\n";
    ofs << "\\usepackage{array}\n";
    ofs << "\\usepackage[a4paper, left=2cm, right=2cm, top=2.5cm, bottom=2.5cm]{geometry}";
    ofs << "\\usepackage{CJKutf8}\n";
    ofs << "\\usepackage[overlap, CJK]{ruby}\n";
    ofs << "\\usepackage{CJKulem}\n";
    ofs << "\\renewcommand{\\rubysep}{-0.1ex}";

    ofs << "\\def\\arraystretch{2}%\n";

    // get date from the input file and add it to the tex file's title
    getline(ifs, line);
    setNumber = line;
    ofs << "\\title{Vocab Practice Sheet \\{ " + setNumber +" \\}}\n";

    // some more preliminary for the tex file...
    ofs << "\\begin{document}\n";
    ofs << "\\maketitle\n";
    ofs << "\\begin{CJK}{UTF8}{min}\n";
    ofs << "\\begin{center}\n";

    string word, def;

    //this is where the main loop begins, going through the file and adding into the tex file simultaneously
    for (int i = 0; i < count; i++) {
        getline(ifs, line);
		size_t ocr = line.find(" ");
		word = line.substr(0, ocr);
		def = line.substr(ocr + 1);
		words.push_back(def);
		
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
    ifs.close();

    ofstream tfs(filename + "_test.tex");
    tfs << "\\documentclass{article}\n";
    tfs << "\\usepackage{array}\n";
    tfs << "\\usepackage[a4paper, left=2cm, right=2cm, top=2.5cm, bottom=2.5cm]{geometry}";
    tfs << "\\usepackage{CJKutf8}\n";
    tfs << "\\usepackage[overlap, CJK]{ruby}\n";
    tfs << "\\usepackage{CJKulem}\n";
    tfs << "\\renewcommand{\\rubysep}{-0.1ex}";

    tfs << "\\def\\arraystretch{3}%\n";

   // get date from the input file and add it to the tex file's title
    tfs << "\\title{Vocab Test Sheet \\{ " + setNumber +" \\}}\n";

    // some more preliminary for the tex file...
    tfs << "\\begin{document}\n";
    tfs << "\\maketitle\n";
    tfs << "\\begin{CJK}{UTF8}{min}\n";
    tfs << "\\begin{center}\n";
    tfs << "{\\Large Fill in the blanks with the corresponding Kanji/Hiragana/Katakana}";
    tfs << "\\end{center}\n";

    tfs << "\\hrulefill \\\\ \\\\\n";
    for(int i = 0; i < words.size(); i++){
        tfs << "{\\Large " + to_string(i + 1) +". " +words[i]+": } \\hrulefill \\\\\n";
    }
    //close tex file and exit..
    tfs << "\\end{CJK}\n";
    tfs << "\\end{document}";
    tfs.close();

}