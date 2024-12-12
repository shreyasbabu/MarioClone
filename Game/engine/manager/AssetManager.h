#pragma once

#include "engine/core/EnableAsService.h"

namespace Asset
{
	enum class Image
	{
		mario,
		goomba,
		tile
	};
	enum class Sound
	{
		background,
		win,
		gameover,
		die,
		jump,
		stomp,
		coin
	};

	enum class Font
	{
		HUD,
	};
}

struct SpriteComponent
{
public:
	SpriteComponent() = default;
	SpriteComponent(const sf::Texture& texture, sf::Vector2u number)
		: texture(texture)
		, numberOfImages(number)
		, spriteSize(texture.getSize().x / number.x, texture.getSize().y / number.y)
	{
	}
	sf::Texture texture;
	sf::Vector2u numberOfImages{ 0, 0 };
	sf::Vector2u spriteSize{ 0, 0 };
};

struct SoundComponent
{
public:
	SoundComponent() = default;

	SoundComponent(const NonOwnPtr<sf::SoundBuffer> soundBuffer)
		: mSoundBuffer(*soundBuffer)
	{
	}

	//std::variant<sf::Sound, sf::Music> mSound;
	sf::SoundBuffer mSoundBuffer;
};

struct FontComponent
{
public:
	FontComponent() = default;

	FontComponent(const NonOwnPtr<sf::Font> font)
		: mFont(*font)
	{
	}

	sf::Font mFont;
};


class AssetManager : public EnableAsService
{
public:
	AssetManager();
	~AssetManager();

	NonOwnPtr<SpriteComponent> getImage(Asset::Image img) override;
	NonOwnPtr<SoundComponent> getSound(Asset::Sound sound) override;
	NonOwnPtr<FontComponent> getFont(Asset::Font sound) override;

	void loadTextures();
	void loadSounds();
	void loadFonts();

private:
	std::map<Asset::Image, SpriteComponent> SpriteSheetList;
	std::map<Asset::Sound, SoundComponent> SoundList;
	std::map<Asset::Font, FontComponent> FontList;
};