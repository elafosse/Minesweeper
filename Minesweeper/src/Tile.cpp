#include "Tile.h"
using namespace std;

Tile::Tile() {
    Reset();
}

void Tile::clickTile() {
    isClicked = true;
    if (numOfAdjacentMines() == 0 && !isMine) {
        revealNonMines();
    }
}

void Tile::toggleFlag() {
    if(isFlagged) {
        isFlagged = false;
    } else {
        isFlagged = true;
    }
}

void Tile::setMine() {
    isMine = true;
}

void Tile::addAdjacentTile(Tile *tile) {
    adjacentTiles.push_back(tile);
}

void Tile::revealNonMines() {
    for (Tile* tile : adjacentTiles) {
        if (!tile->getIfMine() && !tile->isFlagged && !tile->isClicked) {
            tile->isClicked = true;
            if (tile->numOfAdjacentMines() == 0) {
                isClicked = true;
                tile->revealNonMines();
            }
        }
    }
}

void Tile::Reset() {
    isFlagged = false;
    isMine = false;
    isClicked = false;
}

bool Tile::getIfMine() const {
    return this->isMine;
}

bool Tile::getIfFlagged() const {
    return this->isFlagged;
}

bool Tile::getIfClicked() const {
    return this->isClicked;
}

int Tile::numOfAdjacentMines() {
    int num = 0;
    for (Tile* adjacent : adjacentTiles) {
        if (adjacent->getIfMine()) {
            num++;
        }
    }
    return num;
}
