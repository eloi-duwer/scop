/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:22:23 by eduwer            #+#    #+#             */
/*   Updated: 2021/05/22 17:22:24 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	vec3_sub(t_vec3 *one, t_vec3 *two, t_vec3 *out)
{
	out->x = one->x - two->x;
	out->y = one->y - two->y;
	out->z = one->z - two->z;
}

void	vec3_add(t_vec3 *one, t_vec3 *two, t_vec3 *out)
{
	out->x = one->x * two->x;
	out->y = one->y * two->y;
	out->z = one->z * two->z;
}

void	vec3_normalize(t_vec3 *in, t_vec3 *out)
{
	double coef;

	coef = sqrt(pow(in->x, 2.0f) + pow(in->y, 2.0f) + pow(in->z, 2.0f));
	out->x = in->x / coef;
	out->y = in->y / coef;
	out->z = in->z / coef;
}

void	vec3_cross(t_vec3 *one, t_vec3 *two, t_vec3 *out)
{
	out->x = one->y * two->z - one->z * two->y;
	out->y = one->z * two->x - one->x * two->z;
	out->z = one->x * two->y - one->y * two->x;
}

float	vec3_dot(t_vec3 *one, t_vec3 *two)
{
	return (one->x * two->x + one->y * two->y + one->z * two->z);
}

void	mat4x4_mult(t_mat4x4 *one, t_mat4x4 *two, t_mat4x4 *out)
{
	int			vars[2];
	t_mat4x4	ret;

	vars[0] = -1;
	while (++vars[0] < 4)
	{
		vars[1] = -1;
		while (++vars[1] < 4)
		{
			ret.mat[vars[0]][vars[1]] = \
				one->mat[0][vars[1]] * two->mat[vars[0]][0] \
				+ one->mat[1][vars[1]] * two->mat[vars[0]][1] \
				+ one->mat[2][vars[1]] * two->mat[vars[0]][2] \
				+ one->mat[3][vars[1]] * two->mat[vars[0]][3];
		}
	}
	memcpy(out, &ret, sizeof(t_mat4x4));
}

void	mat4x4_displace(t_mat4x4 *inout, float x, float y, float z)
{
	t_mat4x4 dep;

	init_identity_matrix(&dep);
	dep.mat[0][3] = x;
	dep.mat[1][3] = y;
	dep.mat[2][3] = z;
	mat4x4_mult(inout, &dep, inout);
}
