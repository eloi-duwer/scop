#include <scop.h>

void	add_vertice(t_infos *infos, char **line)
{
	t_f_point *vertices;

	if (infos->nb_vertices == infos->vertices_size )
	{
		if (!(vertices = (t_f_point *)realloc(infos->vertices, \
			sizeof(t_f_point) * (infos->vertices_size + BUFFER_SIZE))))
			print_error(infos, "realloc vertices returned null");
		infos->vertices = vertices;
		infos->vertices_size += BUFFER_SIZE;
	}
	if (line[1] == NULL || line[2] == NULL || line[3] == NULL)
		print_error(infos, "A vertice doesn't have 3 coordinates");
	infos->vertices[infos->nb_vertices].x = strtof(line[1], NULL);
	infos->vertices[infos->nb_vertices].y = strtof(line[2], NULL);
	infos->vertices[infos->nb_vertices].z = strtof(line[3], NULL);
	++(infos->nb_vertices);
}

void	add_face(t_infos *infos, char **line)
{
    GLuint	*indexes;
    int		nb_vertices;

    nb_vertices = 0;
    while (line[nb_vertices + 1])
		++nb_vertices;
	if (nb_vertices < 3)
		print_error(infos, "A face has less than 3 vertices");
	else if(nb_vertices > 4)
		print_error(infos, "A face has more than 4 vertices");
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
	//printf("Face 1: %d %d %d\n", infos->indexes[infos->nb_indexes], infos->indexes[infos->nb_indexes + 1], infos->indexes[infos->nb_indexes + 2]);
	if (nb_vertices == 4)
	{
		infos->indexes[infos->nb_indexes + 3] = infos->indexes[infos->nb_indexes];
		infos->indexes[infos->nb_indexes + 4] = infos->indexes[infos->nb_indexes + 2];
		infos->indexes[infos->nb_indexes + 5] = (GLuint)ft_atoi(line[4]) - 1;
		//printf("Face 2: %d %d %d\n", infos->indexes[infos->nb_indexes + 3], infos->indexes[infos->nb_indexes + 4], infos->indexes[infos->nb_indexes + 5]);
		infos->nb_indexes += 3;
	}
	infos->nb_indexes += 3;
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
	/*int i = 0;
	while (i < infos->nb_indexes)
	{
		printf("%d %d %d\n", infos->indexes[i], infos->indexes[i+1], infos->indexes[i+2]);
		i += 3;
	}*/
	if (ret == -1)
		print_error(infos, "get_next_line returned -1");
	free(line);
}
