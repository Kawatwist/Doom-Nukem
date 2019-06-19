/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_rast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:44:56 by jsauron           #+#    #+#             */
/*   Updated: 2019/06/19 16:26:14 by jsauron          ###   ########.fr       */
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

t_vec	*ver_copy(t_win *wn, t_vec *src, int len)
{
	int		i;
	t_vec	*dst;

	i = 0;
	(dst = malloc(sizeof(t_vec ) * len)) == NULL ? stop_exec("Malloc vercpy failed\n", wn) : 0;
	while (i < len)
	{
		dst[i].x = src[i].x;
		dst[i].y = src[i].y;
		dst[i].z = src[i].z;
		i++;
	}
	return (dst);
}

void	print_matrice(double **matrice)
{
	printf("=> [%f][%f][%f][%f]\n", matrice[0][0], matrice[0][1], matrice[0][2], matrice[0][3]);
	printf("=> [%f][%f][%f][%f]\n", matrice[1][0], matrice[1][1], matrice[1][2], matrice[1][3]);
	printf("=> [%f][%f][%f][%f]\n", matrice[2][0], matrice[2][1], matrice[2][2], matrice[2][3]);
	printf("=> [%f][%f][%f][%f]\n", matrice[3][0], matrice[3][1], matrice[3][2], matrice[3][3]);
}

void	print_triangle(t_vec *v1, t_vec *v2, t_vec *v3)
{
	printf(" indice 1 | v1 = [%d] [%d]  v2 = [%d] [%d]\n", (int)v1->x, (int)v1->y, (int)v2->x, (int)v2->y);
	printf(" indice 2 | v1 = [%d] [%d]  v3 = [%d] [%d]\n", (int)v1->x, (int)v1->y, (int)v3->x, (int)v3->y);
	printf(" indice 3 | v2 = [%d] [%d]  v3 = [%d] [%d]\n\n", (int)v2->x, (int)v2->y, (int)v3->x, (int)v3->y);
}
