#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>

class Game {
public:
    Game();
    ~Game();

    bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
    bool IsRunning() const { return isRunning; }


private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    SDL_Rect ballRect;
    float ballSpeedX;
    float ballSpeedY;;
    SDL_Texture* ballTexture;

    // Player 1 and Player 2
    SDL_Rect player1Rect;
    SDL_Rect player2Rect;
    int playerSpeed;

    int player1Score;
    int player2Score;

};

#endif // GAME_H
