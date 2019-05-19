/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawpoly.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:32:23 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/19 16:33:45 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		printmatrice(double **matrice)
{
	printf("0:0 => [%f][%f][%f][%f]\n", matrice[0][0], matrice[0][1], matrice[0][2], matrice[0][3]);
	printf("1:0 => [%f][%f][%f][%f]\n", matrice[1][0], matrice[1][1], matrice[1][2], matrice[1][3]);
	printf("2:0 => [%f][%f][%f][%f]\n", matrice[2][0], matrice[2][1], matrice[2][2], matrice[2][3]);
	printf("3:0 => [%f][%f][%f][%f]\n", matrice[3][0], matrice[3][1], matrice[3][2], matrice[3][3]);
}

static void		initmatrice(double **matrice)
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

static void		matrice(t_poly *curr, double **mat, t_vec *ver)
{
	int		i;

	i = 0;
	while (i < curr->nb_ver)
	{
		ver[i].x = (curr->ver_list[i].x * mat[0][0]) + (curr->ver_list[i].y * mat[0][1]) + (curr->ver_list[i].z * mat[0][2]) + mat[0][3];
		ver[i].y = (curr->ver_list[i].y * mat[1][0]) + (curr->ver_list[i].y * mat[1][1]) + (curr->ver_list[i].z * mat[1][2]) + mat[1][3];
		ver[i].z = (curr->ver_list[i].z * mat[2][0]) + (curr->ver_list[i].y * mat[2][1]) + (curr->ver_list[i].z * mat[2][2]);
		i++;
	}
}

static void		drawtriangle(t_win *wn, t_vec *v1, t_vec *v2, t_vec *v3)
{
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
	double	**mat;
	t_vec	*ver;
	int		i;

	i = 0;
	mat = (double**)malloc(sizeof(double*) * 4);
	while (i < 4)
		mat[i++] = (double*)malloc(sizeof(double) * 4);
	curr = wn->poly;
	SDL_SetRenderDrawColor(wn->rend, 200, 200, 200, 0);
	initmatrice(mat);
	printmatrice(mat);
	rotatey((wn->player->rawx) * M_PI / 180, mat);
	printmatrice(mat);
	rotatex((wn->player->rawy * 360 / YSCREEN) * M_PI / 180, mat);
	printmatrice(mat);
	trans(wn, mat);
	printmatrice(mat);
	while (curr != NULL)
	{
		ver = malloc(sizeof(t_vec) * wn->poly->nb_ver);
		matrice(curr, mat, ver);
		drawpoly(wn, curr, ver);
		free(ver);
		curr = curr->next;
	}
}
