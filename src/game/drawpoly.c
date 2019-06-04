/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawpoly.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:32:23 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/24 12:48:02 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
/*
static void		printmatrice(double **matrice)
{
	printf("0:0 => [%f][%f][%f][%f]\n", matrice[0][0], matrice[0][1], matrice[0][2], matrice[0][3]);
	printf("1:0 => [%f][%f][%f][%f]\n", matrice[1][0], matrice[1][1], matrice[1][2], matrice[1][3]);
	printf("2:0 => [%f][%f][%f][%f]\n", matrice[2][0], matrice[2][1], matrice[2][2], matrice[2][3]);
	printf("3:0 => [%f][%f][%f][%f]\n", matrice[3][0], matrice[3][1], matrice[3][2], matrice[3][3]);
}
*/
void			initmatrice(double **matrice)
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

static void		matrice(t_win *wn, t_poly *curr, double **mat, t_vec *ver)
{
	int		i;

	i = 0;
	while (i < curr->nb_ver)
	{	
		ver[i].x = (curr->ver_tmp[curr->indices[i]].x * mat[0][0]) + (curr->ver_tmp[curr->indices[i]].y * mat[0][1]) + (curr->ver_tmp[curr->indices[i]].z * mat[0][2])  + mat[0][3];
		ver[i].y = (curr->ver_tmp[curr->indices[i]].y * mat[1][0]) + (curr->ver_tmp[curr->indices[i]].y * mat[1][1]) + (curr->ver_tmp[curr->indices[i]].z * mat[1][2]) + mat[1][3];
		ver[i].z = (curr->ver_tmp[curr->indices[i]].z * mat[2][0]) + (curr->ver_tmp[curr->indices[i]].y * mat[2][1]) + (curr->ver_tmp[curr->indices[i]].z * mat[2][2]) + mat[2][3];	
		get_near_n_far(wn, ver[i].z);
		i++;
	}
}

/*static void	proj(t_win *wn, t_poly *curr, t_vec *ver,  double **mat)
{
	int i;

	i = 0;
	projection(wn);
	mat = mult_matrice(mat, wn->rast->mat_proj);
	while (i < curr->nb_ver)
	{
		ver[i].x = (curr->ver_tmp[curr->indices[i]].x * mat[0][0]) + (curr->ver_tmp[curr->indices[i]].y * mat[0][1]) + (curr->ver_tmp[curr->indices[i]].z * mat[0][2]);
		ver[i].y = (curr->ver_tmp[curr->indices[i]].y * mat[1][0]) + (curr->ver_tmp[curr->indices[i]].y * mat[1][1]) + (curr->ver_tmp[curr->indices[i]].z * mat[1][2]);
		ver[i].z = (curr->ver_tmp[curr->indices[i]].z * mat[2][0]) + (curr->ver_tmp[curr->indices[i]].y * mat[2][1]) + (curr->ver_tmp[curr->indices[i]].z * mat[2][2]);
		i++;
	}	
}*/


void		get_near_n_far(t_win *wn, double z)
{
	if (z > wn->player->far && (wn->player->far == wn->player->near))
	{	
		wn->player->far = z;
		wn->player->near = z;
	}
	else if (z > wn->player->far)
		wn->player->far = z;
	else if (z < wn->player->near)
		wn->player->near = z;
}

static void		drawtriangle(t_win *wn, t_vec *v1, t_vec *v2, t_vec *v3)
{
//	printf("1 To 2 DRAW %d | %d => %d | %d\n", (int)v1->x, (int)v1->y, (int)v2->x, (int)v2->y);
//	printf("1 To 3 DRAW %d | %d => %d | %d\n", (int)v1->x, (int)v1->y, (int)v3->x, (int)v3->y);
//	printf("2 TO 3 DRAW %d | %d => %d | %d\n\n", (int)v2->x, (int)v2->y, (int)v3->x, (int)v3->y);
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

static void		vercpy(t_vec *src, t_vec *dst, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		dst[i].x = src[i].x;
		dst[i].y = src[i].y;
		dst[i].z = src[i].z;
		i++;
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
		rotatez(wn->player->rawz, wn->rast->mat);
		rotatey(wn->player->rawy, wn->rast->mat);
		rotatex(wn->player->rawx, wn->rast->mat);
		trans(wn, wn->rast->mat);
		matrice(wn, curr, wn->rast->mat, curr->ver_tmp);
	//	calc_fsu(wn, curr->ver_tmp, curr); // FAUX
	//	proj(wn, curr, curr->ver_tmp, wn->rast->mat);	
		drawpoly(wn, curr, curr->ver_tmp);
		free(curr->ver_tmp);
		curr = curr->next;
	}
	initmatrice(wn->rast->mat);
}
