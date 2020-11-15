#pragma once
#include <algorithm>

namespace constants {
	constexpr int sizeX{ 8 };
	constexpr int sizeY{ 5 };
	constexpr float epsilon{ 1. };
	constexpr int nbRoad{ (sizeX * (sizeY - 1)) + (sizeY * (sizeX - 1)) };
	constexpr int nbIntersection{ sizeX * sizeY };
	constexpr int nbCarMax{ 10 };
	constexpr float speedMax{ 0.02f };
	constexpr int timeMax{ 100 };//milisecond
	constexpr float distanceSecurity{ 0.1f };
	constexpr int SIZE{ 200 };
	constexpr int SCREEN_WIDTH{ (sizeX - 1) * SIZE + 10};
	constexpr int SCREEN_HEIGHT{ (sizeY - 1) * SIZE + 10};
	//if sizeX>1
	constexpr int ratioX{ /*1*/(SCREEN_WIDTH - 10) / (sizeX - 1)};
	//if sizeY>1
	constexpr int ratioY{ /*1*/(SCREEN_HEIGHT - 10) / (sizeY - 1) };
}