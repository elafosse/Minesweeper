#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Tile {
    bool isMine, isFlagged, isClicked;
    vector<Tile*> adjacentTiles;

public:
    Tile();
    void clickTile();
    void toggleFlag();
    void setMine();
    void addAdjacentTile(Tile* tile);
    void revealNonMines();
    void Reset();
    bool getIfMine() const;
    bool getIfFlagged() const;
    bool getIfClicked() const;
    int numOfAdjacentMines();
};