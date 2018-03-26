#include <scop.h>

void	verif_min_max(t_infos *infos, t_f_point vertice)
{
	if (vertice.x > infos->max_point.x)
		infos->max_point.x = vertice.x;
	else if (vertice.x < infos->min_point.x)
		infos->min_point.x = vertice.x;
	if (vertice.y > infos->max_point.y)
		infos->max_point.y = vertice.y;
	else if (vertice.y < infos->min_point.y)
		infos->min_point.y = vertice.y;
	if (vertice.z > infos->max_point.z)
		infos->max_point.z = vertice.z;
	else if (vertice.z < infos->min_point.z)
		infos->min_point.z = vertice.z;
}

void	add_vertice(t_infos *infos, char **line)
{
	t_f_point *vertices;

	if (infos->nb_vertices == infos->vertices_size )
	{
		if (!(vertices = (t_f_point *)realloc(infos->vertices, \
			sizeof(t_f_point) * (infos->vertices_size + BUFFER_SIZE))))
			print_error(infos, "Realloc vertices returned null");
		infos->vertices = vertices;
		infos->vertices_size += BUFFER_SIZE;
	}
	if (line[1] == NULL || line[2] == NULL || line[3] == NULL)
		print_error(infos, "A vertice doesn't have 3 coordinates");
	infos->vertices[infos->nb_vertices].x = strtof(line[1], NULL);
	infos->vertices[infos->nb_vertices].y = strtof(line[2], NULL);
	infos->vertices[infos->nb_vertices].z = strtof(line[3], NULL);
	infos->middle_obj_pos.x += infos->vertices[infos->nb_vertices].x;
	infos->middle_obj_pos.y += infos->vertices[infos->nb_vertices].y;
	infos->middle_obj_pos.z += infos->vertices[infos->nb_vertices].z;
	verif_min_max(infos, infos->vertices[infos->nb_vertices]);
	++(infos->nb_vertices);
}

void	add_face(t_infos *infos, char **line)
{
    GLuint	*indexes;
    int		nb_vertices;

    nb_vertices = 0;
    while (line[nb_vertices + 1])
		++nb_vertices;
	if (nb_vertices < 3 || nb_vertices > 4)
		print_error(infos, "A face has less than 3 vertices or more than 4");
	if (infos->nb_indexes + nb_vertices + (nb_vertices - 3) * 2 > infos->indexes_size)
	{
		if (!(indexes = (GLuint *)realloc(infos->indexes, \
			sizeof(GLuint) * (infos->indexes_size + BUFFER_SIZE))))
			print_error(infos, "Realloc faces returned null");
		infos->indexes = indexes;
		infos->indexes_size += BUFFER_SIZE;
	}
	infos->indexes[infos->nb_indexes] = (GLuint)ft_atoi(line[1]) - 1;
	infos->indexes[infos->nb_indexes + 1] = (GLuint)ft_atoi(line[2]) - 1;
	infos->indexes[infos->nb_indexes + 2] = (GLuint)ft_atoi(line[3]) - 1;
	if (nb_vertices == 4)
	{
		infos->indexes[infos->nb_indexes + 3] = infos->indexes[infos->nb_indexes];
		infos->indexes[infos->nb_indexes + 4] = infos->indexes[infos->nb_indexes + 2];
		infos->indexes[infos->nb_indexes + 5] = (GLuint)ft_atoi(line[4]) - 1;
		infos->nb_indexes += 3;
	}
	infos->nb_indexes += 3;
}

void	add_texture(t_infos *infos, char **line)
{
	float	*textures;

	if (infos->nb_textures >= infos->textures_size)
	{
		if (!(textures = (float *)realloc(infos->textures, \
			sizeof(float) * (infos->textures_size + BUFFER_SIZE))))
			print_error(infos, "Realloc textures returned null");
		infos->textures = textures;
		infos->textures_size += BUFFER_SIZE;
	}
	if (line[1] == NULL || line[2] == NULL)
		print_error(infos, "A texture coord have less than 2 coordinates");
	infos->textures[infos->nb_textures] = strtof(line[1], NULL);
	infos->textures[infos->nb_textures + 1] = strtof(line[2], NULL);
	infos->nb_textures += 2;
}

void	parse_line(t_infos *infos, char *line)
{
	char		**line_split;

	if (!(line_split = ft_strsplit(line, ' ')))
		print_error(infos, "ft_strsplit returned null");
	if (line_split[0] == NULL)
		return;
	if (line_split[0][0] == 'v' && line_split[0][1] == '\0')
		add_vertice(infos, line_split);
	else if(line_split[0][0] == 'f')
		add_face(infos, line_split);
	else if(line_split[0][0] == 'v' && line_split[0][1] == 't')
		add_texture(infos, line_split);
	free_string_tab(line_split);
}

void	parse_file(t_infos *infos, int ac, char **arg)
{
	char	*line;
	int		fd;
	int		ret;

	if (ac >= 2)
		fd = open(arg[1], O_RDONLY);
	else
		fd = open("./objects/42.obj", O_RDONLY);
	if (fd < 0)
		print_error(infos, "fd is < 0");
    while ((ret = get_next_line(fd, &line)) == 1)
	{
		parse_line(infos, line);
		free(line);
	}
	if (ret == -1)
		print_error(infos, "get_next_line returned -1");
	free(line);
	infos->middle_obj_pos.x /= infos->nb_vertices;
	infos->middle_obj_pos.y /= infos->nb_vertices;
	infos->middle_obj_pos.z /= infos->nb_vertices;
}
