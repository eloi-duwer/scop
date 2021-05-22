/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_opengl_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:37:21 by eduwer            #+#    #+#             */
/*   Updated: 2021/05/22 17:10:32 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define GLFUNC_IMPL
#include <gl_init.h>
#include <dlfcn.h>
#include <libft.h>

int load_opengl_funcs(void)
{
	void	*opengl_handle;

	opengl_handle = dlopen("libGL.so", RTLD_LAZY);
	if (!opengl_handle)
	{
		ft_printf("Error: Cannot Load libGL.so: %s\n", dlerror());	
		return (1);
	}
	#define GLFUNC(ret, name, ...) \
		gl##name = (name##Proc *) dlsym(opengl_handle, "gl" #name); \
		if (!gl##name) { \
			ft_printf("Function gl" #name " could not be loaded from libGL.so: %s\n", dlerror()); \
			return (1); \
		}

		OPENGL_FUNCS
	#undef GLFUNC
	return (0);
}