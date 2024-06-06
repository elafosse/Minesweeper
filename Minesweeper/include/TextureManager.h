#pragma once
#include <../lib/SFML/Graphics.hpp>
#include <string>
using namespace std;

class TextureManager {
    static map<string, sf::Texture> textures;
    static void LoadTexture(const string& textureName);

public:
    static sf::Texture& GetTexture(const string& textureName);
    static void Clear();
};