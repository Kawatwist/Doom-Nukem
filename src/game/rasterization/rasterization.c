/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:50:57 by jsauron           #+#    #+#             */
/*   Updated: 2019/06/19 16:59:29 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_vec	*get_vec_from_matrice(t_poly *curr, t_vec *ver, double **mat)
{
	int		i;

	i = 0;
	while (i++ < curr->nb_ver)
		ver[i] = mult_vec_mat(&ver[curr->indices[i]], mat);
	return (ver);
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
	curr->ver_tmp = get_vec_from_matrice(curr, curr->ver_tmp, wn->rast->mat_final);
}
