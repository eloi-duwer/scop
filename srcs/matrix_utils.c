/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:50:29 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/20 16:08:30 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	mult_matrix(float *mat1, float *mat2, float *res)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			res[i * 4 + j] = mat1[j] * mat2[i * 4] \
				+ mat1[j + 4 * 1] * mat2[i * 4 + 1] \
				+ mat1[j + 4 * 2] * mat2[i * 4 + 2] \
				+ mat1[j + 4 * 3] * mat2[i * 4 + 3];
		}
	}
}

void	init_identity_matrix(float *mat)
{
	mat[0] = 1;
	mat[1] = 0;
	mat[2] = 0;
	mat[3] = 0;
	mat[4] = 0;
	mat[5] = 1;
	mat[6] = 0;
	mat[7] = 0;
	mat[8] = 0;
	mat[9] = 0;
	mat[10] = 1;
	mat[11] = 0;
	mat[12] = 0;
	mat[13] = 0;
	mat[14] = 0;
	mat[15] = 1;
}

void	init_projection_infos(t_infos *infos, t_projection *projection)
{
	float	scale;
	int		w;
	int		h;

	SDL_GL_GetDrawableSize(infos->window, &w, &h);
	projection->angle_of_view = 90;
	projection->screen_ratio = (float)w / (float)h;
	projection->near_clip = 0.1;
	projection->far_clip = 100;
	scale = (float)tan(projection->angle_of_view * 0.5 * M_PI / 180) \
		* projection->near_clip;
	projection->right = projection->screen_ratio * scale;
	projection->left = -projection->right;
	projection->top = scale;
	projection->down = -scale;
	init_identity_matrix(projection->projection_matrix);
	projection->projection_matrix[0] = 2 * projection->near_clip / \
		(projection->right - projection->left);
	projection->projection_matrix[5] = 2 * projection->near_clip / \
		(projection->top - projection->down);
	projection->projection_matrix[8] = (projection->right + projection->left) \
		/ (projection->right - projection->left);
	projection->projection_matrix[9] = (projection->top + projection->down) \
		/ (projection->top - projection->down);
	projection->projection_matrix[10] = -(projection->far_clip + \
		projection->near_clip) / (projection->far_clip - projection->near_clip);
	projection->projection_matrix[11] = -1.0;
	projection->projection_matrix[14] = -2 * projection->far_clip * \
		projection->near_clip / (projection->far_clip - projection->near_clip);
	projection->projection_matrix[15] = 0.0;
}
