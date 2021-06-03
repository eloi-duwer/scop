/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:21:34 by eduwer            #+#    #+#             */
/*   Updated: 2021/06/03 17:06:23 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void		load_bitmapinfo_header(t_context *ctx, t_bmp_ctx *bmp, const char *filename)
{
	unsigned char	header[54 - 18];

	if (read(bmp->fd, header, 54 - 18) != 54 - 18)
		print_error(ctx, "File %s does not have a valid header (file too small)\n", filename);
	bmp->img_width = *(int32_t *)&(header[0]);
	bmp->img_height = *(int32_t *)&(header[4]);
	bmp->size = *(uint32_t *)&(header[16]);
}

void		load_bitmapv5_header(t_context *ctx, t_bmp_ctx *bmp, const char *filename)
{
	unsigned char	header[124 - 18];

	if (read(bmp->fd, header, 124 - 18) != 124 - 18)
		print_error(ctx, "File %s does not have a valid header (file too small)\n", filename);
	bmp->img_width = *(int32_t *)&(header[0]);
	bmp->img_height = *(int32_t *)&(header[4]);
	bmp->size = *(uint32_t *)&(header[16]);
}

void		load_bmp(t_context *ctx, t_bmp_ctx *bmp, const char *filename)
{
	unsigned char	header[18];

	ft_bzero(bmp, sizeof(t_bmp_ctx));
	bmp->fd = open(filename, O_RDONLY);
	if (bmp->fd < 0)
		print_error(ctx, "Can't open texture file %s\n", filename);
	if (read(bmp->fd, header, 18) != 18)
		print_error(ctx, "File %s is not a BMP file (file too small)\n", filename);
	if (ft_strncmp((char *)header, "BM", 2) != 0)
		print_error(ctx, "File %s is not a BMP file (bad header)\n", filename);
	bmp->data_offset = *(int32_t *)&(header[10]);
	if (*(uint32_t *)&(header[14]) == 40)
		load_bitmapinfo_header(ctx, bmp, filename);
	else if (*(uint32_t *)&(header[14]) == 124)
		load_bitmapv5_header(ctx, bmp, filename);
	else
		print_error(ctx, "Can't load bmp %s: Header type unsupported (size = %u)\n", filename, *(uint32_t *)&(header[14]));
	if (!bmp->size)
		bmp->size = bmp->img_height * bmp->img_width * 3;
	if (!bmp->data_offset)
		bmp->data_offset = *(int32_t *)&(header[14]);
	if (!(bmp->data = (unsigned char *)malloc(bmp->size)))
		print_error(ctx, "Malloc returned NULL\n");
	lseek(bmp->fd, bmp->data_offset, SEEK_SET);
	read(bmp->fd, bmp->data, bmp->size);
	close(bmp->fd);
}

void		free_mbp(t_bmp_ctx *bmp)
{
	free(bmp->data);
}

void		load_bmp_into_opengl(t_context *ctx, t_object *obj, const char *filename)
{
	t_bmp_ctx	bmp;

	print_opengl_error("Before loading bmp texture");
	load_bmp(ctx, &bmp, filename);
	glBindTexture(GL_TEXTURE_2D, obj->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp.img_width, bmp.img_height, 0, \
		GL_BGR, GL_UNSIGNED_BYTE, bmp.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);
	free_mbp(&bmp);
	print_opengl_error("After loading bmp texture");
}
