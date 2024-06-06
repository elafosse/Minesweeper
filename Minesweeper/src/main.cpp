#include <../lib/SFML/Graphics.hpp>
#include "Tile.h"
#include "Board.h"
#include "TextureManager.h"
using namespace std;

int main() {
    Board uno;

    ///Window Render
    sf::RenderWindow window(sf::VideoMode(uno.getRows() * 32, (uno.getColumns() * 32) + 88), "Minesweeper");

    ///Sprites
    sf::Sprite mine(TextureManager::GetTexture("mine"));
    sf::Sprite hiddenTile(TextureManager::GetTexture("tile_hidden"));
    sf::Sprite revealedTile(TextureManager::GetTexture("tile_revealed"));
    sf::Sprite one(TextureManager::GetTexture("number_1"));
    sf::Sprite two(TextureManager::GetTexture("number_2"));
    sf::Sprite three(TextureManager::GetTexture("number_3"));
    sf::Sprite four(TextureManager::GetTexture("number_4"));
    sf::Sprite five(TextureManager::GetTexture("number_5"));
    sf::Sprite six(TextureManager::GetTexture("number_6"));
    sf::Sprite seven(TextureManager::GetTexture("number_7"));
    sf::Sprite eight(TextureManager::GetTexture("number_8"));
    sf::Sprite flag(TextureManager::GetTexture("flag"));
    sf::Sprite happyFace(TextureManager::GetTexture("face_happy"));
    sf::Sprite winFace(TextureManager::GetTexture("face_win"));
    sf::Sprite loseFace(TextureManager::GetTexture("face_lose"));
    sf::Sprite flagCounter(TextureManager::GetTexture("digits"));
    sf::Sprite debug(TextureManager::GetTexture("debug"));
    sf::Sprite test1(TextureManager::GetTexture("test_1"));
    sf::Sprite test2(TextureManager::GetTexture("test_2"));
    sf::Sprite test3(TextureManager::GetTexture("test_3"));

    ///Array of Digits
    sf::Sprite digitArr[8];
    digitArr[0] = one;
    digitArr[1] = two;
    digitArr[2] = three;
    digitArr[3] = four;
    digitArr[4] = five;
    digitArr[5] = six;
    digitArr[6] = seven;
    digitArr[7] = eight;

    bool gameLost = false, gameWon = false;

    ///Event Loop
    while (window.isOpen())
    {
        sf::Event event{};
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (gameWon) { ///All Mines Flagged When Game Won
                for (int i = 0; i < uno.getNumTiles(); i++) {
                    if (uno.getTile(i).getIfMine() && !uno.getTile(i).getIfFlagged()) {
                        uno.getTile(i).toggleFlag();
                        uno.decrementFlagCounter();
                    }
                }
            }

            if ((gameWon || gameLost) && event.type == sf::Event::MouseButtonPressed) { ///End Game Button Use
                //Reset Button

                sf::Vector2f resetPos;
                if (gameWon) {
                    resetPos = winFace.getPosition();
                } else {
                    resetPos = loseFace.getPosition();
                }
                int xInt = mousePosition.x - resetPos.x;
                int yInt = mousePosition.y - resetPos.y;
                if (xInt > 0 && yInt > 0 && xInt <= 64 && yInt <= 64) {
                    gameLost = false;
                    gameWon = false;
                    uno.Reset();
                }

                //Tests
                auto test1Pos = test1.getPosition();
                auto test2Pos = test2.getPosition();
                auto test3Pos = test3.getPosition();

                xInt = mousePosition.x - test1Pos.x;
                yInt = mousePosition.y - test1Pos.y;
                if (xInt > 0 && yInt > 0 && xInt <= 64 && yInt <= 64) {
                    gameLost = false;
                    gameWon = false;
                    uno.setCurrBoardName("testboard1");
                    uno.Reset("testboard1");
                }

                xInt = mousePosition.x - test2Pos.x;
                yInt = mousePosition.y - test2Pos.y;
                if (xInt > 0 && yInt > 0 && xInt <= 64 && yInt <= 64) {
                    gameLost = false;
                    gameWon = false;
                    uno.setCurrBoardName("testboard2");
                    uno.Reset("testboard2");
                }

                xInt = mousePosition.x - test3Pos.x;
                yInt = mousePosition.y - test3Pos.y;
                if (xInt > 0 && yInt > 0 && xInt <= 64 && yInt <= 64) {
                    gameLost = false;
                    gameWon = false;
                    uno.setCurrBoardName("testboard3");
                    uno.Reset("testboard3");
                }


            }

            if (!gameWon && !gameLost && event.type == sf::Event::MouseButtonPressed) { ///Button Press
                //sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                int x = mousePosition.x;
                int y = mousePosition.y;
                int index = x / 32 + (y / 32 * uno.getRows());

                if (event.mouseButton.button == sf::Mouse::Right && !uno.getTile(index).getIfClicked()) { //Flag Tiles
                    uno.getTile(index).toggleFlag();
                    if (uno.getTile(index).getIfFlagged()) {
                        uno.decrementFlagCounter();
                    } else {
                        uno.incrementFlagCounter();
                    }
                }

                if (event.mouseButton.button == sf::Mouse::Left) { //Reveal Tiles
                    if (y / 32 < uno.getColumns()) {
                        if (!uno.getTile(index).getIfFlagged()) {
                            uno.getTile(index).clickTile();
                        }
                    } else {
                        //Reset Button
                        auto resetPos = happyFace.getPosition();
                        int xInt = x - resetPos.x;
                        int yInt = y - resetPos.y;
                        if (xInt > 0 && yInt > 0 && xInt <= 64 && yInt <= 64) {
                            gameLost = false;
                            gameWon = false;
                            uno.Reset();
                        }

                        //Debug Button
                        auto debugPos = debug.getPosition();
                        xInt = x - debugPos.x;
                        yInt = y - debugPos.y;
                        if (xInt > 0 && yInt > 0 && xInt <= 64 && yInt <= 64) {
                            if (!uno.isDebugOn()) {
                                uno.setDebugState(true);
                            } else {
                                uno.setDebugState(false);
                            }
                        }

                        //Test Buttons
                        auto test1Pos = test1.getPosition();
                        auto test2Pos = test2.getPosition();
                        auto test3Pos = test3.getPosition();

                        xInt = x - test1Pos.x;
                        yInt = y - test1Pos.y;
                        if (xInt > 0 && yInt > 0 && xInt <= 64 && yInt <= 64) {
                            uno.setCurrBoardName("testboard1");
                            uno.Reset("testboard1");
                        }

                        xInt = x - test2Pos.x;
                        yInt = y - test2Pos.y;
                        if (xInt > 0 && yInt > 0 && xInt <= 64 && yInt <= 64) {
                            uno.setCurrBoardName("testboard2");
                            uno.Reset("testboard2");
                        }

                        xInt = x - test3Pos.x;
                        yInt = y - test3Pos.y;
                        if (xInt > 0 && yInt > 0 && xInt <= 64 && yInt <= 64) {
                            uno.setCurrBoardName("testboard3");
                            uno.Reset("testboard3");
                        }
                    }
                }
            }
        }

        window.clear();

        ///Draw
        for (int i = 0, j = 0; i < uno.getNumTiles(); ++i) {
            if (i != 0 && i % uno.getRows() == 0) {
                j++;
            }
            float xPos = i % uno.getRows() * 32;
            float yPos = j % uno.getColumns() * 32;

            if (gameLost && uno.getTile(i).getIfMine()) {
                revealedTile.setPosition(xPos, yPos);
                window.draw(revealedTile);
                mine.setPosition(xPos, yPos);
                window.draw(mine);
            } else if (!uno.getTile(i).getIfClicked()) {  //NOT CLICKED
                hiddenTile.setPosition(xPos, yPos);
                window.draw(hiddenTile);
                if (gameWon && uno.getTile(i).getIfMine()) {
                    flag.setPosition(xPos, yPos);
                    window.draw(flag);
                }
                if (uno.getTile(i).getIfFlagged()) {
                    flag.setPosition(xPos, yPos);
                    window.draw(flag);
                }
                if (uno.isDebugOn() && uno.getTile(i).getIfMine()) {
                    mine.setPosition(xPos, yPos);
                    window.draw(mine);
                }
            } else { //CLICKED
                revealedTile.setPosition(xPos, yPos);
                window.draw(revealedTile);
                if (uno.getTile(i).getIfMine()) { //MINE
                    mine.setPosition(xPos, yPos);
                    window.draw(mine);
                    gameLost = true;
                } else if (uno.getTile(i).numOfAdjacentMines() > 0) { //NOT MINE
                    int adjacentMines = uno.getTile(i).numOfAdjacentMines();
                    digitArr[adjacentMines - 1].setPosition(xPos, yPos);
                    window.draw(digitArr[adjacentMines - 1]);
                }
            }
        }

        debug.setPosition(uno.getRows() * 32 - (8 * 32), uno.getColumns() * 32);
        window.draw(debug);

        test1.setPosition(uno.getRows() * 32 - (6 * 32), uno.getColumns() * 32);
        window.draw(test1);

        test2.setPosition(uno.getRows() * 32 - (4 * 32), uno.getColumns() * 32);
        window.draw(test2);

        test3.setPosition(uno.getRows() * 32 - (2 * 32), uno.getColumns() * 32);
        window.draw(test3);

        ////Lower Menu Options
        if (uno.allTilesClicked()) {
            gameWon = true;
            winFace.setPosition(uno.getRows() * 16 - 32, uno.getColumns() * 32);
            window.draw(winFace);
        } else if (gameLost) {
            loseFace.setPosition(uno.getRows() * 16 - 32, uno.getColumns() * 32);
            window.draw(loseFace);
        } else {
            happyFace.setPosition(uno.getRows() * 16 - 32, uno.getColumns() * 32);
            window.draw(happyFace);
        }

        string counter = to_string(uno.getMineFlagCounter());
        int offset = 0;
        if (uno.getMineFlagCounter() < 0) {
            sf::Rect<int> rect(210, 0, 21, 32);
            flagCounter.setTextureRect(rect);
            flagCounter.setPosition(offset, uno.getColumns() * 32);
            window.draw(flagCounter);
            offset += 21;
        }
        for (char digit : counter) {
            if (digit != '-') {
                int num = (int)digit - 48;
                sf::Rect<int> rect1(num * 21, 0, 21, 32);
                flagCounter.setTextureRect(rect1);
                flagCounter.setPosition(offset, uno.getColumns() * 32);
                window.draw(flagCounter);
                offset += 21;
            }
        }

        window.display();
    }

    TextureManager::Clear();

    return 0;
}