#include <scop.h>

void	init_sdl_opengl(t_infos *infos)
{
	SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_LoadLibrary(NULL);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    infos->window = SDL_CreateWindow("Test scope", SDL_WINDOWPOS_UNDEFINED, \
		SDL_WINDOWPOS_UNDEFINED, 1080, 590, SDL_WINDOW_OPENGL);
    infos->glcontext = SDL_GL_CreateContext(infos->window);
	gladLoadGLLoader(SDL_GL_GetProcAddress);
	SDL_GL_SetSwapInterval(1);
	glGenVertexArrays(1, &(infos->vertex_array_id));
	glBindVertexArray(infos->vertex_array_id);
	glGenBuffers(1, &(infos->vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, infos->vertexbuffer);
	create_program(infos);
}


