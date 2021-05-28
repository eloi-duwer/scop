/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 03:01:31 by eduwer            #+#    #+#             */
/*   Updated: 2021/05/28 16:29:08 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

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
	uint32_t	indexes[3];
	t_triangle	*new_triangles;

	if (!line[1] || !line[2] || !line[3])
		print_error(ctx, "Line %d: The face must have at least 3 points\n");
	indexes[0] = ft_atoi(line[1]) - 1;
	indexes[1] = ft_atoi(line[2]) - 1;
	i = 3;
	while (line[i])
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
		ft_memcpy(&obj->faces[obj->nb_faces], indexes, sizeof(uint32_t) * 3);
		indexes[1] = indexes[2];
		++i;
		++(obj->nb_faces);
	}
}

void	add_tex_coord(t_context *ctx, t_object *obj, char **line, int line_nb)
{
	t_vec2	*new_texutre_coords;

	if (obj->nb_tex_coords == obj->size_tex_coords)
	{
		if (!(new_texutre_coords = (t_vec2 *)realloc(obj->tex_coords, \
			sizeof(t_vec2) * (obj->nb_tex_coords + BUFF_SIZE))))
			print_error(ctx, "Realloc returned NULL\n");
		obj->tex_coords = new_texutre_coords;
		obj->size_tex_coords += BUFF_SIZE;
	}
	obj->tex_coords[obj->nb_tex_coords].x = strtof(line[1], NULL);
	obj->tex_coords[obj->nb_tex_coords].y = strtof(line[2], NULL);
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
	else if (ft_strcmp(splitted[0], "vt") == 0)
		add_tex_coord(ctx, obj, splitted, line_nb);
	free_string_tab(splitted);
}