/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_matrix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:50:39 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/20 15:55:24 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	translation_matrix(float *mat, float x, float y, float z)
{
	float	translation[16];
	float	res[16];

	init_identity_matrix(translation);
	mat[12] = x;
	mat[13] = y;
	mat[14] = z;
	mult_matrix(mat, translation, res);
	memcpy(mat, res, sizeof(float) * 16);
}
