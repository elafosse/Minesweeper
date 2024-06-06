#pragma once
#include "Tile.h"
#include <vector>
#include <iostream>
using namespace std;

class Board {
    int mineFlagCounter, numMines, numTiles, columns, rows;
    bool debugOn;
    string boardName;
    Tile* tiles;

public:
    Board();
    ~Board();
    void setBoardConfig();
    void createTiles();
    void loadBoard(const string& fileName);
    void randomMines();
    void setAdjacentTiles();
    void decrementFlagCounter();
    void incrementFlagCounter();
    void setCurrBoardName(const string& board);
    void Reset();
    void Reset(const string& board);
    int getRows() const;
    int getColumns() const;
    int getNumTiles() const;
    int getMineFlagCounter() const;
    int calcNumOfMines() const;
    bool allTilesClicked();
    void setDebugState(bool debugOn);
    bool isDebugOn() const;
    Tile& getTile(int index);
};