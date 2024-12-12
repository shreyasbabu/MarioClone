#include "Precompiled.h"
#include "AssetManager.h"

AssetManager::AssetManager()
{
	ServiceLocator::instance().RegisterService(ServiceType::AssetManager, this);
    loadTextures();
    loadSounds();
	loadFonts();
}

AssetManager::~AssetManager()
{
	ServiceLocator::instance().UnregisterService(ServiceType::AssetManager);
}

NonOwnPtr<SpriteComponent> AssetManager::getImage(Asset::Image img)
{
    return &SpriteSheetList[img];
}

NonOwnPtr<SoundComponent> AssetManager::getSound(Asset::Sound sound)
{
    return &SoundList[sound];
}

NonOwnPtr<FontComponent> AssetManager::getFont(Asset::Font font)
{
	return &FontList[font];
}

void AssetManager::loadTextures()
{
    sf::Texture texture;

	texture.loadFromFile("./asset/sprite/mario2.png");
    SpriteSheetList.emplace(Asset::Image::mario, SpriteComponent(texture, sf::Vector2u(14,1)));

	texture.loadFromFile("./asset/sprite/tile.png");
    SpriteSheetList.emplace(Asset::Image::tile, SpriteComponent(texture, sf::Vector2u(32,28)));

    texture.loadFromFile("./asset/sprite/enemy.png");
    SpriteSheetList.emplace(Asset::Image::goomba, SpriteComponent(texture, sf::Vector2u(6,1)));

}

void AssetManager::loadSounds()
{
	sf::SoundBuffer mSoundBuffer;
	mSoundBuffer.loadFromFile("./asset/sound/background.wav");
	SoundList.emplace(Asset::Sound::background, (&mSoundBuffer));

	mSoundBuffer.loadFromFile("./asset/sound/coin.wav");
	SoundList.emplace(Asset::Sound::coin, (&mSoundBuffer));

	mSoundBuffer.loadFromFile("./asset/sound/die.wav");
	SoundList.emplace(Asset::Sound::die, (&mSoundBuffer));

	mSoundBuffer.loadFromFile("./asset/sound/gameover.wav");
	SoundList.emplace(Asset::Sound::gameover, (&mSoundBuffer));

	mSoundBuffer.loadFromFile("./asset/sound/jump.wav");
	SoundList.emplace(Asset::Sound::jump, (&mSoundBuffer));

	mSoundBuffer.loadFromFile("./asset/sound/stomp.wav");
	SoundList.emplace(Asset::Sound::stomp, (&mSoundBuffer));

	mSoundBuffer.loadFromFile("./asset/sound/win.wav");
	SoundList.emplace(Asset::Sound::win, &mSoundBuffer);
}

void AssetManager::loadFonts()
{
	sf::Font font;
	font.loadFromFile("./asset/font/emulogic.ttf");
	FontList.emplace(Asset::Font::HUD, &font);
}
