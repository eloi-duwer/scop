/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:22:14 by eduwer            #+#    #+#             */
/*   Updated: 2021/05/22 17:22:15 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<scop.h>

void	rotation_matrix_x(t_mat4x4 *mat, float angle)
{
	t_mat4x4	rot;
	float		sinus;
	float		cosinus;

	sinus = sin(angle);
	cosinus = cos(angle);
	init_identity_matrix(&rot);
	rot.mat[1][1] = cosinus;
	rot.mat[1][2] = -sinus;
	rot.mat[2][1] = sinus;
	rot.mat[2][2] = cosinus;
	mat4x4_mult(mat, &rot, mat);
}

void	rotation_matrix_y(t_mat4x4 *mat, float angle)
{
	t_mat4x4	rot;
	float		sinus;
	float		cosinus;

	sinus = sin(angle);
	cosinus = cos(angle);
	init_identity_matrix(&rot);
	rot.mat[0][0] = cosinus;
	rot.mat[0][2] = sinus;
	rot.mat[2][0] = -sinus;
	rot.mat[2][2] = cosinus;
	mat4x4_mult(mat, &rot, mat);
}

void	rotation_matrix_z(t_mat4x4 *mat, float angle)
{
	t_mat4x4	rot;
	float		sinus;
	float		cosinus;

	sinus = sin(angle);
	cosinus = cos(angle);
	init_identity_matrix(&rot);
	rot.mat[0][0] = cosinus;
	rot.mat[0][1] = sinus;
	rot.mat[1][0] = -sinus;
	rot.mat[1][1] = cosinus;
	mat4x4_mult(mat, &rot, mat);
}

void	rotation_vec_y(t_vec3 *vec, float angle)
{
	t_vec3 res;

	res.x = cos(angle) * vec->x + sin(angle) * vec->z;
	res.y = vec->y;
	res.z = -sin(angle) * vec->x + cos(angle) * vec->z;
	*vec = res;
}

double	pow2(double n)
{
	return (pow(n, 2.0));
}

void	rotation_around_axis(t_mat4x4 *mat, t_vec3 *a, double angle)
{
	t_mat4x4	rot;
	double		l;
	double		cosinus;
	double		sinus;

	l = pow2(a->x) + pow2(a->y) + pow2(a->z);
	cosinus = cos(angle);
	sinus = sin(angle);
	rot.mat[0][0] = (pow2(a->x) + (pow2(a->y) + pow2(a->z)) * cosinus) / l;
	rot.mat[0][1] = (a->x * a->y * (1 - cosinus) - (a->z * sqrt(l) * sinus)) / l;
	rot.mat[0][2] = (a->x * a->z * (1 - cosinus) + (a->y * sqrt(l) * sinus)) / l;
	rot.mat[0][3] = 0;
	rot.mat[1][0] = (a->x * a->y * (1 - cosinus) + (a->z * sqrt(l) * sinus)) / l;
	rot.mat[1][1] = (pow2(a->y) + (pow2(a->x) + pow2(a->z)) * cosinus) / l;
	rot.mat[1][2] = (a->y * a->z * (1 - cosinus) - (a->x * sqrt(l) * sinus)) / l;
	rot.mat[1][3] = 0;
	rot.mat[2][0] = (a->x * a->z * (1 - cosinus) - (a->y * sqrt(l) * sinus)) / l;
	rot.mat[2][1] = (a->y * a->z * (1 - cosinus) + (a->x * sqrt(l) * sinus)) / l;
	rot.mat[2][2] = (pow2(a->z) + (pow2(a->x) + pow2(a->y)) * cosinus) / l;
	rot.mat[2][3] = 0;
	rot.mat[3][0] = 0;
	rot.mat[3][1] = 0;
	rot.mat[3][2] = 0;
	rot.mat[3][3] = 1;
	mat4x4_mult(&rot, mat,mat);
}

void	rotation_around_axis_vec(t_vec3 *inout, t_vec3 *a, double angle)
{
	t_mat4x4	rot;
	double		l;
	double		cosinus;
	double		sinus;
	t_vec3		ret;

	l = pow2(a->x) + pow2(a->y) + pow2(a->z);
	cosinus = cos(angle);
	sinus = sin(angle);
	rot.mat[0][0] = (pow2(a->x) + (pow2(a->y) + pow2(a->z)) * cosinus) / l;
	rot.mat[0][1] = (a->x * a->y * (1 - cosinus) - (a->z * sqrt(l) * sinus)) / l;
	rot.mat[0][2] = (a->x * a->z * (1 - cosinus) + (a->y * sqrt(l) * sinus)) / l;
	rot.mat[0][3] = 0;
	rot.mat[1][0] = (a->x * a->y * (1 - cosinus) + (a->z * sqrt(l) * sinus)) / l;
	rot.mat[1][1] = (pow2(a->y) + (pow2(a->x) + pow2(a->z)) * cosinus) / l;
	rot.mat[1][2] = (a->y * a->z * (1 - cosinus) - (a->x * sqrt(l) * sinus)) / l;
	rot.mat[1][3] = 0;
	rot.mat[2][0] = (a->x * a->z * (1 - cosinus) - (a->y * sqrt(l) * sinus)) / l;
	rot.mat[2][1] = (a->y * a->z * (1 - cosinus) + (a->x * sqrt(l) * sinus)) / l;
	rot.mat[2][2] = (pow2(a->z) + (pow2(a->x) + pow2(a->y)) * cosinus) / l;
	rot.mat[2][3] = 0;
	rot.mat[3][0] = 0;
	rot.mat[3][1] = 0;
	rot.mat[3][2] = 0;
	rot.mat[3][3] = 1;
	
	ret.x = inout->x * rot.mat[0][0] + inout->y * rot.mat[0][1] + inout->z * rot.mat[0][2];
	ret.y = inout->x * rot.mat[1][0] + inout->y * rot.mat[1][1] + inout->z * rot.mat[1][2];
	ret.z = inout->x * rot.mat[2][0] + inout->y * rot.mat[2][1] + inout->z * rot.mat[2][2];
	*inout = ret;
}
