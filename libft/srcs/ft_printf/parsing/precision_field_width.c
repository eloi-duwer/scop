/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision_field_width.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:31:44 by eduwer            #+#    #+#             */
/*   Updated: 2020/02/14 12:46:37 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

e_printf_state get_field_width(t_printf_context *ctx)
{
	if (ft_isdigit(ctx->input[ctx->in_i]) == 1)
	{
		ctx->field_width = ft_atoi(&(ctx->input[ctx->in_i]));
		while(ctx->input[ctx->in_i] != '\0' && \
			ft_isdigit(ctx->input[ctx->in_i]) == 1)
			ctx->in_i++;
	}
	return get_precision(ctx);
}

e_printf_state get_precision(t_printf_context *ctx)
{
	if(ctx->input[ctx->in_i] == '.')
	{
		ctx->in_i++;
		ctx->precision = ft_atoi(&(ctx->input[ctx->in_i]));
		if (ctx->precision < 0)
			ctx->precision = -1;
		while (ctx->input[ctx->in_i] != '\0' && \
			ft_isdigit(ctx->input[ctx->in_i]) == 1)
			ctx->in_i++;
	}
	return get_modifiers(ctx);
}
