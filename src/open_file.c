/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:21:46 by eduwer            #+#    #+#             */
/*   Updated: 2021/05/23 14:46:14 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void	free_object_ressources(t_context *ctx)
{
	int i;

	i = -1;
	while (++i < ctx->nb_objects)
	{
		free(ctx->objects[i].faces);
		free(ctx->objects[i].vertexes);
	}
	free(ctx->objects);
	glDeleteVertexArrays(1, &ctx->vertex_array);
	glDeleteBuffers(2, ctx->vertex_buffers);
}

void	open_file_chooser(t_context *ctx)
{
	GtkFileChooserNative	*chooser;
	gint					res;
	char					*filename;
	int						fd;

	chooser = gtk_file_chooser_native_new(\
			"Selectionnez un fichier a ouvrir", \
			gtk_application_get_active_window(ctx->app), \
			GTK_FILE_CHOOSER_ACTION_OPEN, \
			"Ouvrir", "Fermer");
	res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(chooser));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser));
		free_object_ressources(ctx);
		fd = open(filename, O_RDONLY);
		if (fd < 0)
			print_error(ctx, "Cannot open the file %s\n", filename);
		load_file(ctx, fd);
		close(fd);
		g_free(filename);
	}
	g_object_unref(chooser);
}

void	init_object(t_context *ctx)
{
	ctx->objects = (t_object *)malloc(sizeof(t_object) * 1);
	ctx->nb_objects = 1;
	if ((ctx->objects[0].faces = (t_triangle *)malloc(sizeof(t_triangle) * BUFF_SIZE)) == NULL)
		print_error(ctx, "Error on malloc\n");
	ctx->objects[0].size_faces = BUFF_SIZE;
	ctx->objects[0].nb_faces = 0;
	if ((ctx->objects[0].vertexes = (t_vec3 *)malloc(sizeof(t_vec3) * BUFF_SIZE)) == NULL)
		print_error(ctx, "Error on malloc\n");
	ctx->objects[0].size_vertexes = BUFF_SIZE;
	ctx->objects[0].nb_vertexes = 0;
	ctx->objects[0].center = (t_vec3) {0.0, 0.0, 0.0};
	ctx->objects[0].world_position = (t_vec3) {0.0, 0.0, 0.0};
	ctx->objects[0].dimensions = (t_vec3) {1.0f, 1.0f, 1.0f};
	init_identity_matrix(&ctx->objects[0].rotation_matrix);
	init_identity_matrix(&ctx->objects[0].model_matrix);
	ctx->objects[0].min_coords = (t_vec3) { INFINITY, INFINITY, INFINITY};
	ctx->objects[0].max_coords = (t_vec3) { -INFINITY, -INFINITY, -INFINITY};
}

static void	check_size_object(t_object *obj, int vertex_index)
{
	if (obj->vertexes[vertex_index].x > obj->max_coords.x)
		obj->max_coords.x = obj->vertexes[vertex_index].x;
	else if (obj->vertexes[vertex_index].x < obj->min_coords.x)
		obj->min_coords.x = obj->vertexes[vertex_index].x;
	if (obj->vertexes[vertex_index].y > obj->max_coords.y)
		obj->max_coords.y = obj->vertexes[vertex_index].y;
	else if (obj->vertexes[vertex_index].y < obj->min_coords.y)
		obj->min_coords.y = obj->vertexes[vertex_index].y;
	if (obj->vertexes[vertex_index].z > obj->max_coords.z)
		obj->max_coords.z = obj->vertexes[vertex_index].z;
	else if (obj->vertexes[vertex_index].z < obj->min_coords.z)
		obj->min_coords.z = obj->vertexes[vertex_index].z;
	obj->center.x += obj->vertexes[vertex_index].x;
	obj->center.y += obj->vertexes[vertex_index].y;
	obj->center.z += obj->vertexes[vertex_index].z;
}

void	add_vertice(t_context *ctx, t_object *obj, char **line, int line_nb)
{
	t_vec3	*new_vertexes;

	if (obj->nb_vertexes == obj->size_vertexes)
	{
		if (!(new_vertexes = (t_vec3 *)realloc(obj->vertexes, \
			sizeof(t_vec3) * (obj->nb_vertexes + BUFF_SIZE))))
			print_error(ctx, "Realloc returned NULL\n");
		obj->vertexes = new_vertexes;
		obj->size_vertexes += BUFF_SIZE;
	}
	if (!line[1] || !line[2] || !line[3])
		print_error(ctx, "Line %d: The vertex line don't have 3 coordinates\n", line_nb);
	setlocale(LC_NUMERIC, "en-US");
	obj->vertexes[obj->nb_vertexes].x = strtof(line[1], NULL);
	obj->vertexes[obj->nb_vertexes].y = strtof(line[2], NULL);
	obj->vertexes[obj->nb_vertexes].z = strtof(line[3], NULL);
	check_size_object(obj, obj->nb_vertexes);
	++(obj->nb_vertexes);
}

void	add_face(t_context *ctx, t_object *obj, char **line, int line_nb)
{
	int			i;
	int			indexes[3];
	t_triangle	*new_triangles;

	if (!line[3])
		print_error(ctx, "Line %d: The face must have at least 3 points\n");
	indexes[0] = ft_atoi(line[1]) - 1;
	indexes[1] = ft_atoi(line[2]) - 1;
	i = 3;
	while(line[i])
	{
		if (obj->nb_faces == obj->size_faces)
		{
			if (!(new_triangles = (t_triangle *)realloc(obj->faces, \
				sizeof(t_triangle) * (obj->nb_faces + BUFF_SIZE))))
				print_error(ctx, "Realloc returned NULL\n");
			obj->faces = new_triangles;
			obj->size_faces += BUFF_SIZE;
		}
		indexes[2] = ft_atoi(line[i]) - 1;
		ft_memcpy(&obj->faces[obj->nb_faces], indexes, sizeof(int) * 3);
		indexes[1] = indexes[2];
		++i;
		++(obj->nb_faces);
	}
}

void	parse_line(t_context *ctx, t_object *obj, char *line, int line_nb)
{
	char **splitted;

	splitted = ft_strsplit(line, ' ');
	if (splitted[0] == NULL)
		return;
	if (ft_strcmp(splitted[0], "v") == 0)
		add_vertice(ctx, obj, splitted, line_nb);
	else if (ft_strcmp(splitted[0], "f") == 0)
		add_face(ctx, obj, splitted, line_nb);
	free_string_tab(splitted);
}

void	load_obj_into_opengl(t_context *ctx, t_object *obj)
{
	glGenVertexArrays(1, &ctx->vertex_array);
	glBindVertexArray(ctx->vertex_array);
	glGenBuffers(2, ctx->vertex_buffers);
	glBindBuffer(GL_ARRAY_BUFFER, ctx->vertex_buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3) * obj->nb_vertexes, \
		obj->vertexes, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ctx->vertex_buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(t_triangle) * obj->nb_faces, \
		obj->faces, GL_STATIC_DRAW);
	free(obj->vertexes);
	free(obj->faces);
	obj->vertexes = NULL;
	obj->faces = NULL;
}

static void	set_inital_object_size_and_pos(t_context *ctx, t_object *obj)
{
	double		scale;
	uint64_t	i;

	scale = 2 / fmax(fmax(obj->max_coords.x - \
		obj->min_coords.x, obj->max_coords.y - obj->min_coords.y), \
		obj->max_coords.z - obj->min_coords.z);
	obj->dimensions = (t_vec3) { scale, scale, scale };
	obj->center.x /= obj->nb_vertexes;
	obj->center.y /= obj->nb_vertexes;
	obj->center.z /= obj->nb_vertexes;
	i = 0;
	while (i < obj->nb_vertexes)
	{
		obj->vertexes[i].x -= obj->center.x;
		obj->vertexes[i].y -= obj->center.y;
		obj->vertexes[i].z -= obj->center.z;
		i++;
	}
	glUniform3f(ctx->center, obj->center.x, obj->center.y, obj->center.z);
	printf("min coord:\n");
	print_vec(&obj->min_coords);
	printf("max coord:\n");
	print_vec(&obj->max_coords);
	printf("center:\n");
	print_vec(&obj->center);
	printf("scale: %.4f\n", scale);
}

void	load_file(t_context *ctx, int fd)
{
	int		ret;
	char	*line;
	int		line_nb;

	init_object(ctx);
	line_nb = 1;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		parse_line(ctx, &ctx->objects[0], line, line_nb);
		free(line);
		++line_nb;
	}
	if (ret == -1)
		print_error(ctx, "Error occured while parsing the file\n");
	free(line);
	set_inital_object_size_and_pos(ctx, &ctx->objects[0]);
	printf("nb vertexes: %lu\n", ctx->objects[0].nb_vertexes);
	printf("nb faces: %lu\n", ctx->objects[0].nb_faces);
	//print_face_coords(ctx->objects);

	uint64_t i = 0;
	while (i < ctx->objects[0].nb_faces) {
		if (ctx->objects[0].faces[i].points[2] > ctx->objects[0].nb_vertexes) {
			printf("Error found, Face index %lu %lu %lu, nb vertexes = %lu\n", ctx->objects[0].faces[i].points[0], ctx->objects[0].faces[i].points[1], ctx->objects[0].faces[i].points[2], ctx->objects[0].nb_vertexes);
		}
		i++;
	}
	load_obj_into_opengl(ctx, &ctx->objects[0]);
	if (ctx->text_name != NULL)
		load_bmp_into_opengl(ctx, ctx->text_name);
	else
		load_bmp_into_opengl(ctx, "./textures/unicorn_pattern.bmp");
}
