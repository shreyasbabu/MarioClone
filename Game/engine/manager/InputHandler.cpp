#include "Precompiled.h"

#include "InputHandler.h"

InputHandler::InputHandler(NonOwnPtr<sf::RenderWindow> window)
	:ISystem(window)
{
	ServiceLocator::instance().RegisterService(ServiceType::InputHandler, this);
}

InputHandler::~InputHandler()
{
	ServiceLocator::instance().UnregisterService(ServiceType::InputHandler);
}

void InputHandler::update(float deltaTime)
{
	if (mWindow.isNull())
	{
		return;
	}

	sf::Event inputEvent;
	while(mWindow->pollEvent(inputEvent))
	{
		if (inputEvent.type == sf::Event::Closed)
		{
			callExitGame();
			return;
		}
		if (inputEvent.type == sf::Event::KeyPressed)
		{
			_resolveInput(inputEvent.key.code, true);

		}
		else if (inputEvent.type == sf::Event::KeyReleased)
		{
			_resolveInput(inputEvent.key.code, false);
		}
	}
}

GameInput InputHandler::getKeyInput() const
{                   
    return mCurrentKeyInput;
}

void InputHandler::_resolveInput(sf::Keyboard::Key input, bool set)
{
	switch (input)
	{
		case sf::Keyboard::W:
			_setInputBits(GameInput::up, set);
			break;
		case sf::Keyboard::S:
			_setInputBits(GameInput::down, set);
			break;
		case sf::Keyboard::A:
			_setInputBits(GameInput::left, set);
			break;
		case sf::Keyboard::D:
			_setInputBits(GameInput::right, set);
			break;
		case sf::Keyboard::Space:
			_setInputBits(GameInput::jump, set);
			break;
		default:
			break;
	}
}

void InputHandler::_setInputBits(GameInput inputKey, bool set)
{
	if (set)
	{
		mCurrentKeyInput = static_cast<GameInput>(static_cast<int>(mCurrentKeyInput) | static_cast<int>(inputKey));
	}
	else
	{
		mCurrentKeyInput = static_cast<GameInput>(static_cast<int>(mCurrentKeyInput) & ~(static_cast<int>(inputKey)));
	}
}
