/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:19:49 by jsauron           #+#    #+#             */
/*   Updated: 2019/06/17 16:57:13 by jsauron          ###   ########.fr       */
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

t_vec	init_vec_pos(t_win *wn)
{
	t_vec	pos;

	pos.x = (wn->player->x);
	pos.y = (wn->player->y);
	pos.y = (wn->player->z);
	return(pos);
}

void	init_mat_view(double **matrice, t_vec *f, t_vec *s, t_vec *u, t_vec pos)
{
	matrice[0][0] = s->x;
	matrice[1][0] = s->y;
	matrice[2][0] = s->z;
	matrice[3][0] = -(ft_dot_product(*s, pos));
	matrice[0][1] = u->x;
	matrice[1][1] = u->y;
	matrice[2][1] = u->z;
	matrice[3][1] = -(ft_dot_product(*u, pos));
	matrice[0][2] = -(f->x);
	matrice[1][2] = -(f->y);
	matrice[2][2] = -(f->z);
	matrice[3][2] = -(ft_dot_product(*f, pos));
}

void	init_ver(t_vec *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

t_vec	initvec(float x, float y, float z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;

	return(vec);
}

t_vec	inverse_vec(t_vec vec)
{
	t_vec	res;

	res.x = -1 * vec.x;
	res.y = -1 * vec.y;
	res.z = -1 * vec.z;

	return (res);
}

void	init_rast(t_win **wn)
{
	int i;

	i = 0;
	((*wn)->rast = malloc(sizeof(t_rast))) == NULL ? stop_exec("malloc struct rast failed\n", *wn) : 0;
	malloc_mat(wn, &((*wn)->rast->model));
	malloc_mat(wn, &((*wn)->rast->view));
	malloc_mat(wn, &((*wn)->rast->proj));
	malloc_mat(wn, &((*wn)->rast->mat_pos));
	((*wn)->rast->f = malloc(sizeof(t_vec))) == NULL ? stop_exec("malloc rast->f failed\n", *wn) : 0;
	((*wn)->rast->s = malloc(sizeof(t_vec))) == NULL ? stop_exec("malloc rast->s failed\n", *wn) : 0;
	((*wn)->rast->u = malloc(sizeof(t_vec))) == NULL ? stop_exec("malloc rast->u failed\n", *wn) : 0;
	initmatrice((*wn)->rast->model);
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

