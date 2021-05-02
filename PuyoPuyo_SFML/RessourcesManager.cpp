#include "RessourcesManager.h"

RessourcesManager* RessourcesManager::Instance = nullptr;

RessourcesManager::RessourcesManager()
{
	AllTexture.resize(TextureLabel::CountTexture);

	getTextureFromFile(TextureLabel::PuyoSpriteSheet, "Assets/PuyoSpriteSheet.png");


	AllFont.resize(FontLabel::CountFont);

	getFontFromFile(FontLabel::MLFont, "Assets/ML2.ttf");
}

void RessourcesManager::getTextureFromFile(int i, const char* str)
{
	sf::Texture* t = new sf::Texture;
	t->loadFromFile(str);
	t->setSmooth(true);
	AllTexture[i] = t;
}

void RessourcesManager::getFontFromFile(int i, const char* str)
{
	sf::Font* t = new sf::Font;
	t->loadFromFile(str);
	AllFont[i] = t;
}

RessourcesManager* RessourcesManager::getInstance()
{
	if (Instance == nullptr) {
		Instance = new RessourcesManager();
	}
	return Instance;
}

sf::Texture* RessourcesManager::getTexture(TextureLabel t)
{
	return AllTexture[t];
}

sf::Font* RessourcesManager::getFont(FontLabel f)
{
	return AllFont[f];
}