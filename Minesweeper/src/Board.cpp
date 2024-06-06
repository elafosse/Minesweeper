#include "Board.h"
#include <fstream>
#include <iostream>
#include <time.h>
using namespace std;

Board::Board() {
    debugOn = false;
    Reset();
}

Board::~Board() {
    delete[] tiles;
}

void Board::setBoardConfig() {
    fstream boardConfig("boards/config.cfg", ios_base::in);

    boardConfig >> this->rows;
    boardConfig >> this->columns;
    boardConfig >> this->numMines;
    mineFlagCounter = numMines;
    this->numTiles = columns * rows;
}

void Board::createTiles() {
    for (int i = 0; i < numTiles; i++) {
        Tile temp;
        tiles[i] = temp;
    }
}

void Board::loadBoard(const string& fileName) {
    fstream file(fileName, ios_base::binary | ios_base::in);

    char tile = 0;

    for (int i = 0; i < numTiles; i++) {
        file.read((char*)&tile, sizeof(tile));
        if (tile == '\r' || tile == '\n') {
            i--;
            continue;
        } else if (tile == '1') {
            tiles[i].setMine();
        }
    }
}

void Board::randomMines() {
    int mineCount = numMines, randMine;
    srand(time(NULL));

    while (mineCount != 0) {
        randMine = rand() % numTiles;
        if (!tiles[randMine].getIfMine()) {
            tiles[randMine].setMine();
            mineCount--;
        }
    }
}

void Board::setAdjacentTiles() {
    for (int i = 0; i < numTiles; i++) {

        if (i == 0) {
            tiles[i].addAdjacentTile(&tiles[i + 1]); //nth col
            tiles[i].addAdjacentTile(&tiles[i + rows]);
            tiles[i].addAdjacentTile(&tiles[i + rows + 1]); //nth col
        } else if (i == (rows - 1)) {
            tiles[i].addAdjacentTile(&tiles[i - 1]); //1st col
            tiles[i].addAdjacentTile(&tiles[i + rows - 1]); //1st col
            tiles[i].addAdjacentTile(&tiles[i + rows]);
        } else if (i == (numTiles - rows)) {
            tiles[i].addAdjacentTile(&tiles[i - rows]); //1st row
            tiles[i].addAdjacentTile(&tiles[i - rows + 1]); //1st row
            tiles[i].addAdjacentTile(&tiles[i + 1]);
        } else if (i == (numTiles - 1)) {
            tiles[i].addAdjacentTile(&tiles[i - rows - 1]); //1st row
            tiles[i].addAdjacentTile(&tiles[i - rows]); //1st row
            tiles[i].addAdjacentTile(&tiles[i - 1]);
        }

        if (i < rows && i != 0 && i != (rows - 1)) { //1st col
            tiles[i].addAdjacentTile(&tiles[i - 1]);
            tiles[i].addAdjacentTile(&tiles[i + 1]);
            tiles[i].addAdjacentTile(&tiles[i + rows - 1]);
            tiles[i].addAdjacentTile(&tiles[i + rows]);
            tiles[i].addAdjacentTile(&tiles[i + rows + 1]);
        } else if (i > (numTiles - rows) && (i != (numTiles - 1))) { //nth col
            tiles[i].addAdjacentTile(&tiles[i - rows - 1]);
            tiles[i].addAdjacentTile(&tiles[i - rows]);
            tiles[i].addAdjacentTile(&tiles[i - rows + 1]);
            tiles[i].addAdjacentTile(&tiles[i - 1]);
            tiles[i].addAdjacentTile(&tiles[i + 1]);
        } else if (i % rows == 0 && i != 0 && i != (numTiles - rows)) { //1st row
            tiles[i].addAdjacentTile(&tiles[i - rows]);
            tiles[i].addAdjacentTile(&tiles[i - rows + 1]);
            tiles[i].addAdjacentTile(&tiles[i + 1]);
            tiles[i].addAdjacentTile(&tiles[i + rows]);
            tiles[i].addAdjacentTile(&tiles[i + rows + 1]);
        } else if (i % rows == (rows - 1) && i != (rows - 1) && i != (numTiles - 1)) { //nth row
            tiles[i].addAdjacentTile(&tiles[i - rows - 1]);
            tiles[i].addAdjacentTile(&tiles[i - rows]);
            tiles[i].addAdjacentTile(&tiles[i - 1]);
            tiles[i].addAdjacentTile(&tiles[i + rows - 1]);
            tiles[i].addAdjacentTile(&tiles[i + rows]);
        } else if (i != 0 && i != (rows - 1) && i != (numTiles - rows) && i != (numTiles - 1)) {
            tiles[i].addAdjacentTile(&tiles[i - rows - 1]);
            tiles[i].addAdjacentTile(&tiles[i - rows]);
            tiles[i].addAdjacentTile(&tiles[i - rows + 1]);
            tiles[i].addAdjacentTile(&tiles[i - 1]);
            tiles[i].addAdjacentTile(&tiles[i + 1]);
            tiles[i].addAdjacentTile(&tiles[i + rows - 1]);
            tiles[i].addAdjacentTile(&tiles[i + rows]);
            tiles[i].addAdjacentTile(&tiles[i + rows + 1]);
        }
    }
}

void Board::decrementFlagCounter() {
    mineFlagCounter--;
}

void Board::incrementFlagCounter() {
    mineFlagCounter++;
}

void Board::setCurrBoardName(const string& board) {
    this->boardName = board;
}

void Board::Reset() {
    mineFlagCounter = 0;
    numMines = 0;
    numTiles = 0;
    columns = 0;
    rows = 0;

    setBoardConfig();

    tiles = new Tile[numTiles];

    //Set tiles
    createTiles();

    //Randomize Mines
    randomMines();

    //set adjacent tiles
    setAdjacentTiles();
}

void Board::Reset(const string& board) {
    mineFlagCounter = 0;
    numMines = 0;
    numTiles = 0;
    columns = 0;
    rows = 0;
    this->boardName = board;

    setBoardConfig();

    tiles = new Tile[numTiles];

    //Set tiles
    createTiles();

    //Load mines
    string boardLocation = "boards/" + board + ".brd";
    loadBoard(boardLocation);

    //set adjacent tiles
    setAdjacentTiles();

    //Set Mine Counter for named boards
    numMines = calcNumOfMines();
    mineFlagCounter = numMines;
}

int Board::getRows() const {
    return rows;
}

int Board::getColumns() const {
    return columns;
}

int Board::getNumTiles() const {
    return numTiles;
}

int Board::getMineFlagCounter() const {
    return mineFlagCounter;
}

int Board::calcNumOfMines() const {
    int num = 0;
    for (int i = 0; i < numTiles; i++) {
        if (tiles[i].getIfMine()) {
            num++;
        }
    }
    return num;
}

bool Board::allTilesClicked() {
    for (int i = 0; i < numTiles; i++) {
        if (!tiles[i].getIfMine() && !tiles[i].getIfClicked()) {
            return false;
        }
    }
    return true;
}

Tile& Board::getTile(int index) {
    Tile& indexTile = tiles[index];
    return indexTile;
}

bool Board::isDebugOn() const {
    return debugOn;
}

void Board::setDebugState(bool debugOn) {
    Board::debugOn = debugOn;
}
