#pragma once
#ifndef Game_hpp
#define Game_hpp

#include "SDL.h"
#include <iostream>

using namespace std;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

private:
	bool isRunning;
	int cnt = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;


};

#endif // !game_h
