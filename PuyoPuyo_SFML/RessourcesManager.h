#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

class RessourcesManager
{
public:
	enum TextureLabel
	{
		PuyoSpriteSheet,
		CountTexture
	};

	enum FontLabel
	{
		MLFont,
		CountFont
	};

private:

	std::vector<sf::Texture*> AllTexture;
	std::vector<sf::Font*> AllFont;

	static RessourcesManager* Instance;
	RessourcesManager();

	void getTextureFromFile(int, const char*);
	void getFontFromFile(int, const char*);

public:
	static RessourcesManager* getInstance();

	sf::Texture* getTexture(TextureLabel);
	sf::Font* getFont(FontLabel);
};

