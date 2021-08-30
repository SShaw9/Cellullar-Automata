#include <iostream>
#include <string>
#include "gen.h"
#include "ui.h"
#include "cellauto.h"


int main() {
    int bitlength = 8;
    int rows = 10;
    int cols = 50;
    std::vector<std::string> r = GenElemRules(bitlength);
    cout << r[127] << endl;
    //vector<int> rule = r[30];
    std::vector<int> rule = {1,1,1,1,1,1,1,0};

    std::string start = "Cellular Automaton Running";
    printf("%s\n", start.c_str());

    CellAuto cellauto(50, 100, rule);
    cellauto.StartAutomaton();
    return 0;
}


