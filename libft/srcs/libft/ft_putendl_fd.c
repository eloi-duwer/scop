/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 17:31:54 by eduwer            #+#    #+#             */
/*   Updated: 2016/11/09 17:44:47 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef _WIN64
# include <io.h>
# define WRITE _write
#else
# include <unistd.h>
# define WRITE write
#endif
#include <string.h>

void	ft_putendl_fd(char const *s, int fd)
{
	char	*pt_s;

	if (s != NULL)
	{
		pt_s = (char *)s;
		while (*pt_s != '\0')
		{
			WRITE(fd, pt_s, 1);
			pt_s++;
		}
		WRITE(fd, "\n", 1);
	}
}
