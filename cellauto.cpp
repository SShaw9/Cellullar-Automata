#include <iostream>
#include <vector>
#include <unistd.h>
#include "cellauto.h"

using namespace std;

map<int, vector<int>> CellAuto::GenElemRuleMap()
{
    map<int, vector<int>> rule_map;
    map<int, vector<int>>::iterator itr = rule_map.begin();

    rule_map.insert(pair<int, vector<int>>(0, {1,1,1}));
    rule_map.insert(pair<int, vector<int>>(1, {1,1,0}));
    rule_map.insert(pair<int, vector<int>>(2, {1,0,1}));
    rule_map.insert(pair<int, vector<int>>(3, {1,0,0}));
    rule_map.insert(pair<int, vector<int>>(4, {0,1,1}));
    rule_map.insert(pair<int, vector<int>>(5, {0,1,0}));
    rule_map.insert(pair<int, vector<int>>(6, {0,0,1}));
    rule_map.insert(pair<int, vector<int>>(7, {0,0,0}));

    return rule_map;
}

void CellAuto::PrintRuleMap()
{
    map<int, vector<int>>::iterator itr = this->ca_map.begin();

    while (itr != this->ca_map.end())
    {
        int map_key = itr->first;
        int map_value0 = itr->second[0];
        int map_value1 = itr->second[1];
        int map_value2 = itr->second[2];
        cout << "Key: " << map_key << "     Rule: " << map_value0 << map_value1 << map_value2 << endl;

        itr ++;
    }
}

vector<int> CellAuto::InitFirstRowState(int cols)
{
    vector<int> init_row;
    int centre_idx;
    int c = cols;

    // check to see if column width is odd, if even then add one.
    if (cols%2 == 0)
    {
        cols = (cols + 1);
    }
    centre_idx = ((cols/2) + 1);

    // set centre cell of first row to black/1
    for(int i=0; i<=cols; i++)
    {
        if (i==(centre_idx-1))
        {
            init_row.push_back(1);
        }
        init_row.push_back(0);
    }

    return init_row;
}

vector<vector<int>> CellAuto::InitCellGrid(pair<int, int> grid_size)
{
    vector<vector<int>> grid;
    int rows = grid_size.first;
    int cols = grid_size.second;
    int centre_idx;

    if (cols%2 == 0)
    {
        cols = (cols + 1);
    }
    centre_idx = ((cols/2) + 1);
    vector<int> grid_row(cols, 0);
    vector<int> init_row(cols, 0);

    init_row[centre_idx-1] = 1;
    grid.push_back(init_row);
    for (int i=1; i<=rows; i++)
    {
        grid.push_back(grid_row);
    }

    return grid;
}

vector<int> CellAuto::GetPrevCellState(vector<int> prev_row, int idx)
{
    vector<int> state;
    vector<int> *pstate = &state;

    for (int i=0; i<=prev_row.size(); i++)
    {
        pstate->push_back(prev_row[(idx-1)]);
        pstate->push_back(prev_row[idx]);
        pstate->push_back(prev_row[(idx+1)]);
    }

    return state;
}

vector<int> CellAuto::UpdateRow(vector<int> prev_row, vector<int> row, map<int, vector<int>> rule_map)
{
    vector<int> rule = this->ca_rule;
    map<int, vector<int>>::iterator itr = rule_map.begin();
    int row_size = row.size();
    vector<int> new_row = row;

    for (int i=1; i<=row_size-1; i++)
    {
        vector<int> prev_state = GetPrevCellState(prev_row, i);
        for (int j=0; j<=rule.size(); j++)
        {
            if(rule[j] == 1)
            {
                vector<int> map_vect = rule_map.at(j);

                if(prev_state[0] == map_vect[0]
                    && prev_state[1] == map_vect[1]
                    && prev_state[2] == map_vect[2])
                {
                    new_row[i] = 1;
                }
            }
        }
    }
    return new_row;
}

void CellAuto::PrintGrid()
{
    for(vector<int> vect : this->ca_grid)
    {
        for(int v : vect)
        {
            cout << v;
        }
        cout << endl;
    }
}

void CellAuto::PrintRow(vector<int> row)
{
    for(int cell : row)
    {
        cout << cell;
    }
    cout << endl;
}

void CellAuto::StartAutomaton()
{
    int grid_length = this->ca_grid.size();

    for(int i=0; i<=grid_length; i++)
    {
        vector<int> row = this->ca_grid[i];
        PrintRow(row);
        vector<int> new_row = UpdateRow(this->ca_grid[i],
                                        this->ca_grid[i+1],
                                        this->ca_map);
        this->ca_grid[i+1] = new_row;
        sleep(1);
    }
}

