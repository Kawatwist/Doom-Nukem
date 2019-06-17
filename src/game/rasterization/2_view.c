/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_world_2_view.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:04:13 by jsauron           #+#    #+#             */
/*   Updated: 2019/06/17 16:58:55 by jsauron          ###   ########.fr       */
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
		curr->normal[j] = ft_normalise(curr->normal[j]);
		i += 3;
		j++;
	}
}

void		data_fsu(t_win *wn)
{
	t_vec	z;
	t_vec	y;
	t_vec	x;

	z = ft_normalise(initvec(cos(degres_to_radius(wn->player->rawz))
				* sin(degres_to_radius(wn->player->rawz)),
				sin(degres_to_radius(degres_to_radius(wn->player->rawz))),
				cos(degres_to_radius(wn->player->rawz))
				* cos(degres_to_radius(wn->player->rawz))));
	y = ft_normalise(initvec(sin(degres_to_radius(wn->player->y) - M_PI / 2.0f),
				0,
				cos(degres_to_radius(wn->player->y) - M_PI / 2.0f)));
	x = inverse_vec(ft_normalise(ft_cross_product(z, y)));
	wn->rast->f = &z;
	wn->rast->s = &y;
	wn->rast->u = &x;
}

void	w2v_matrice(t_win *wn, t_vec *ver, t_poly *curr)
{
	int		i;

	i = 0;
	(void)ver;
	while (i++ < curr->nb_indices)
	{
		data_fsu(wn);
		init_mat_view(wn->rast->view, wn->rast->f,  wn->rast->s, wn->rast->u, init_vec_pos(wn));
	printf("x = %f\n", ver[curr->indices[i]].x);
	printf("y = %f\n", ver[curr->indices[i]].y);
	printf("z = %f\n", ver[curr->indices[i]].z);
		printmatrice(wn->rast->view);
	}
}

