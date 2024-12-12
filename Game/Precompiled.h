#pragma once

//STL
#include <algorithm>
#include <string_view>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <functional>
#include <memory>
#include <assert.h>

//Data Structures
#include <array>
#include <vector>
#include <map>
#include <list>

//SFML
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

//Engine(custom)
#include "engine/core/NonOwnPtr.h"
#include "engine/core/EnableAsService.h"
#include "engine/core/ServiceLocator.h"

//Game
#include "game/LevelData.h"

constexpr int SCREEN_WIDTH = 1024;
constexpr int SCREEN_HEIGHT = 1024;
constexpr float GRAVITY = 0.60f;
constexpr int SCALE = 4;
constexpr float PLAYER_SPEED = 0.65f;
constexpr int LEVEL_HEIGHT = 16;
constexpr int LEVEL_WIDTH = 192;
constexpr int SCALED_LEVEL_WIDTH = LEVEL_WIDTH * SCALE * 16;
