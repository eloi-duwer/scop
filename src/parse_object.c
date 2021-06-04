/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 03:01:31 by eduwer            #+#    #+#             */
/*   Updated: 2021/06/04 02:29:52 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void	check_size_object(t_object *obj, int vertex_index)
{
	if (obj->vertexes.b[vertex_index].x > obj->max_coords.x)
		obj->max_coords.x = obj->vertexes.b[vertex_index].x;
	else if (obj->vertexes.b[vertex_index].x < obj->min_coords.x)
		obj->min_coords.x = obj->vertexes.b[vertex_index].x;
	if (obj->vertexes.b[vertex_index].y > obj->max_coords.y)
		obj->max_coords.y = obj->vertexes.b[vertex_index].y;
	else if (obj->vertexes.b[vertex_index].y < obj->min_coords.y)
		obj->min_coords.y = obj->vertexes.b[vertex_index].y;
	if (obj->vertexes.b[vertex_index].z > obj->max_coords.z)
		obj->max_coords.z = obj->vertexes.b[vertex_index].z;
	else if (obj->vertexes.b[vertex_index].z < obj->min_coords.z)
		obj->min_coords.z = obj->vertexes.b[vertex_index].z;
}

void	add_vertice(t_context *ctx, t_object *obj, char **line, int line_nb)
{
	check_size_buff_vec3(ctx, &obj->vertexes);
	if (!line[1] || !line[2] || !line[3])
		print_error(ctx, "Line %d: The vertex line don't have 3 coordinates\n", line_nb);
	setlocale(LC_NUMERIC, "en-US");
	obj->vertexes.b[obj->vertexes.nbel].x = strtof(line[1], NULL);
	obj->vertexes.b[obj->vertexes.nbel].y = strtof(line[2], NULL);
	obj->vertexes.b[obj->vertexes.nbel].z = strtof(line[3], NULL);
	check_size_object(obj, obj->vertexes.nbel);
	obj->vertexes.nbel++;
}

void	parse_face(char *face, uint32_t	*face_index, uint32_t *tex_index, int *has_tex)
{
	char **splitted;

	splitted = ft_strsplit(face, '/');
	if (!splitted[1])
		*has_tex = 0;
	else
	{
		*has_tex = 1;
		*tex_index = ft_atoi(splitted[1]) - 1;
	}
	*face_index = ft_atoi(splitted[0]) - 1;
	free(splitted);
}

void	add_face(t_context *ctx, t_object *obj, char **line, int line_nb)
{
	int			i;
	uint32_t	index_face[3];
	int			has_tex;
	uint32_t	index_tex[3];

	if (!line[1] || !line[2] || !line[3])
		print_error(ctx, "Line %d: The face must have at least 3 points\n");
	parse_face(line[1], index_face, index_tex, &has_tex);
	parse_face(line[2], index_face + 1, index_tex + 1, &has_tex);
	i = 3;
	while (line[i])
	{
		check_size_buff_tri(ctx, &obj->faces);
		parse_face(line[i], index_face + 2, index_tex + 2, &has_tex);
		ft_memcpy(&obj->faces.b[obj->faces.nbel], index_face, sizeof(uint32_t) * 3);
		if (has_tex)
		{
			check_size_buff_tri(ctx, &obj->faces_tex);
			ft_memcpy(&obj->faces_tex.b[obj->faces_tex.nbel], index_tex, sizeof(uint32_t) * 3);
		}
		index_face[1] = index_face[2];
		index_tex[1] = index_tex[2];
		i++;
		obj->faces.nbel++;
	}
}

void	add_tex_coord(t_context *ctx, t_object *obj, char **line, int line_nb)
{
	check_size_buff_vec2(ctx, &obj->tex_coords);
	obj->tex_coords.b[obj->tex_coords.nbel].x = strtof(line[1], NULL);
	obj->tex_coords.b[obj->tex_coords.nbel].y = strtof(line[2], NULL);
	obj->tex_coords.nbel++;
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