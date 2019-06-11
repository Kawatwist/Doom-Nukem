/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_world_2_view.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:04:13 by jsauron           #+#    #+#             */
/*   Updated: 2019/06/11 17:25:46 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		each_triangle(t_poly *curr)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < curr->nb_ver)
	{
		curr->normal[j] = ft_calculate_normal_of_points(
				curr->ver_tmp[curr->indices[i]],
				curr->ver_tmp[curr->indices[i + 1]],
				curr->ver_tmp[curr->indices[i + 2]]);
		i += 3;
		j++;
	}
}

static void		calc_f(t_win *wn)
{
	wn->rast->f->x = wn->player->x - wn->player->rawx;
	wn->rast->f->y = wn->player->y - wn->player->rawy;
	wn->rast->f->z = wn->player->z - wn->player->rawz;
}

static void		calc_s(t_win *wn, t_vec *f, t_vec *up)
{
	wn->rast->s->x = (f->x * up->x) + (f->x * up->y) + (f->x * up->z);
	wn->rast->s->y = (f->y * up->x) + (f->y * up->y) + (f->y * up->z);
	wn->rast->s->z = (f->z * up->x) + (f->z * up->y) + (f->z * up->z);
}

static void		calc_u(t_win *wn, t_vec *s, t_vec *f)
{
	wn->rast->u->x = (f->x * s->x) + (f->x * s->y) + (f->x * s->z);
	wn->rast->u->y = (f->y * s->x) + (f->y * s->y) + (f->y * s->z);
	wn->rast->u->z = (f->z * s->x) + (f->z * s->y) + (f->z * s->z);
}

void	w2v_matrice(t_win *wn, t_vec *ver, t_poly *curr)
{
	int		i;

	i = -1;
	while (++i < curr->nb_indices)
	{
		calc_f(wn);
		calc_s(wn, wn->rast->f, &curr->normal[i / 3]);
		calc_u(wn , wn->rast->s, wn->rast->f);
		w2v_matrice_calcul(wn, &(ver[curr->indices[i]]), wn->rast->f, wn->rast->s, wn->rast->u);
	}
}

void	w2v_matrice_calcul(t_win *wn, t_vec *ver, t_vec *f, t_vec *s, t_vec *u)
{
	t_vec	*ver_tmp;

	(ver_tmp = malloc(sizeof(t_vec))) == NULL ? stop_exec("malloc ver_tmp failed\n", wn) : 0;
	init_ver(ver_tmp, ver->x, ver->y, ver->z);
	ver->x = (s->x * 1 * ver_tmp->x) + (s->y * 0 * ver_tmp->y) + (s->z * 0 * ver_tmp->z) + (0 * -(wn->player->x) * 1);
	ver->y = (u->x * 1 * ver_tmp->x) + (u->y * 0 * ver_tmp->y) + (u->z * 0 * ver_tmp->z) + (0 * -(wn->player->y) * 1);
	ver->z = (-(f->x) * 1 * ver_tmp->x) + (-(f->y) * 0 * ver_tmp->y) + (-(f->z) * 0 * ver_tmp->z) + (0 * -(wn->player->y) * 1);
	free(ver_tmp);
}
