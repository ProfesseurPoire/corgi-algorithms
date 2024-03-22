#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <corgi/algorithms/graphs/dijkstra.h>
#include <corgi/math/vec2.h>
#include <corgi/opengl/renderer.h>
#include <glad/glad.h>

#include <bit>
#include <bitset>
#include <iostream>

using namespace corgi;

constexpr unsigned short screen_width  = 500;
constexpr unsigned short screen_height = 500;

int main(int argc, char** argv)
{

    graphs::graph g;

    g.nodes = 8;

    g.edges.push_back({0, 1});

    g.edges.push_back({1, 2});
    g.edges.push_back({1, 3});

    g.edges.push_back({3, 4});

    g.edges.push_back({4, 5});
    g.edges.push_back({5, 6});
    g.edges.push_back({4, 7});

    g.build_adjacency_matrix();

    float distance = 60;

    std::vector<corgi::vec2> points;
    points.emplace_back(-distance, 0);
    points.emplace_back(0, 0);
    points.emplace_back(distance, 0);
    points.emplace_back(0, -distance);
    points.emplace_back(distance, -distance);
    points.emplace_back(distance, -distance * 2);
    points.emplace_back(distance * 2, -distance * 2);
    points.emplace_back(distance * 2, -distance);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    std::bitset<32> flags;

    flags[std::bit_width(unsigned(SDL_WINDOW_OPENGL)) - 1]     = 1;
    flags[std::bit_width(unsigned(SDL_WINDOW_SHOWN)) - 1]      = 1;
    flags[std::bit_width(unsigned(SDL_WINDOW_RESIZABLE)) - 1]  = 1;
    flags[std::bit_width(unsigned(SDL_WINDOW_BORDERLESS)) - 1] = 0;

    auto window = SDL_CreateWindow("dijkstra", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, screen_width,
                                   screen_height, flags.to_ullong());

    if(!window)
        std::cout << "Could not create window" << std::endl;

    const auto context = SDL_GL_CreateContext(window);

    gladLoadGLLoader(SDL_GL_GetProcAddress);

    SDL_GL_MakeCurrent(window, context);
    SDL_GL_SetSwapInterval(0);

    renderer renderer(screen_width, screen_height);

    glEnable(GL_MULTISAMPLE);

    bool quit = false;

    renderer.set_clear_color({0.3f, 0.3F, 0.3F, 1.0F});

    while(!quit)
    {
        renderer.clear();

        SDL_Event e;

        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    quit = true;
                    return 1;
            }
        }

        int i = 0;
        int j = 0;
        for(auto adj : g.adjacency_matrix)
        {
            j = 0;
            for(auto n : adj)
            {
                if(n != 0)
                {
                    renderer.set_default_color(1.0F, 1.0F, 1.0F);
                    renderer.draw_default_line_on_screen(
                        points[i].x, points[i].y, points[j].x, points[j].y);
                }
                j++;
            }
            i++;
        }

        for(auto point : points)
        {
            renderer.set_default_color(1.0F, 1.0F, 0.0F);
            renderer.draw_default_circle_on_screen(point.x, point.y, 10);
        }

        SDL_GL_SwapWindow(window);
    }

    SDL_Quit();
    return 1;
}