/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_index_object.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:45:47 by eduwer            #+#    #+#             */
/*   Updated: 2021/06/04 23:16:20 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static int	close_enough(float a, float b)
{
	return (a <= b + 0.00001f && a >= b - 0.00001f);
}

static int	find_vertex_with_properties(t_buff_vec3 *vertex, t_buff_vec2 *textures,\
			t_vec3 *pos, t_vec2 *tex, uint32_t *ret_index)
{
	t_vec3	*v;
	t_vec2	*vt;

	*ret_index = 0;
	while (*ret_index < vertex->nbel)
	{
		v = &vertex->b[*ret_index];
		vt = &textures->b[*ret_index];
		if (close_enough(v->x, pos->x) && close_enough(v->y, pos->x) && close_enough(v->z, pos->z)
			&& close_enough(vt->x, tex->x) && close_enough(vt->y, tex->y))
			return (1);
		(void)*ret_index++;
	}
	return (0);
}

static void	add_vertex_infos(t_context *ctx, t_buff_vec3 *vertex_buff, \
	t_buff_vec2 *tex_buff, t_vec3 *v, t_vec2 *vt, uint32_t *found_index)
{
	check_size_buff_vec3(ctx, vertex_buff);
	check_size_buff_vec2(ctx, tex_buff);
	ft_memcpy(&vertex_buff->b[vertex_buff->nbel], v, sizeof(*v));
	ft_memcpy(&tex_buff->b[tex_buff->nbel], vt, sizeof(*vt));
	*found_index = vertex_buff->nbel;
	vertex_buff->nbel++;
	tex_buff->nbel++;
}

void		reconstruct_index_object(t_context *ctx, t_object *obj)
{
	t_buff_tri	index_buffer;
	t_buff_vec3	vertex;
	t_buff_vec2	tex_coord;
	uint32_t	i;
	uint32_t	vertex_index;
	uint32_t	text_index;
	uint32_t	found_index;

	if (obj->faces_tex.nbel == 0)
	{
		obj->has_tex_coords = 0;
		return ;
	}
	obj->has_tex_coords = 1;
	ft_bzero(&index_buffer, sizeof(index_buffer));
	ft_bzero(&vertex, sizeof(vertex));
	ft_bzero(&tex_coord, sizeof(tex_coord));
	i = 0;
	while (i < obj->faces.nbel * 3)
	{
		vertex_index = ((uint32_t *)obj->faces.b)[i];
		text_index = ((uint32_t *)obj->faces_tex.b)[i];
		if (vertex_index >= obj->vertexes.nbel || text_index >= obj->tex_coords.nbel)
			print_error(ctx, "Found out of bound index in the object\n");
		if (!find_vertex_with_properties(&vertex, &tex_coord, &obj->vertexes.b[vertex_index], \
			&obj->tex_coords.b[text_index], &found_index))
		{
			add_vertex_infos(ctx, &vertex, &tex_coord, &obj->vertexes.b[vertex_index], \
				&obj->tex_coords.b[text_index], &found_index);
		}
		check_size_buff_tri(ctx, &index_buffer);
		((uint32_t *)index_buffer.b)[i] = found_index;
		index_buffer.nbel++;
		i++;
	}
	free(obj->faces.b);
	free(obj->faces_tex.b);
	free(obj->vertexes.b);
	free(obj->tex_coords.b);
	ft_memcpy(&obj->faces, &index_buffer, sizeof(index_buffer));
	ft_memcpy(&obj->vertexes, &vertex, sizeof(vertex));
	ft_memcpy(&obj->tex_coords, &tex_coord, sizeof(tex_coord));
}