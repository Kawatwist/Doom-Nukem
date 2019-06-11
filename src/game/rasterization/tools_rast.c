/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_rast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:44:56 by jsauron           #+#    #+#             */
/*   Updated: 2019/06/11 17:10:43 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	malloc_mat(t_win **wn, double ***matrice)
{
	int		i;

	i = 0;
	((*matrice) = (double **)malloc(sizeof(double *) * 4)) == NULL ? stop_exec("malloc_matrice failed\n", *wn) : 0;
	while (i < 4)
		(((*matrice)[i++]) = (double *)malloc(sizeof(double) * 4)) == NULL ? stop_exec("malloc_matrice[] failed\n", *wn) : 0;
}

void	vercpy(t_vec *src, t_vec *dst, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		dst[i].x = src[i].x;
		dst[i].y = src[i].y;
		dst[i].z = src[i].z;
		i++;
	}
}
