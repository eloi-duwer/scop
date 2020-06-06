/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 15:56:09 by eduwer            #+#    #+#             */
/*   Updated: 2016/11/09 17:42:55 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef _WIN64
# include <io.h>
# define WRITE _write
#else
# include <unistd.h>
# define WRITE write
#endif


void	ft_putendl(char const *s)
{
	char *pt_s;

	if (s != NULL)
	{
		pt_s = (char *)s;
		while (*pt_s != '\0')
		{
			WRITE(1, pt_s, 1);
			pt_s++;
		}
		WRITE(1, "\n", 1);
	}
}
