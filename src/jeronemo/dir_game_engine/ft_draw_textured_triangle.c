/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_textured_triangle.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:09:20 by jchardin          #+#    #+#             */
/*   Updated: 2019/08/22 12:16:02 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

SDL_Texture		*loadbmp(SDL_Renderer *tmp_renderer, char *path)
{
	SDL_Texture			*txt;
	SDL_Surface			*tmp;

	tmp = SDL_LoadBMP(path);
	txt = SDL_CreateTextureFromSurface(tmp_renderer, tmp);
	if (tmp != NULL)
		SDL_FreeSurface(tmp);
	return (txt);
}

void	ft_swap_int(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_swap_float(float *a, float *b)
{
	float tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_order_point(	int *x1, int *y1, float *u1, float *v1, float *w1,
		int *x2, int *y2, float *u2, float *v2, float *w2,
		int *x3, int *y3, float *u3, float *v3, float *w3)
{
	if (*y2 < *y1)
	{
		ft_swap_int(x1, x2);
		ft_swap_int(y1, y2);
		ft_swap_float(u1, u2);
		ft_swap_float(v1, v2);
		ft_swap_float(w1, w2);
	}
	if (*y3 < *y1)
	{
		ft_swap_int(x1, x3);
		ft_swap_int(y1, y3);
		ft_swap_float(u1, u3);
		ft_swap_float(v1, v3);
		ft_swap_float(w1, w3);
	}
	if (*y3 < *y2)
	{
		ft_swap_int(x2, x3);
		ft_swap_int(y2, y3);
		ft_swap_float(u2, u3);
		ft_swap_float(v2, v3);
		ft_swap_float(w2, w3);
	}
}

void	ft_draw_textured_triangle(
		int x1, int y1, float u1, float v1, float w1,
		int x2, int y2, float u2, float v2, float w2,
		int x3, int y3, float u3, float v3, float w3,
		t_win *wn,
		SDL_Texture *texture)
{
	ft_order_point(
			&x1, &y1, &u1, &v1, &w1,
			&x2, &y2, &u2, &v2, &w2,
			&x3, &y3, &u3, &v3, &w3);

	int		j;
	int		i;
	int		dy1;			float	dv1;
	int		dx1;			float	du1;
	int		dy2;			float	dv2;
	int		dx2;			float	du2;
	float	dax_step = 0;	float	du1_step = 0;	float	dv1_step = 0;
	float	dbx_step = 0;	float	du2_step = 0;	float	dv2_step = 0;
	int		ax;
	int		bx;

	float	tex_u;
	float	tex_v;
	float	tstep;

	SDL_Rect	srcrect;
	SDL_Rect	dstrect;
	/* ************************************************************************** */
	/*	on draw le triangle du haut        bleu                                   */
	/* ************************************************************************** */
	dy1 = y2 - y1;			dv1 = v2 - v1;
	dx1 = x2 - x1;			du1 = u2 - u1;

	dy2 = y3 - y1;			dv2 = v3 - v1;
	dx2 = x3 - x1;			du2 = u3 - u1;

	if (dy1)
	{
		dax_step = dx1 / (float)abs(dy1);//de combien de y on descent quand on avance d'un y
		du1_step = du1 / abs(dy1);
		dv1_step = dv1 / abs(dy1);
	}
	if (dy2)
	{
		dbx_step = dx2 / (float)abs(dy2);
		du2_step = du2 / abs(dy2);
		dv2_step = dv2 / abs(dy2);
	}
	/* ************************************************************************** */
	/*	on draw le triangle du haut             to half        en bleu            */
	/* ************************************************************************** */

	/* ########             DRAWING                         #########################*/

	int count = 0;

	if (dy1 > 0)
	{
		i = y1;
		while (i < y2)
		{
			ax = x1 + (float)(i - y1) * dax_step;
			bx = x1 + (float)(i - y1) * dbx_step;

			float tex_su = u1 + (float)(i - y1) * du1_step;
			float tex_sv = v1 + (float)(i - y1) * dv1_step;

			float tex_eu = u1 + (float)(i - y1) * du2_step;
			float tex_ev = v1 + (float)(i - y1) * dv2_step;
			if (ax > bx)
			{
				ft_swap_int(&ax, &bx);
				ft_swap_float(&tex_su, &tex_eu);
				ft_swap_float(&tex_sv, &tex_ev);
			}

			tex_u = tex_su;
			tex_v = tex_sv;
			tstep = 1.0 / ((float)(bx - ax));
			float t = 0.0;
			j = ax;
			while (j < bx)
			{
				tex_u = (1.0 - t) * tex_su + t * tex_eu;
				tex_v = (1.0 - t) * tex_sv + t * tex_ev;
				t += tstep;
				srcrect.x = tex_u * 512;
				srcrect.y = tex_v * 512;
				srcrect.w = 1;
				srcrect.h = 1;
				dstrect.x = j;
				dstrect.y = i;
				dstrect.w = 1;
				dstrect.h = 1;
				SDL_RenderCopy(wn->rend, texture, &srcrect, &dstrect);
				j++;
				count++;
			}
			i++;
		}
	}

	/* ************************************************************************** */
	/*	on draw le triangle du bas                                                */
	/* ************************************************************************** */
	dy1 = y3 - y2;
	dx1 = x3 - x2;
	dv1 = v3 - v2;
	du1 = u3 - u2;


	if (dy1)
		dax_step = dx1 / (float)abs(dy1);
	if (dy2)
		dbx_step = dx2 / (float)abs(dy2);
	du1_step = 0;
	dv1_step = 0;
	if (dy1)
	{
		du1_step = du1 / (float)abs(dy1);
		dv1_step = dv1 / (float)abs(dy1);
	}
	/* ########             DRAWING       green          #########################*/
	if (dy1 > 0)
	{
		i = y2;
		while (i < y3)
		{
			ax = x2 + (float)(i - y2) * dax_step;
			bx = x1 + (float)(i - y1) * dbx_step;
			float tex_su = u2 + (float)(i - y2) * du1_step;
			float tex_sv = v2 + (float)(i - y2) * dv1_step;
			float tex_eu = u1 + (float)(i - y1) * du2_step;
			float tex_ev = v1 + (float)(i - y1) * dv2_step;
			if (ax > bx)
			{
				ft_swap_int(&ax, &bx);
				ft_swap_float(&tex_su, &tex_eu);
				ft_swap_float(&tex_sv, &tex_ev);
			}
			tex_u = tex_su;
			tex_v = tex_sv;
			tstep = 1.0f / ((float)(bx - ax));
			float t = 0.0f;
			j = ax;
			while (j < bx)
			{
				tex_u = (1.0f - t) * tex_su + t * tex_eu;
				tex_v = (1.0f - t) * tex_sv + t * tex_ev;
				srcrect.x = tex_u * 512;
				srcrect.y = tex_v * 512;
				srcrect.w = 1;
				srcrect.h = 1;
				dstrect.x = j;
				dstrect.y = i;
				dstrect.w = 1;
				dstrect.h = 1;
				SDL_RenderCopy(wn->rend, texture, &srcrect, &dstrect);
				j++;
				t += tstep;
			}
			i++;
		}
	}
}
