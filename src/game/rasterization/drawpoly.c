/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawpoly.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:32:23 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/17 16:59:39 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		printmatrice(double **matrice)
{
	printf("0:0 => [%f][%f][%f][%f]\n", matrice[0][0], matrice[0][1], matrice[0][2], matrice[0][3]);
	printf("1:0 => [%f][%f][%f][%f]\n", matrice[1][0], matrice[1][1], matrice[1][2], matrice[1][3]);
	printf("2:0 => [%f][%f][%f][%f]\n", matrice[2][0], matrice[2][1], matrice[2][2], matrice[2][3]);
	printf("3:0 => [%f][%f][%f][%f]\n", matrice[3][0], matrice[3][1], matrice[3][2], matrice[3][3]);
}

static void		drawtriangle(t_win *wn, t_vec *v1, t_vec *v2, t_vec *v3)
{
	printf("1 To 2 DRAW %d | %d => %d | %d\n", (int)v1->x, (int)v1->y, (int)v2->x, (int)v2->y);
	printf("1 To 3 DRAW %d | %d => %d | %d\n", (int)v1->x, (int)v1->y, (int)v3->x, (int)v3->y);
	printf("2 TO 3 DRAW %d | %d => %d | %d\n\n", (int)v2->x, (int)v2->y, (int)v3->x, (int)v3->y);

	SDL_RenderDrawLine(wn->rend, (int)v1->x, (int)v1->y, (int)v2->x, (int)v2->y);
	SDL_RenderDrawLine(wn->rend, (int)v1->x, (int)v1->y, (int)v3->x, (int)v3->y);
	SDL_RenderDrawLine(wn->rend, (int)v2->x, (int)v2->y, (int)v3->x, (int)v3->y);
}

static void		drawpoly(t_win *wn, t_poly *curr, t_vec *ver)
{
	int		i;

	i = 0;
	while (i < curr->nb_indices)
	{
		drawtriangle(wn, &ver[curr->indices[i]], &ver[curr->indices[i + 1]], &ver[curr->indices[i + 2]]);
		i += 3;
	}
}

void			maindrawpoly(t_win *wn)
{
	t_poly	*curr;
	int		i;

	i = 0;
	curr = wn->poly;
	SDL_SetRenderDrawColor(wn->rend, 255, 0, 0, 0);
	while (curr != NULL)
	{
		(curr->ver_tmp = malloc(sizeof(t_vec) * curr->nb_ver)) == NULL ? stop_exec("Ver not malloc\n", wn) : 0;
		vercpy(curr->ver_list, curr->ver_tmp, curr->nb_ver);
		curr->normal = malloc(sizeof(t_vec) * (curr->nb_ver / 3));
		each_triangle(curr);
		rotatez(wn->player->rawz, wn->rast->model);
		rotatey(wn->player->rawy, wn->rast->model);
		rotatex(wn->player->rawx, wn->rast->model);
		trans(wn, wn->rast->model);
		m2w_matrice(wn, curr, wn->rast->model, curr->ver_tmp);
		w2v_matrice(wn, curr->ver_tmp, curr); 
	//	v2p_matrice_calcul(wn, curr, curr->ver_tmp, wn->rast->proj);
		drawpoly(wn, curr, curr->ver_tmp);
		free(curr->ver_tmp);
		curr = curr->next;
	}
	initmatrice(wn->rast->model);
}
