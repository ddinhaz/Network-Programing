#include "game.h"

Game::Game() : window(nullptr), renderer(nullptr), isRunning(false), ballRect({ 0, 0, 20, 20 }), ballSpeedX(1), ballSpeedY(1), ballTexture(nullptr), player1Rect({ 0, 0, 20, 100 }), player2Rect({ 0, 0, 20, 100 }), playerSpeed(1) {}

Game::~Game() {}

bool Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            renderer = SDL_CreateRenderer(window, -1, 0);
            if (renderer) {
                isRunning = true;

                // Set initial position for the ball
                ballRect.x = (width - ballRect.w) / 2;
                ballRect.y = (height - ballRect.h) / 2;

                // Set initial positions for player 1 and player 2
                player1Rect.x = 20; // Adjust position as needed
                player1Rect.y = (height - player1Rect.h) / 2;
                player2Rect.x = width - player2Rect.w - 20; // Adjust position as needed
                player2Rect.y = (height - player2Rect.h) / 2;

                return true;
            }
        }
    }
    return false;
}

void Game::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        }
    }

    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    // Player 1 controls
    if (keyboardState[SDL_SCANCODE_W]) {
        player1Rect.y -= playerSpeed;
    }
    if (keyboardState[SDL_SCANCODE_S]) {
        player1Rect.y += playerSpeed;
    }

    // Player 2 controls
    if (keyboardState[SDL_SCANCODE_UP]) {
        player2Rect.y -= playerSpeed;
    }
    if (keyboardState[SDL_SCANCODE_DOWN]) {
        player2Rect.y += playerSpeed;
    }
}

void Game::Update() {
    // Update the ball's position
    ballRect.x += ballSpeedX;
    ballRect.y += ballSpeedY;

    // Ball collision with window boundaries
    if (ballRect.x < 0 || ballRect.x > 800 - ballRect.w) {
        ballSpeedX = -ballSpeedX;
    }
    if (ballRect.y < 0 || ballRect.y > 600 - ballRect.h) {
        ballSpeedY = -ballSpeedY;
    }

    if (ballRect.x < 0) {
        // Goal oleh player 2
        //player2Score++;
        // Reset posisi bola
        ballRect.x = (800 - ballRect.w) / 2;
        ballRect.y = (600 - ballRect.h) / 2;
        // Reset kecepatan bola
        ballSpeedX = 1;
    }

    if (ballRect.x > 800 - ballRect.w) {
        // Goal oleh player 1
        //player1Score++;
        // Reset posisi bola
        ballRect.x = (800 - ballRect.w) / 2;
        ballRect.y = (600 - ballRect.h) / 2;
        // Reset kecepatan bola
        ballSpeedX = 1;
    }

    // Check collision with players
    if (SDL_HasIntersection(&ballRect, &player1Rect) || SDL_HasIntersection(&ballRect, &player2Rect)) {
        ballSpeedX = -ballSpeedX; // Reverse direction on collision
    }
}

void Game::Render() {
    // Set background color to green (0, 128, 0)
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    SDL_RenderClear(renderer);

    // Render the ball as a black rectangle
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &ballRect);

    // Render player 1 (blue)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &player1Rect);

    // Render player 2 (red)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &player2Rect);



    SDL_RenderPresent(renderer);
}

void Game::Clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}