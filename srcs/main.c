#include <scop.h>

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,
};

void	quit_prog(t_infos *infos)
{
	SDL_DestroyWindow(infos->window);
	SDL_Quit();
	exit(0);
}

void	print_error(t_infos *infos, char *str)
{
	printf("%s\n", str);
	quit_prog(infos);
}

void	test_event(t_infos *infos)
{
	int event_type;

	event_type = (infos->event).type;
	if (event_type == SDL_KEYDOWN)
		handlekeyboarddown(infos);
	else if (event_type == SDL_QUIT)
		quit_prog(infos);
}

void	main_loop(t_infos *infos)
{
	while (true)
	{
		while (SDL_PollEvent(&(infos->event)))
			test_event(infos);
		glClear(GL_COLOR_BUFFER_BIT);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, infos->vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);
		glFlush();
		SDL_GL_SwapWindow(infos->window);
	}
}

int		main(int argc, char *argv[])
{
	t_infos infos;

	init_sdl_opengl(&infos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), \
		g_vertex_buffer_data, GL_STATIC_DRAW);
	main_loop(&infos);
    SDL_Quit();

    return 0;
}
