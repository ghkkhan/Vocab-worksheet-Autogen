/* 
 * This file is used for the creation of the Kanji study sheets...
 * Therefore, this code is largely irrelevant to this program... for now.
*/

#include <iostream>
#include <fstream>

using namespace std;
int main(int argc, char * argv[]) {

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

    // create the tex file to be used. same name as source file, just with a tex extension
    ofstream ofs(filename + ".tex");

    // adds some headers to the tex file...
    ofs << "\\documentclass{article}\n";
    ofs << "\\usepackage{array}\n";
    ofs << "\\usepackage{multirow}\n";
    ofs << "\\usepackage{CJKutf8}\n";
    ofs << "\\usepackage[overlap, CJK]{ruby}\n";
    ofs << "\\usepackage{CJKulem}\n";
    ofs << "\\renewcommand{\\rubysep}{-0.1ex}";

    ofs << "\\def\\arraystretch{3}%\n";

    // get date from the input file and add it to the tex file's title
    getline(ifs, line);
    ofs << "\\title{Kanji Practice Sheet \\{ " + line +" \\}}\n";

    // some more preliminary for the tex file...
    ofs << "\\begin{document}\n";
    ofs << "\\maketitle\n";
    ofs << "\\begin{CJK}{UTF8}{min}\n";
    ofs << "\\begin{center}\n";

    //this is where the main loop begins, going through the file and adding into the tex file simultaneously

    for (int i = 0; i < count; i++) {

        ofs << "\\begin{tabular}{| p{2.5cm} | p{10cm} |}\n";
        ofs << "\\hline\n";
        ofs << "\\begin{tabular}{c}\n";

        getline(ifs, line); // First line contains the kanji
        ofs << "{\\Huge " + line + "} \\\\ \n";
        ofs << "\\hline\n";
        
        getline(ifs, line); // gets the number of meanings...
        int num = stoi(line);
        for (int j = 0; j < num; j++) { // adds the meanings to the texfile
            getline(ifs,line);
            ofs << line + "\\\\\n";
        }
        // One tabular ends and another begins...
        ofs << "\\end{tabular}\n";
        ofs << "&\\begin{tabular}{l}\n";
        // now we number of examples, followed by the examples themselves...
        getline(ifs, line);
        num = stoi(line);
        for (int j = 0; j < num; j++) {
            // each example consists of a kanji compound, followed by reading,\
             and then definition all in separate lines...
            getline(ifs, line); // contains the kanji...
            ofs << "{\\large \\ruby{"+line+"}";
            getline(ifs,line); // get the furigana line...
            ofs << "{" + line+ "}}";
            getline(ifs, line); // this line is the defintion itself...
            ofs << line + "\\\\ \n";
        }
        getline(ifs, line); // an extra space to separate the kanji blocks... more readable source file...
        ofs << "\\end{tabular} \\\\ \n";
        ofs << "\\hline\n";
        ofs << "\\end{tabular}\n";
    }
    // the main loop has ended... just adding some closing brackets...
    ofs << "\\end{center}\n";
    ofs << "\\end{CJK}\n";
    ofs << "\\end{document}";
    ifs.close();
    ofs.close();
}