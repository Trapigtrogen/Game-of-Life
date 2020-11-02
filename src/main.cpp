//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <list>
#include <algorithm>

// --------------------------------------------------------
//
// Window And Grid System Creation From:
// https://github.com/catsocks/sdl-grid/blob/master/main.c
//
// --------------------------------------------------------
    

int main( int argc, char* args[] )
{
    int grid_cell_size = 10;
    int grid_width = 100;
    int grid_height = 100;

    std::list<SDL_Rect> startNodes;
    std::list<SDL_Rect> playingNodes;

    // + 1 so that the last grid lines fit in the screen.
    int window_width = (grid_width * grid_cell_size) + 1;
    int window_height = (grid_height * grid_cell_size) + 1;

    // Place the grid cursor in the middle of the screen.
    SDL_Rect grid_cursor = {
        .x = (grid_width - 1) / 2 * grid_cell_size,
        .y = (grid_height - 1) / 2 * grid_cell_size,
        .w = grid_cell_size,
        .h = grid_cell_size,
    };

    // The cursor ghost is a cursor that always shows in the cell below the
    // mouse cursor.
    SDL_Rect grid_cursor_ghost = {grid_cursor.x, grid_cursor.y, grid_cell_size, grid_cell_size};

    // Colours
    SDL_Color grid_background = {22, 22, 22, 255}; // Barely Black
    SDL_Color grid_line_color = {44, 44, 44, 255}; // Dark grey
    SDL_Color grid_cursor_ghost_color = {44, 44, 44, 255};
    SDL_Color grid_cursor_color = {255, 255, 255, 255}; // White

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
                     SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window;
    SDL_Renderer *renderer;
    if (SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window,
                                    &renderer) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Create window and renderer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_SetWindowTitle(window, "Game of Life");

    SDL_bool quit = SDL_FALSE;
    SDL_bool mouse_active = SDL_FALSE;
    SDL_bool mouse_hover = SDL_FALSE;

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_MOUSEBUTTONDOWN: {
                grid_cursor.x = (event.motion.x / grid_cell_size) * grid_cell_size;
                grid_cursor.y = (event.motion.y / grid_cell_size) * grid_cell_size;
                std::list<SDL_Rect>::iterator rectFound = std::find_if(std::begin(startNodes), std::end(startNodes),
					[grid_cursor](const SDL_Rect rhs) {
					return (grid_cursor.x == rhs.x && grid_cursor.y == rhs.y);
				});
                if(rectFound == startNodes.end()) {
                    startNodes.push_back(grid_cursor);
                }
                else {
                    startNodes.erase(rectFound);
                }
            break; }

            case SDL_MOUSEMOTION:
                grid_cursor_ghost.x = (event.motion.x / grid_cell_size) * grid_cell_size;
                grid_cursor_ghost.y = (event.motion.y / grid_cell_size) * grid_cell_size;

                if (!mouse_active)
                    mouse_active = SDL_TRUE;
            break;

            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_ENTER && !mouse_hover)
                    mouse_hover = SDL_TRUE;
                else if (event.window.event == SDL_WINDOWEVENT_LEAVE && mouse_hover)
                    mouse_hover = SDL_FALSE;
            break;

            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_SPACE) {
                    printf("Start Simulation\n");
                    
                }
                else if(event.key.keysym.sym == SDLK_ESCAPE) {
                    printf("Stop Simulation\n");
                }
            break;

            case SDL_QUIT:
                quit = SDL_TRUE;
            break;
            }
        }

        // Draw grid background.
        SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g,
                               grid_background.b, grid_background.a);
        SDL_RenderClear(renderer);

        // Draw grid lines.
        SDL_SetRenderDrawColor(renderer, grid_line_color.r, grid_line_color.g,
                               grid_line_color.b, grid_line_color.a);

        for (int x = 0; x < 1 + grid_width * grid_cell_size;
             x += grid_cell_size) {
            SDL_RenderDrawLine(renderer, x, 0, x, window_height);
        }

        for (int y = 0; y < 1 + grid_height * grid_cell_size;
             y += grid_cell_size) {
            SDL_RenderDrawLine(renderer, 0, y, window_width, y);
        }

        // Draw grid ghost cursor.
        if (mouse_active && mouse_hover) {
            SDL_SetRenderDrawColor(renderer, grid_cursor_ghost_color.r,
                                   grid_cursor_ghost_color.g,
                                   grid_cursor_ghost_color.b,
                                   grid_cursor_ghost_color.a);
            SDL_RenderFillRect(renderer, &grid_cursor_ghost);
        }

        for(SDL_Rect rect : startNodes) {
            SDL_SetRenderDrawColor(renderer, grid_cursor_color.r,
                                   grid_cursor_color.g, grid_cursor_color.b,
                                   grid_cursor_color.a); 
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}