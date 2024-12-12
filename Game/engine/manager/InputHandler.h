#pragma once

#include "engine/core/ISystem.h"

enum class GameInput : int
{
	none = 0,
	up = 1 << 0,
	down = 1 << 1,
	left = 1 << 2,
	right = 1 << 3,
	jump =  1 << 4
};

class InputHandler : public ISystem, public EnableAsService
{
public:
	InputHandler(NonOwnPtr<sf::RenderWindow> window);
	virtual ~InputHandler() override;

	void update(float deltaTime) override;
	GameInput getKeyInput() const override;

private:
	void _resolveInput(sf::Keyboard::Key input, bool set);
	void _setInputBits(GameInput inputKey, bool set);

	GameInput mCurrentKeyInput = GameInput::none;
};

