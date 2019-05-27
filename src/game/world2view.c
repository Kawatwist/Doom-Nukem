/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world2vew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:11:44 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/22 16:44:45 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		calc_f(t_win *wn)
{
	wn->rast->f->x = wn->player->x - wn->player->rawx;
	wn->rast->f->y = wn->player->y - wn->player->rawy;
	wn->rast->f->z = wn->player->z - wn->player->rawz;
}

static void		calc_s(t_win *wn, t_vec *f)
{
	// FAUX
	wn->rast->s->x = (f->x * 0) + (f->x * 1) + (f->x * 0);
	wn->rast->s->y = (f->y * 0) + (f->y * 1) + (f->y * 0);
	wn->rast->s->z = (f->z * 0) + (f->z * 1) + (f->z * 0);
}

static void		calc_u(t_win *wn, t_vec *s, t_vec *f)
{
	wn->rast->u->x = (f->x * s->x) + (f->x * s->y) + (f->x * s->z);
	wn->rast->u->y = (f->y * s->x) + (f->y * s->y) + (f->y * s->z);
	wn->rast->u->z = (f->z * s->x) + (f->z * s->y) + (f->z * s->z);
}

void			calc_fsu(t_win *wn, t_vec *ver, t_poly *curr)
{
	int		i;

	i = -1;
	calc_f(wn);
	calc_s(wn, wn->rast->f); // FAUX
	calc_u(wn , wn->rast->s, wn->rast->f);
	while (++i < curr->nb_indices)
		world2view(wn, &(ver[curr->indices[i]]), wn->rast->f, wn->rast->s, wn->rast->u);
}
