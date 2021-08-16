#include "./../includes/WSGen.hpp"


int main(int argc, char * argv[]) {
    if (argc < 2) {
        cerr << "missing file name. Use: './KPSGen.sh /path/to/file'" << endl;
    }

    string filename = argv[1];
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cerr << "File could not be opened. Please check the file name and try again :)" << endl;
        return 1;
    }

    vector<string> lines;
    string line;
    while (getline(ifs, line)) {
        lines.push_back(line);
    }

    createPracticeSheet(lines, filename);
    createTestSheet(lines, filename);
}

