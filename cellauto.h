//
// Created by sshaw on 29/08/2021.
//

#ifndef BITCELL_CELLAUTO_H
#define BITCELL_CELLAUTO_H

#endif //BITCELL_CELLAUTO_H
#include <vector>
#include <map>

using namespace std;

class CellAuto
{
public:
    pair<int, int> ca_size;
    vector<vector<int>> ca_grid;
    map<int, vector<int>> ca_map;
    vector<int> ca_rule;

    CellAuto(int rows, int cols, vector<int> rule)
    {
        ca_size.first = rows;
        ca_size.second = cols;
        ca_rule = rule;
        ca_map = GenElemRuleMap();
        ca_grid = InitCellGrid(ca_size);

    };

    map<int, vector<int>> GenElemRuleMap();
    void PrintRuleMap();
    vector<int> InitFirstRowState(int);
    vector<vector<int>> InitCellGrid(pair<int, int>);
    vector<int> GetPrevCellState(vector<int>, int);
    vector<int> UpdateRow(vector<int>, vector<int>, map<int, vector<int>>);
    void PrintGrid();
    void PrintRow(vector<int>);
    void StartAutomaton();

};