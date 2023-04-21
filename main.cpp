#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const int MAX_ITER = 100;

void hsvToRgb(float h, float s, float v, int *r, int *g, int *b) {
    int i = int(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);
    i %= 6;
    switch (i) {
        case 0:
            *r = v * 255, *g = t * 255, *b = p * 255;
            break;
        case 1:
            *r = q * 255, *g = v * 255, *b = p * 255;
            break;
        case 2:
            *r = p * 255, *g = v * 255, *b = t * 255;
            break;
        case 3:
            *r = p * 255, *g = q * 255, *b = v * 255;
            break;
        case 4:
            *r = t * 255, *g = p * 255, *b = v * 255;
            break;
        case 5:
            *r = v * 255, *g = p * 255, *b = q * 255;
            break;
    }
}

int julia(double real, double imag, double c_real, double c_imag) {
    double r = real, i = imag;
    for (int iter = 0; iter < MAX_ITER; iter++) {
        double r2 = r * r;
        double i2 = i * i;
        if (r2 + i2 > 4.0) {
            return iter;
        }
        i = 2 * r * i + c_imag;
        r = r2 - i2 + c_real;
    }
    return MAX_ITER;
}

int main(int argc, char *argv[]) {
    double input_real = argv[1] ? atof(argv[1]) : -0.7;
    double input_imag = argv[2] ? atof(argv[2]) : 0.27015;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    double offsetX = 0.0;
    double offsetY = 0.0;
    double zoom = 1.0;

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        offsetY += 0.1 / zoom;
                        break;
                    case SDLK_DOWN:
                        offsetY -= 0.1 / zoom;
                        break;
                    case SDLK_LEFT:
                        offsetX += 0.1 / zoom;
                        break;
                    case SDLK_RIGHT:
                        offsetX -= 0.1 / zoom;
                        break;
                    case SDLK_p:
                        zoom *= 1.1;
                        break;
                    case SDLK_m:
                        zoom /= 1.1;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                double real = offsetX + (x - WIDTH / 2.0) * 4.0 / (WIDTH * zoom);
                double imag = offsetY + (y - HEIGHT / 2.0) * 4.0 / (HEIGHT * zoom);

                double c_real = input_real;
                double c_imag = input_imag;

                int value = julia(real, imag, c_real, c_imag);
                float color = (float) value / MAX_ITER;

                int r, g, b;
                hsvToRgb(color, 1.0, value < MAX_ITER ? 1.0 : 0.0, &r, &g, &b);
                SDL_SetRenderDrawColor(renderer, r, g, b, 255);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}