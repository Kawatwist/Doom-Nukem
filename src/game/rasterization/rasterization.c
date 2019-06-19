/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:50:57 by jsauron           #+#    #+#             */
/*   Updated: 2019/06/19 16:23:48 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_vec	*get_vec_from_matrice(t_win *wn, t_poly *curr, t_vec *ver, double **mat)
{
	int		i;
	t_vec	*ver_tmp;

	i = 0;
	ver_tmp = ver_copy(wn, ver, curr->nb_ver);
	while (i < curr->nb_ver)
	{
		ver_tmp[i].x = (ver[curr->indices[i]].x * mat[0][0])
			+ (ver[curr->indices[i]].y * mat[0][1])
			+ (ver[curr->indices[i]].z * mat[0][2])
			+ mat[0][3];
		ver_tmp[i].y = (ver[curr->indices[i]].x * mat[1][0])
			+ (ver[curr->indices[i]].y * mat[1][1])
			+ (ver[curr->indices[i]].z * mat[1][2])
			+ mat[1][3];
		ver_tmp[i].z = (ver[curr->indices[i]].x * mat[2][0])
			+ (ver[curr->indices[i]].y * mat[2][1])
			+ (ver[curr->indices[i]].z * mat[2][2])
			+ mat[2][3];
		i++;
	}
	return (ver_tmp);
}

void	rasterization(t_win *wn, t_poly *curr)
{
	matrice_model(wn, wn->rast->model);
	printf("\n ======== MATRICE MODEL ====== \n");
	print_matrice(wn->rast->model);
	matrice_view(wn, curr->ver_tmp, curr);
	printf("\n ======== MATRICE VIEW ====== \n");
	print_matrice(wn->rast->view);
	matrice_projection(wn);
	printf("\n ======== MATRICE PROJECTION ====== \n");
	print_matrice(wn->rast->proj);
	wn->rast->mat_final = mult_matrice(mult_matrice(wn->rast->proj, wn->rast->view), wn->rast->model);
	curr->ver_tmp = get_vec_from_matrice(wn, curr, curr->ver_tmp, wn->rast->mat_final);
}
