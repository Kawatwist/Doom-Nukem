/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawpoly.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:32:23 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/18 10:15:03 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
		ver[i].x = (curr->ver_list[i].x * mat[0][0]) + (curr->ver_list[i].y * mat[0][1]) + (curr->ver_list[i].z * mat[0][2]);
		ver[i].y = (curr->ver_list[i].y * mat[1][0]) + (curr->ver_list[i].y * mat[1][1]) + (curr->ver_list[i].z * mat[1][2]);
		ver[i].z = (curr->ver_list[i].z * mat[2][0]) + (curr->ver_list[i].y * mat[2][1]) + (curr->ver_list[i].z * mat[2][2]);
		i++;
	}
}

static void		drawtriangle(t_win *wn, t_vec *v1, t_vec *v2, t_vec *v3)
{
	printf("DRAW TRIANGLE\n");
	SDL_RenderDrawLine(wn->rend, v1->x, v1->y, v2->x, v2->y);
	SDL_RenderDrawLine(wn->rend, v1->x, v1->y, v3->x, v3->y);
	SDL_RenderDrawLine(wn->rend, v2->x, v2->y, v3->x, v3->y);
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
	printf("Set\n");
	SDL_SetRenderDrawColor(wn->rend, 200, 200, 200, 0);
	printf("Color\n");
	initmatrice(mat);
	printf("INIT\n");
	rotatex(wn->player->rawx, mat);
	printf("RotX\n");
	rotatey(wn->player->rawy * 360 / YSCREEN, mat);
	printf("RotY\n");
	while (curr != NULL)
	{
		ver = malloc(sizeof(t_vec) * wn->poly->nb_ver);
		printf("Malloc\n");
		matrice(curr, mat, ver);
		printf("Matrice\n");
		drawpoly(wn, curr, ver);
		printf("Draw\n");
		free(ver);
		printf("Free\n");
		curr = curr->next;
		printf("Next\n");
	}
	printf("Poly end\n");
}
