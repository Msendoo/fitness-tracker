#include <SDL2/SDL.h>
#include <iostream>

int initialMain(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 100;
const int BALL_SIZE = 10;
const int PADDLE_SPEED = 10;
const int BALL_SPEED = 5;

struct Paddle {
    int x, y;
};

struct Ball {
    int x, y;
    int velX, velY;
};

void movePaddle(Paddle &paddle, int direction) {
    paddle.y += direction * PADDLE_SPEED;
    if (paddle.y < 0) paddle.y = 0;
    if (paddle.y > SCREEN_HEIGHT - PADDLE_HEIGHT) paddle.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
}

void moveBall(Ball &ball, Paddle &leftPaddle, Paddle &rightPaddle) {
    ball.x += ball.velX;
    ball.y += ball.velY;

    if (ball.y <= 0 || ball.y >= SCREEN_HEIGHT - BALL_SIZE) {
        ball.velY = -ball.velY;
    }

    if ((ball.x <= leftPaddle.x + PADDLE_WIDTH && ball.y >= leftPaddle.y && ball.y <= leftPaddle.y + PADDLE_HEIGHT) ||
        (ball.x >= rightPaddle.x - BALL_SIZE && ball.y >= rightPaddle.y && ball.y <= rightPaddle.y + PADDLE_HEIGHT)) {
        ball.velX = -ball.velX;
    }

    if (ball.x < 0 || ball.x > SCREEN_WIDTH) {
        ball.x = SCREEN_WIDTH / 2;
        ball.y = SCREEN_HEIGHT / 2;
        ball.velX = BALL_SPEED * (ball.velX > 0 ? -1 : 1);
        ball.velY = BALL_SPEED * (ball.velY > 0 ? -1 : 1);
    }
}

void render(SDL_Renderer* renderer, Paddle &leftPaddle, Paddle &rightPaddle, Ball &ball) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect leftRect = { leftPaddle.x, leftPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT };
    SDL_Rect rightRect = { rightPaddle.x, rightPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT };
    SDL_Rect ballRect = { ball.x, ball.y, BALL_SIZE, BALL_SIZE };

    SDL_RenderFillRect(renderer, &leftRect);
    SDL_RenderFillRect(renderer, &rightRect);
    SDL_RenderFillRect(renderer, &ballRect);

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Paddle leftPaddle = { 10, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2 };
    Paddle rightPaddle = { SCREEN_WIDTH - 20, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2 };
    Ball ball = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, BALL_SPEED, BALL_SPEED };

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_W]) {
            movePaddle(leftPaddle, -1);
        }
        if (currentKeyStates[SDL_SCANCODE_S]) {
            movePaddle(leftPaddle, 1);
        }
        if (currentKeyStates[SDL_SCANCODE_UP]) {
            movePaddle(rightPaddle, -1);
        }
        if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            movePaddle(rightPaddle, 1);
        }

        moveBall(ball, leftPaddle, rightPaddle);
        render(renderer, leftPaddle, rightPaddle, ball);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}