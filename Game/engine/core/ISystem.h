#pragma once

class ISystem
{
public:
	ISystem(NonOwnPtr<sf::RenderWindow> window)
		: mWindow(window)
	{
	}

	virtual ~ISystem() = default;

	bool shouldExitGame() const
	{
		return mExitGame;
	}

	void callExitGame()
	{
		mExitGame = true;
	}

	virtual void update(float deltaTime) = 0;

protected:
	NonOwnPtr<sf::RenderWindow> mWindow = nullptr;

private:
	bool mExitGame = false;
};

