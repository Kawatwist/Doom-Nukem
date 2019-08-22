/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_textured_triangle.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:09:20 by jchardin          #+#    #+#             */
/*   Updated: 2019/08/22 12:58:26 by jchardin         ###   ########.fr       */
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
		SDL_Texture *texture,
		t_mytext *s_tex)
{

	/* t_mytext	*s_tex; */
	/* s_tex = malloc(sizeof(t_mytext)); */


	ft_order_point(
			&x1, &y1, &u1, &v1, &w1,
			&x2, &y2, &u2, &v2, &w2,
			&x3, &y3, &u3, &v3, &w3);

	int		j;
	int		i;

	int		dy1;
	float	dv1;
	int		dx1;
	float	du1;
	int		dy2;
	float	dv2;
	int		dx2;
	float	du2;

	s_tex->dax_step = 0;
	s_tex->du1_step = 0;
	s_tex->dv1_step = 0;
	s_tex->dbx_step = 0;
	s_tex->du2_step = 0;
	s_tex->dv2_step = 0;
	/* ********************************************************************** */
	/*	on draw le triangle du haut        bleu                               */
	/* ********************************************************************** */
	dy1 = y2 - y1;
	dv1 = v2 - v1;
	dx1 = x2 - x1;
	du1 = u2 - u1;
	dy2 = y3 - y1;
	dv2 = v3 - v1;
	dx2 = x3 - x1;
	du2 = u3 - u1;
	if (dy1)
	{
		s_tex->dax_step = dx1 / (float)abs(dy1);
		s_tex->du1_step = du1 / abs(dy1);
		s_tex->dv1_step = dv1 / abs(dy1);
	}
	if (dy2)
	{
		s_tex->dbx_step = dx2 / (float)abs(dy2);
		s_tex->du2_step = du2 / abs(dy2);
		s_tex->dv2_step = dv2 / abs(dy2);
	}
	if (dy1 > 0)
	{
		i = y1;
		while (i < y2)
		{
			s_tex->ax = x1 + (float)(i - y1) * s_tex->dax_step;
			s_tex->bx = x1 + (float)(i - y1) * s_tex->dbx_step;

			float tex_su = u1 + (float)(i - y1) * s_tex->du1_step;
			float tex_sv = v1 + (float)(i - y1) * s_tex->dv1_step;

			float tex_eu = u1 + (float)(i - y1) * s_tex->du2_step;
			float tex_ev = v1 + (float)(i - y1) * s_tex->dv2_step;
			if (s_tex->ax > s_tex->bx)
			{
				ft_swap_int(&(s_tex->ax), &(s_tex->bx));
				ft_swap_float(&(tex_su), &(tex_eu));
				ft_swap_float(&(tex_sv), &(tex_ev));
			}
			s_tex->tex_u = tex_su;
			s_tex->tex_v = tex_sv;
			s_tex->tstep = 1.0 / ((float)(s_tex->bx - s_tex->ax));
			float t = 0.0;
			j = s_tex->ax;
			while (j < s_tex->bx)
			{
				s_tex->tex_u = (1.0 - t) * tex_su + t * tex_eu;
				s_tex->tex_v = (1.0 - t) * tex_sv + t * tex_ev;
				t += s_tex->tstep;
				s_tex->srcrect.x = s_tex->tex_u * 512;
				s_tex->srcrect.y = s_tex->tex_v * 512;
				s_tex->srcrect.w = 1;
				s_tex->srcrect.h = 1;
				s_tex->dstrect.x = j;
				s_tex->dstrect.y = i;
				s_tex->dstrect.w = 1;
				s_tex->dstrect.h = 1;
				SDL_RenderCopy(wn->rend, texture, &(s_tex->srcrect), &(s_tex->dstrect));
				j++;
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
		s_tex->dax_step = dx1 / (float)abs(dy1);
	if (dy2)
		s_tex->dbx_step = dx2 / (float)abs(dy2);
	s_tex->du1_step = 0;
	s_tex->dv1_step = 0;
	if (dy1)
	{
		s_tex->du1_step = du1 / (float)abs(dy1);
		s_tex->dv1_step = dv1 / (float)abs(dy1);
	}
	if (dy1 > 0)
	{
		i = y2;
		while (i < y3)
		{
			s_tex->ax = x2 + (float)(i - y2) * s_tex->dax_step;
			s_tex->bx = x1 + (float)(i - y1) * s_tex->dbx_step;
			float tex_su = u2 + (float)(i - y2) * s_tex->du1_step;
			float tex_sv = v2 + (float)(i - y2) * s_tex->dv1_step;
			float tex_eu = u1 + (float)(i - y1) * s_tex->du2_step;
			float tex_ev = v1 + (float)(i - y1) * s_tex->dv2_step;
			if (s_tex->ax > s_tex->bx)
			{
				ft_swap_int(&(s_tex->ax), &(s_tex->bx));
				ft_swap_float(&(tex_su), &(tex_eu));
				ft_swap_float(&(tex_sv), &(tex_ev));
			}
			s_tex->tex_u = tex_su;
			s_tex->tex_v = tex_sv;
			s_tex->tstep = 1.0f / ((float)(s_tex->bx - s_tex->ax));
			float t = 0.0f;
			j = s_tex->ax;
			while (j < s_tex->bx)
			{
				s_tex->tex_u = (1.0f - t) * tex_su + t * tex_eu;
				s_tex->tex_v = (1.0f - t) * tex_sv + t * tex_ev;
				s_tex->srcrect.x = s_tex->tex_u * 512;
				s_tex->srcrect.y = s_tex->tex_v * 512;
				s_tex->srcrect.w = 1;
				s_tex->srcrect.h = 1;
				s_tex->dstrect.x = j;
				s_tex->dstrect.y = i;
				s_tex->dstrect.w = 1;
				s_tex->dstrect.h = 1;
				SDL_RenderCopy(wn->rend, texture, &(s_tex->srcrect), &(s_tex->dstrect));
				j++;
				t += s_tex->tstep;
			}
			i++;
		}
	}
}
