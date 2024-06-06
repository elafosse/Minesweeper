#include "TextureManager.h"

map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(const string& textureName) {
    string filePath = "images/" + textureName + ".png";
    textures[textureName].loadFromFile(filePath);
}

sf::Texture &TextureManager::GetTexture(const string& textureName) {
    if (textures.find(textureName) == textures.end()) {
        LoadTexture(textureName);
    }
    return textures[textureName];
}

void TextureManager::Clear() {
    textures.clear();
}