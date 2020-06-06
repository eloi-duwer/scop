/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 17:30:48 by eduwer            #+#    #+#             */
/*   Updated: 2016/11/08 18:55:28 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef _WIN64
# include <io.h>
# define WRITE _write
#else
# include <unistd.h>
# define WRITE write
#endif

void	ft_putchar_fd(char c, int fd)
{
	unsigned char d;

	d = (unsigned char)c;
	WRITE(fd, &d, 1);
}
