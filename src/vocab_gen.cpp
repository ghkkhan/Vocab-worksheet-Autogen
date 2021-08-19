#include <iostream>
#include <fstream>
#include <string.h>
#include "./../includes/Databank.hpp"
#include "./../includes/WSGen.hpp"

#define AD "-a"
#define WS "-w"
#define TS "-t"
#define SC "-s"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Not enough arguments... please read documentation and try again ;)" << endl;
        return 1;
    }

    // Flags:
    bool ADD_FLAG, WORKSHEET_FLAG, TEST_FLAG,  SCORE_FLAG;
    ADD_FLAG = WORKSHEET_FLAG = TEST_FLAG = SCORE_FLAG = false;

    string set_file;
    int ws_set_size;

    argv++; argc--;
    while (argc > 0) {
        if (strcmp(argv[0], AD) == 0 && argc > 1) {
            // add option has been selected... look for a file name right after...
            ADD_FLAG = true;
            set_file = argv[1];
            argc -= 2;
            argv += 2;
        }
        else if (strcmp(argv[0], WS) == 0 && argc > 1) {
            WORKSHEET_FLAG = true;
            ws_set_size = stoi(argv[1]);
            argc -= 2;
            argv += 2;
        }
        else if (strcmp(argv[0], TS) == 0) {
            TEST_FLAG = true;
            argv++; argc--;
        }
        else if ( strcmp(argv[0], SC) == 0 ) {
            SCORE_FLAG = true;
            argv++; argc--;
        }
        else {
            argv++; argc--;
        }
    }
    if (SCORE_FLAG && (WORKSHEET_FLAG || TEST_FLAG)) {
        cout << "Wrong combination of options: DNC." <<endl;
        return 1;
    }

    DataBank DB;
    if (ADD_FLAG) {
        if (DB.addVocabSet(set_file) == 1) {
            cout << "Error; could not add data to file..." << endl;
            return 1;
        }
        else {
            cout << "The given file has been added to records." << endl;
        }
    }
    if (WORKSHEET_FLAG) {
        createPracticeSheet(DB, ws_set_size);
        cout << "making worksheet" << ws_set_size << endl;
    }
    if (TEST_FLAG) {
        createTestSheet();
        cout << "making testsheet" << endl;
    }
    if (SCORE_FLAG) {
        cout << "beginning scoring program. For each presented word, please enter 0 if answered correctly... and 1 if answered incorrectly" << endl;
        auto changes = begin_score();
        DB.updateScores(changes);
    }

    return 0;
}