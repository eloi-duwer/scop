/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exposed_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:20:41 by eduwer            #+#    #+#             */
/*   Updated: 2020/02/14 13:10:30 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

int	ft_printf(const char *str, ...)
{
	va_list	list;
	t_printf_context ctx;

	va_start(list, str);
	init_printf_context(&ctx, str, &list);
	reset_flags(&ctx);
	if (main_loop(&ctx) == error)
		return -1;
	va_end(list);
	ft_putstr(ctx.output);
	free(&(ctx.output[0]));
	return (ctx.out_i);
}

int	ft_sprintf(char *str, const char *format, ...)
{
	va_list	list;
	t_printf_context ctx;

	va_start(list, format);
	init_printf_context(&ctx, str, &list);
	reset_flags(&ctx);
	if (main_loop(&ctx) == error)
		return -1;
	va_end(list);
	ft_memcpy(str, ctx.output, ctx.out_i);
	str[ctx.out_i] = '\0';
	free(&(ctx.output[0]));
	return (ctx.out_i);
}

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	list;
	t_printf_context ctx;

	va_start(list, format);
	init_printf_context(&ctx, format, &list);
	reset_flags(&ctx);
	if (size != 0 && str == NULL)
		return -1;
	if (main_loop(&ctx) == error)
		return -1;
	va_end(list);
	if (str != NULL) {
		ft_bzero(str, size);
		ft_memcpy(str, ctx.output, size < ctx.out_i ? size : ctx.out_i);
	}
	free(&(ctx.output[0]));
	return (ctx.out_i);
}

int	ft_asprintf(char **pstr, const char *format, ...)
{
	va_list	list;
	t_printf_context ctx;

	va_start(list, format);
	init_printf_context(&ctx, format, &list);
	reset_flags(&ctx);
	if (main_loop(&ctx) == error)
		return -1;
	va_end(list);
	*pstr = ctx.output;
	return (ctx.out_i);
}
