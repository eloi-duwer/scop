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
		SDL_WINDOWPOS_UNDEFINED, 590, 590, SDL_WINDOW_OPENGL);
	infos->glcontext = SDL_GL_CreateContext(infos->window);
	//gladLoadGLLoader(SDL_GL_GetProcAddress);
	SDL_GL_SetSwapInterval(1);
	create_program(infos);
}


void	setup_objects(t_infos *infos)
{
	GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,
	};

	GLfloat square[4][3] = {
	{10.0, 20.0, -20.0},
	{20.0, 20.0, -20.0},
	{20.0, 10.0, -20.0},
	{10.0, 10.0, -20.0}};

    GLfloat colors[4][3] = {{1.0, 0.0, 0.0}, \
		{0.0, 0.0, 1.0}, \
		{0.0, 1.0,  0.0}, \
		{1.0, 0.0, 0.0}};

	glGenVertexArrays(1, &(infos->vertex_array_id));
	glBindVertexArray(infos->vertex_array_id);
	glGenBuffers(2, infos->vertexbuffers);
	glBindBuffer(GL_ARRAY_BUFFER, infos->vertexbuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), \
		g_vertex_buffer_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, infos->vertexbuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
}
