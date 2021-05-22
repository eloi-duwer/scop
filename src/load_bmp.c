/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:21:34 by eduwer            #+#    #+#             */
/*   Updated: 2021/05/22 17:21:35 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void	init_bmp(t_context *ctx, t_bmp_ctx *bmp, char *filename)
{
	bmp->fd = open(filename, O_RDONLY);
	if (bmp->fd < 0)
		print_error(ctx, "Can't open texture file %s\n", filename);
	if (read(bmp->fd, bmp->header, 54) != 54)
		print_error(ctx, "File %s is not a BMP file (file too small)\n", filename);
	if (ft_strncmp((char *)bmp->header, "BM", 2) != 0)
		print_error(ctx, "File %s is not a BMP file (bad header)\n", filename);
	bmp->data_offset = *(int *)&(bmp->header[10]);
	bmp->img_width = *(int *)&(bmp->header[18]);
	bmp->img_height = *(int *)&(bmp->header[22]);
	bmp->size = *(unsigned int *)&(bmp->header[34]);

	if (!bmp->size)
		bmp->size = bmp->img_height * bmp->img_width * 3;
	if (!bmp->data_offset)
		bmp->data_offset = 54;
	if (!(bmp->data = (unsigned char *)malloc(bmp->size)))
		print_error(ctx, "Malloc returned NULL\n");
	read(bmp->fd, bmp->data, bmp->size);
	close(bmp->fd);
}

void		load_bmp_into_opengl(t_context *ctx, char *filename)
{
	t_bmp_ctx	bmp;

	print_opengl_error("Before loading bmp texture");
	init_bmp(ctx, &bmp, filename);
	glGenTextures(1, &ctx->objects[0].texture);
	glBindTexture(GL_TEXTURE_2D, ctx->objects[0].texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp.img_width, bmp.img_height, 0, \
		GL_BGR, GL_UNSIGNED_BYTE, bmp.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);
	print_opengl_error("After loading bmp texture");
}
