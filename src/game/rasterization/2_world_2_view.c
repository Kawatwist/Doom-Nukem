/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_world_2_view.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:04:13 by jsauron           #+#    #+#             */
/*   Updated: 2019/06/15 17:59:07 by jsauron          ###   ########.fr       */
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
	/*	printf("curr->ver_tmp[curr->indices[i]].x= %f\n", curr->ver_tmp[curr->indices[i]].x);
		printf("curr->ver_tmp[curr->indices[i]].y= %f\n", curr->ver_tmp[curr->indices[i]].y);
		printf("curr->ver_tmp[curr->indices[i]].z= %f\n", curr->ver_tmp[curr->indices[i]].z);
		printf("curr->ver_tmp[curr->indices[i + 1]].x= %f\n", curr->ver_tmp[curr->indices[i + 1]].x);
		printf("curr->ver_tmp[curr->indices[i + 1]].y= %f\n", curr->ver_tmp[curr->indices[i + 1]].y);
		printf("curr->ver_tmp[curr->indices[i + 1]].z= %f\n", curr->ver_tmp[curr->indices[i + 1]].z);
		printf("curr->ver_tmp[curr->indices[i + 2]].x= %f\n", curr->ver_tmp[curr->indices[i + 2]].x);
		printf("curr->ver_tmp[curr->indices[i + 2]].y= %f\n", curr->ver_tmp[curr->indices[i + 2]].y);
		printf("curr->ver_tmp[curr->indices[i + 2]].z= %f\n", curr->ver_tmp[curr->indices[i + 2]].z);
		printf("normal.x = %f\n", curr->normal[j].x);
		printf("normal.y = %f\n", curr->normal[j].y);
		printf("normal.z = %f\n", curr->normal[j].z);
	*/	i += 3;
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
	/*wn->rast->s->x = (f->x * up->x) + (f->x * up->y) + (f->x * up->z);
	wn->rast->s->y = (f->y * up->x) + (f->y * up->y) + (f->y * up->z);
	wn->rast->s->z = (f->z * up->x) + (f->z * up->y) + (f->z * up->z);
	*/
	*wn->rast->s = ft_cross_product(*f, *up);
	*wn->rast->s = ft_normalise(*wn->rast->s);
}

static void		calc_u(t_win *wn, t_vec *s, t_vec *f)
{
/*	wn->rast->u->x = (f->x * s->x) + (f->x * s->y) + (f->x * s->z);
	wn->rast->u->y = (f->y * s->x) + (f->y * s->y) + (f->y * s->z);
	wn->rast->u->z = (f->z * s->x) + (f->z * s->y) + (f->z * s->z);
*/
	*wn->rast->u = ft_cross_product(*s, *f);
	}

void	w2v_matrice(t_win *wn, t_vec *ver, t_poly *curr)
{
	int		i;

	i = -1;
	(void)ver;
	while (++i < curr->nb_indices)
	{
		calc_f(wn);
		calc_s(wn, wn->rast->f, &curr->normal[i / 3]);
		calc_u(wn , wn->rast->s, wn->rast->f);
		init_mat_2(wn->rast->mat_2, wn->rast->f, wn->rast->s, wn->rast->u);
		init_mat_pos(wn, wn->rast->mat_pos);
		wn->rast->mat_2 = mult_matrice(wn->rast->mat_2, wn->rast->mat_pos);
		w2v_matrice_calcul(wn, &(ver[curr->indices[i]]), wn->rast->mat_2);
		printmatrice(wn->rast->mat_2);
	}
}

void	w2v_matrice_calcul(t_win *wn, t_vec *ver, double **mat)
{
	t_vec	*ver_tmp;

	(ver_tmp = malloc(sizeof(t_vec))) == NULL ? stop_exec("malloc ver_tmp failed\n", wn) : 0;
	init_ver(ver_tmp, ver->x, ver->y, ver->z);
	ver->x = (mat[0][0] * ver_tmp->x)
		+ (mat[0][1] * ver_tmp->y)
		+ (mat[0][2] * ver_tmp->z)
		+ (mat[0][3] * 1);
	ver->y = (mat[1][0]* ver_tmp->x)
		+ (mat[1][1]* ver_tmp->y)
		+ (mat[1][2] * ver_tmp->z)
		+ (mat[1][3] * 1);
	ver->z = (mat[2][0] * ver_tmp->x)
		+ (mat[2][1] * ver_tmp->y)
		+ (mat[2][2]* ver_tmp->z)
		+ (mat[2][3] * 1);
	printf("x = %f\n", ver->x);
	printf("y = %f\n", ver->y);
	printf("z = %f\n", ver->z);
	free(ver_tmp);
}
