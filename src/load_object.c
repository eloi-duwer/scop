/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:21:46 by eduwer            #+#    #+#             */
/*   Updated: 2021/05/26 03:35:00 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void	free_object_ressources(t_context *ctx)
{
	int i;

	print_opengl_error("Before freeing object ressources");
	i = -1;
	while (++i < ctx->nb_objects)
	{
		free(ctx->objects[i].faces);
		free(ctx->objects[i].vertexes);
		glDeleteVertexArrays(1, &ctx->objects[i].vertex_array);
		glDeleteBuffers(2, ctx->objects[i].vertex_buffers);
	}
	free(ctx->objects);
	print_opengl_error("After freeing object ressources");
}

void	open_file_chooser(t_context *ctx)
{
	GtkFileChooserNative	*chooser;
	gint					res;
	char					*filename;

	gdk_frame_clock_end_updating(ctx->clock);
	chooser = gtk_file_chooser_native_new(\
			"Open a new Object file", \
			gtk_application_get_active_window(ctx->app), \
			GTK_FILE_CHOOSER_ACTION_OPEN, \
			"Open", "Close");
	res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(chooser));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser));
		free_object_ressources(ctx);
		load_object_from_file(ctx->objects, ctx, filename);
		g_free(filename);
	}
	gdk_frame_clock_begin_updating(ctx->clock);
	g_object_unref(chooser);
}

void	init_object(t_context *ctx, t_object *obj)
{
	ft_bzero(obj, sizeof(t_object));
	if ((obj->faces = (t_triangle *)malloc(sizeof(t_triangle) * BUFF_SIZE)) == NULL)
		print_error(ctx, "Error on malloc\n");
	obj->size_faces = BUFF_SIZE;
	obj->nb_faces = 0;
	if ((obj->vertexes = (t_vec3 *)malloc(sizeof(t_vec3) * BUFF_SIZE)) == NULL)
		print_error(ctx, "Error on malloc\n");
	obj->size_vertexes = BUFF_SIZE;
	obj->nb_vertexes = 0;
	obj->center = (t_vec3) {0.0, 0.0, 0.0};
	obj->world_position = (t_vec3) {0.0, 0.0, 0.0};
	obj->dimensions = (t_vec3) {1.0f, 1.0f, 1.0f};
	init_identity_matrix(&obj->rotation_matrix);
	init_identity_matrix(&obj->model_matrix);
	obj->min_coords = (t_vec3) { INFINITY, INFINITY, INFINITY};
	obj->max_coords = (t_vec3) { -INFINITY, -INFINITY, -INFINITY};
}

void	load_obj_into_opengl(t_context *ctx, t_object *obj)
{
	print_opengl_error("Before loading object");
	glGenVertexArrays(1, &obj->vertex_array);
	glBindVertexArray(obj->vertex_array);
	glGenBuffers(2, obj->vertex_buffers);
	glBindBuffer(GL_ARRAY_BUFFER, obj->vertex_buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3) * obj->nb_vertexes, \
		obj->vertexes, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->vertex_buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(t_triangle) * obj->nb_faces, \
		obj->faces, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	free(obj->vertexes);
	free(obj->faces);
	obj->vertexes = NULL;
	obj->faces = NULL;
	print_opengl_error("After loading object");
}

static void	set_inital_object_size_and_pos(t_context *ctx, t_object *obj)
{
	double		scale;
	uint64_t	i;

	print_opengl_error("Before setting inital object size and pos");
	scale = 2 / fmax(fmax(obj->max_coords.x - \
		obj->min_coords.x, obj->max_coords.y - obj->min_coords.y), \
		obj->max_coords.z - obj->min_coords.z);
	obj->dimensions = (t_vec3) { scale, scale, scale };
	obj->center.x = (obj->min_coords.x + obj->max_coords.x) / 2;
	obj->center.y = (obj->min_coords.y + obj->max_coords.y) / 2;
	obj->center.z = (obj->min_coords.z + obj->max_coords.z) / 2;
	i = 0;
	while (i < obj->nb_vertexes)
	{
		obj->vertexes[i].x -= obj->center.x;
		obj->vertexes[i].y -= obj->center.y;
		obj->vertexes[i].z -= obj->center.z;
		i++;
	}
	printf("min coord:\n");
	print_vec(&obj->min_coords);
	printf("max coord:\n");
	print_vec(&obj->max_coords);
	printf("center:\n");
	print_vec(&obj->center);
	printf("scale: %.4f\n", scale);
	print_opengl_error("After setting inital object size and pos");
}

void	load_object_from_file(t_object *obj_ret, t_context *ctx, const char *filename)
{
	int			ret;
	char		*line;
	int			line_nb;
	int			fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error(ctx, "Cannot open the file %s\n", filename);
	init_object(ctx, obj_ret);
	line_nb = 1;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		parse_line(ctx, obj_ret, line, line_nb);
		free(line);
		++line_nb;
	}
	if (ret == -1)
		print_error(ctx, "Error occured while parsing the file\n");
	free(line);
	close(fd);
	set_inital_object_size_and_pos(ctx, obj_ret);
	printf("nb vertexes: %lu\n", obj_ret->nb_vertexes);
	printf("nb faces: %lu\n", obj_ret->nb_faces);
	load_obj_into_opengl(ctx, obj_ret);
}
