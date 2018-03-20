/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:50:34 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/20 15:56:00 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	rotation_matrix_x(float *mat, float angle)
{
	float	rot[16];
	float	res[16];

	rot[0] = 1;
	rot[1] = 0;
	rot[2] = 0;
	rot[3] = 0;
	rot[4] = 0;
	rot[5] = (float)cos(angle);
	rot[6] = (float)sin(angle);
	rot[7] = 0;
	rot[8] = 0;
	rot[9] = (float)-sin(angle);
	rot[10] = (float)cos(angle);
	rot[11] = 0;
	rot[12] = 0;
	rot[13] = 0;
	rot[14] = 0;
	rot[15] = 1;
	mult_matrix(rot, mat, res);
	memcpy(mat, res, sizeof(float) * 16);
}

void	rotation_matrix_y(float *mat, float angle)
{
	float	rot[16];
	float	res[16];

	rot[0] = (float)cos(angle);
	rot[1] = 0;
	rot[2] = (float)-sin(angle);
	rot[3] = 0;
	rot[4] = 0;
	rot[5] = 1;
	rot[6] = 0;
	rot[7] = 0;
	rot[8] = (float)sin(angle);
	rot[9] = 0;
	rot[10] = (float)cos(angle);
	rot[11] = 0;
	rot[12] = 0;
	rot[13] = 0;
	rot[14] = 0;
	rot[15] = 1;
	mult_matrix(rot, mat, res);
	memcpy(mat, res, sizeof(float) * 16);
}

void	rotation_matrix_z(float *mat, float angle)
{
	float	rot[16];
	float	res[16];

	rot[0] = (float)cos(angle);
	rot[1] = (float)sin(angle);
	rot[2] = 0;
	rot[3] = 0;
	rot[4] = (float)-sin(angle);
	rot[5] = (float)cos(angle);
	rot[6] = 0;
	rot[7] = 0;
	rot[8] = 0;
	rot[9] = 0;
	rot[10] = 1;
	rot[11] = 0;
	rot[12] = 0;
	rot[13] = 0;
	rot[14] = 0;
	rot[15] = 1;
	mult_matrix(mat, rot, res);
	memcpy(mat, res, sizeof(float) * 16);
}
