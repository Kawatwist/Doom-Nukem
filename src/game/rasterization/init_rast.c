/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:19:49 by jsauron           #+#    #+#             */
/*   Updated: 2019/06/11 16:56:06 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	initmatrice(double **matrice)
{
	matrice[0][0] = 1.0;
	matrice[0][1] = 0.0;
	matrice[0][2] = 0.0;
	matrice[0][3] = 0.0;
	matrice[1][0] = 0.0;
	matrice[1][1] = 1.0;
	matrice[1][2] = 0.0;
	matrice[1][3] = 0.0;
	matrice[2][0] = 0.0;
	matrice[2][1] = 0.0;
	matrice[2][2] = 1.0;
	matrice[2][3] = 0.0;
	matrice[3][0] = 0.0;
	matrice[3][1] = 0.0;
	matrice[3][2] = 0.0;
	matrice[3][3] = 1.0;
}

void	init_ver(t_vec*vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void	init_rast(t_win **wn)
{
	int i;

	i = 0;
	((*wn)->rast = malloc(sizeof(t_rast))) == NULL ? stop_exec("malloc struct rast failed\n", *wn) : 0;
	malloc_mat(wn, (*wn)->rast->mat_1);
	malloc_mat(wn, (*wn)->rast->mat_2);
	malloc_mat(wn, (*wn)->rast->mat_3);
	((*wn)->rast->f = malloc(sizeof(t_vec))) == NULL ? stop_exec("malloc rast->f failed\n", *wn) : 0;
	((*wn)->rast->s = malloc(sizeof(t_vec))) == NULL ? stop_exec("malloc rast->s failed\n", *wn) : 0;
	((*wn)->rast->u = malloc(sizeof(t_vec))) == NULL ? stop_exec("malloc rast->u failed\n", *wn) : 0;
	initmatrice((*wn)->rast->mat_1);
	init_ver((*wn)->rast->f, 0, 0, 0);
	init_ver((*wn)->rast->s, 0, 0, 0);
	init_ver((*wn)->rast->u, 0, 0, 0);
}

void	init_poly(t_win **wn)
{
	(*wn)->poly = malloc(sizeof(t_poly));
	(*wn)->poly->ver_list = (t_vec *)malloc(sizeof(t_vec) * 4);
	init_ver(&((*wn)->poly->ver_list[0]), 100, 100, 100);
	init_ver(&((*wn)->poly->ver_list[1]), 120, 120, 100);
	init_ver(&((*wn)->poly->ver_list[2]), 120, 160, 100);
	init_ver(&((*wn)->poly->ver_list[3]), 100, 140, 100);
	(*wn)->poly->indices = malloc(sizeof(int) * 6);
	(*wn)->poly->indices[0] = 0;
	(*wn)->poly->indices[1] = 1;
	(*wn)->poly->indices[2] = 2;
	(*wn)->poly->indices[3] = 0;
	(*wn)->poly->indices[4] = 2;
	(*wn)->poly->indices[5] = 3;
	(*wn)->poly->nb_indices = 6;
	(*wn)->poly->nb_ver = 6;
	(*wn)->poly->next = NULL;
	(*wn)->poly->ver_tmp = NULL;
}

