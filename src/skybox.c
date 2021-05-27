/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 00:06:16 by eduwer            #+#    #+#             */
/*   Updated: 2021/05/28 01:31:07 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void load_skybox_cube(t_context *ctx);
static void	load_skybox_texture(t_context *ctx);

static const char	*g_skybox_files[6] = {
	"./textures/skybox/right.bmp",
	"./textures/skybox/left.bmp",
	"./textures/skybox/top.bmp",
	"./textures/skybox/bottom.bmp",
	"./textures/skybox/front.bmp",
	"./textures/skybox/back.bmp"
};

void	load_skybox_into_opengl(t_context *ctx)
{
	load_skybox_cube(ctx);
	load_skybox_texture(ctx);
}

static void load_skybox_cube(t_context *ctx)
{
	load_object_from_file(&ctx->skybox, ctx, "./models/cube.obj");
}

static void	reverse_bmp(t_bmp_ctx *bmp)
{
	unsigned char	*tmp;
	const int		w = bmp->img_width * 3;
	const int		h = bmp->img_height;

	tmp = (unsigned char *)malloc(w);
	if (tmp == NULL)
		return ;
	for (int i = 0; i < h / 2; i++)
	{
		ft_memcpy(tmp, &bmp->data[bmp->size - (i + 1) * w], w);
		ft_memcpy(&bmp->data[bmp->size - (i + 1) * w], &bmp->data[i * w], w);
		ft_memcpy(&bmp->data[i * w], tmp, w);
	}
	free(tmp);
}

static void	load_skybox_texture(t_context *ctx)
{
	t_bmp_ctx	bmp;

	glGenTextures(1, &ctx->tex_skybox);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ctx->tex_skybox);
	for (int i = 0; i < 6; i++)
	{
		load_bmp(ctx, &bmp, g_skybox_files[i]);
		reverse_bmp(&bmp);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, bmp.img_width, \
			bmp.img_height, 0, GL_BGR, GL_UNSIGNED_BYTE, bmp.data);
		free_mbp(&bmp);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}