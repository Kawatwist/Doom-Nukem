/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_textured_triangle.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:09:20 by jchardin          #+#    #+#             */
/*   Updated: 2019/11/04 18:23:28 by jchardin         ###   ########.fr       */
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
	*a = *b; *b = tmp;
}

void	ft_swap_float(float *a, float *b)
{
	float tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_order_point(
		float *x1, float *y1, float *u1, float *v1, float *w1,
		float *x2, float *y2, float *u2, float *v2, float *w2,
		float *x3, float *y3, float *u3, float *v3, float *w3)
{
		*x1 = (int)*x1;
		*x2 = (int)*x2;
		*x3 = (int)*x3;
		*y1 = (int)*y1;
		*y2 = (int)*y2;
		*y3 = (int)*y3;
	if (*y2 < *y1)
	{
		ft_swap_float(x1, x2);
		ft_swap_float(y1, y2);
		ft_swap_float(u1, u2);
		ft_swap_float(v1, v2);
		ft_swap_float(w1, w2);
	}
	if (*y3 < *y1)
	{
		ft_swap_float(x1, x3);
		ft_swap_float(y1, y3);
		ft_swap_float(u1, u3);
		ft_swap_float(v1, v3);
		ft_swap_float(w1, w3);
	}
	if (*y3 < *y2)
	{
		ft_swap_float(x2, x3);
		ft_swap_float(y2, y3);
		ft_swap_float(u2, u3);
		ft_swap_float(v2, v3);
		ft_swap_float(w2, w3);
	}
}


void ft_clear_screen(int** pixel)
{
	int *val;
	int i =0;
	val = malloc(sizeof(int));
	*val = 0;
	while (i   <  (1920 * 1080)   )
	{
		(*pixel)[i] = val[0];
		i++;
	}
}


void	ft_draw_textured_triangle(t_mytriangle *tri, t_mytext *s_tex, int** pixel)
{
	/* int		tri->vertice[0].x = tri->vertice[0].x;    //x1 */
	/* int		tri->vertice[0].y = tri->vertice[0].y;    //y1 */
	/* float	tri->texture[0].u = tri->texture[0].u;    //u1 */
	/* float	tri->texture[0].v = tri->texture[0].v;    //v1 */
	/* float	tri->texture[0].w = tri->texture[0].w;    //w1 */

	/* float	tri->vertice[1].x = tri->vertice[1].x;    //x2 */
	/* float	tri->vertice[1].y = tri->vertice[1].y;    //y2 */
	/* float	tri->texture[1].u = tri->texture[1].u;    //u2 */
	/* float	tri->texture[1].v = tri->texture[1].v;    //v2 */
	/* float	tri->texture[1].w = tri->texture[1].w;    //w2 */

	/* float	tri->vertice[2].x = tri->vertice[2].x;    //x3 */
	/* float	tri->vertice[2].y = tri->vertice[2].y;    //y3 */
	/* float	tri->texture[2].u = tri->texture[2].u;    //u3 */
	/* float	tri->texture[2].v = tri->texture[2].v;    //v3 */
	/* float	tri->texture[2].w = tri->texture[2].w;    //w3 */


	int		j;
	int		i;
	float	t;

	s_tex->dax_step = 0;
	s_tex->dbx_step = 0;
	s_tex->du1_step = 0;
	s_tex->dv1_step = 0;
	s_tex->du2_step = 0;
	s_tex->dv2_step = 0;
	s_tex->dw1_step = 0;
	s_tex->dw2_step = 0;

	ft_order_point( &(tri->vertice[0].x), &(tri->vertice[0].y), &(tri->texture[0].u), &(tri->texture[0].v), &(tri->texture[0].w), &(tri->vertice[1].x), &(tri->vertice[1].y), &(tri->texture[1].u), &(tri->texture[1].v), &(tri->texture[1].w), &(tri->vertice[2].x), &(tri->vertice[2].y), &(tri->texture[2].u), &(tri->texture[2].v), &(tri->texture[2].w));
	/* ************************************************************************/
	/*	on draw le triangle du haut        bleu                               */
	/* ************************************************************************/
	s_tex->dy1 = tri->vertice[1].y - tri->vertice[0].y;
	s_tex->dv1 = tri->texture[1].v - tri->texture[0].v;
	s_tex->dx1 = tri->vertice[1].x - tri->vertice[0].x;
	s_tex->du1 = tri->texture[1].u - tri->texture[0].u;
	s_tex->dw1 = tri->texture[1].w - tri->texture[0].w;
	s_tex->dy2 = tri->vertice[2].y - tri->vertice[0].y;
	s_tex->dv2 = tri->texture[2].v - tri->texture[0].v;
	s_tex->dx2 = tri->vertice[2].x - tri->vertice[0].x;
	s_tex->du2 = tri->texture[2].u - tri->texture[0].u;
	s_tex->dw2 = tri->texture[2].w - tri->texture[0].w;

	if (s_tex->dy1)
	{
		s_tex->dax_step = s_tex->dx1 / (float)abs(s_tex->dy1);
		s_tex->du1_step = s_tex->du1 / (float)abs(s_tex->dy1);
		s_tex->dv1_step = s_tex->dv1 / (float)abs(s_tex->dy1);
		s_tex->dw1_step = s_tex->dw1 / (float)abs(s_tex->dy1);
	}
	if (s_tex->dy2)
	{
		s_tex->dbx_step = s_tex->dx2 / (float)abs(s_tex->dy2);
		s_tex->du2_step = s_tex->du2 / (float)abs(s_tex->dy2);
		s_tex->dv2_step = s_tex->dv2 / (float)abs(s_tex->dy2);
		s_tex->dw2_step = s_tex->dw2 / (float)abs(s_tex->dy2);
	}
	if (s_tex->dy1 > 0)
	{
		i = tri->vertice[0].y;
		while (i < tri->vertice[1].y)
		{
			s_tex->ax = tri->vertice[0].x + (float)(i - tri->vertice[0].y) * s_tex->dax_step;
			s_tex->bx = tri->vertice[0].x + (float)(i - tri->vertice[0].y) * s_tex->dbx_step;

			s_tex->tex_su = tri->texture[0].u + (float)(i - tri->vertice[0].y) * s_tex->du1_step;
			s_tex->tex_sv = tri->texture[0].v + (float)(i - tri->vertice[0].y) * s_tex->dv1_step;
			s_tex->tex_sw = tri->texture[0].w + (float)(i - tri->vertice[0].y) * s_tex->dw1_step;

			s_tex->tex_eu = tri->texture[0].u + (float)(i - tri->vertice[0].y) * s_tex->du2_step;
			s_tex->tex_ev = tri->texture[0].v + (float)(i - tri->vertice[0].y) * s_tex->dv2_step;
			s_tex->tex_ew = tri->texture[0].w + (float)(i - tri->vertice[0].y) * s_tex->dw2_step;

			if (s_tex->ax > s_tex->bx)
			{
				ft_swap_int(&(s_tex->ax), &(s_tex->bx));
				ft_swap_float(&(s_tex->tex_su), &(s_tex->tex_eu));
				ft_swap_float(&(s_tex->tex_sv), &(s_tex->tex_ev));
				ft_swap_float(&(s_tex->tex_sw), &(s_tex->tex_ew));
			}
			s_tex->tex_u = s_tex->tex_su;
			s_tex->tex_v = s_tex->tex_sv;
			s_tex->tex_w = s_tex->tex_sw;
			s_tex->tstep = 1.0 / ((float)(s_tex->bx - s_tex->ax));
			t = 0.0;
			j = s_tex->ax;
			while (j < s_tex->bx)
			{
				s_tex->tex_u = (1.0 - t) * s_tex->tex_su + t * s_tex->tex_eu;
				s_tex->tex_v = (1.0 - t) * s_tex->tex_sv + t * s_tex->tex_ev;
				s_tex->tex_w = (1.0 - t) * s_tex->tex_sw + t * s_tex->tex_ew;
				t += s_tex->tstep;
				s_tex->srcrect.x = s_tex->tex_u / s_tex->tex_w * s_tex->tga->w;
				s_tex->srcrect.y = s_tex->tex_v / s_tex->tex_w * s_tex->tga->w;
				s_tex->dstrect.x = j;
				s_tex->dstrect.y = i;

				if ((s_tex->srcrect.x + s_tex->srcrect.y * s_tex->tga->w) < 512 * 512)
				{
					/* if ((i * 1920 + j)   <  (1920 * 1080)  ) */
					if ((i * 1920 + j)   <  (1920 * 1080)   )
					{
						(*pixel)[i * 1920 + j] = ((int *)s_tex->tga->data)[(s_tex->srcrect.x + s_tex->srcrect.y * s_tex->tga->w)];
					}
				}
				j++;
			}
			i++;
		}
	}
	/**************************************************************************/
	/*	on draw le triangle du bas                                            */
	/**************************************************************************/
	s_tex->dy1 = tri->vertice[2].y - tri->vertice[1].y;
	s_tex->dx1 = tri->vertice[2].x - tri->vertice[1].x;
	s_tex->dv1 = tri->texture[2].v - tri->texture[1].v;
	s_tex->du1 = tri->texture[2].u - tri->texture[1].u;
	s_tex->dw1 = tri->texture[2].w - tri->texture[1].w;
	if (s_tex->dy1)
		s_tex->dax_step = s_tex->dx1 / (float)abs(s_tex->dy1);
	if (s_tex->dy2)
		s_tex->dbx_step = s_tex->dx2 / (float)abs(s_tex->dy2);
	s_tex->du1_step = 0;
	s_tex->dv1_step = 0;
	if (s_tex->dy1)
	{
		s_tex->du1_step = s_tex->du1 / (float)abs(s_tex->dy1);
		s_tex->dv1_step = s_tex->dv1 / (float)abs(s_tex->dy1);
		s_tex->dw1_step = s_tex->dw1 / (float)abs(s_tex->dy1);
	}
	if (s_tex->dy1 > 0)
	{
		i = tri->vertice[1].y;
		while (i < tri->vertice[2].y)
		{
			s_tex->ax = tri->vertice[1].x + (float)(i - tri->vertice[1].y) * s_tex->dax_step;
			s_tex->bx = tri->vertice[0].x + (float)(i - tri->vertice[0].y) * s_tex->dbx_step;
			s_tex->tex_su = tri->texture[1].u + (float)(i - tri->vertice[1].y) * s_tex->du1_step;
			s_tex->tex_sv = tri->texture[1].v + (float)(i - tri->vertice[1].y) * s_tex->dv1_step;
			s_tex->tex_sw = tri->texture[1].w + (float)(i - tri->vertice[1].y) * s_tex->dw1_step;

			s_tex->tex_eu = tri->texture[0].u + (float)(i - tri->vertice[0].y) * s_tex->du2_step;
			s_tex->tex_ev = tri->texture[0].v + (float)(i - tri->vertice[0].y) * s_tex->dv2_step;
			s_tex->tex_ew = tri->texture[0].w + (float)(i - tri->vertice[0].y) * s_tex->dw2_step;
			if (s_tex->ax > s_tex->bx)
			{
				ft_swap_int(&(s_tex->ax), &(s_tex->bx));
				ft_swap_float(&(s_tex->tex_su), &(s_tex->tex_eu));
				ft_swap_float(&(s_tex->tex_sv), &(s_tex->tex_ev));
				ft_swap_float(&(s_tex->tex_sw), &(s_tex->tex_ew));
			}
			s_tex->tex_u = s_tex->tex_su;
			s_tex->tex_v = s_tex->tex_sv;
			s_tex->tex_w = s_tex->tex_sw;

			s_tex->tstep = 1.0f / ((float)(s_tex->bx - s_tex->ax));
			t = 0.0f;
			j = s_tex->ax;
			while (j < s_tex->bx)
			{
				s_tex->tex_u = (1.0f - t) * s_tex->tex_su + t * s_tex->tex_eu;
				s_tex->tex_v = (1.0f - t) * s_tex->tex_sv + t * s_tex->tex_ev;
				s_tex->tex_w = (1.0f - t) * s_tex->tex_sw + t * s_tex->tex_ew;

				s_tex->srcrect.x = s_tex->tex_u / s_tex->tex_w * s_tex->tga->w;
				s_tex->srcrect.y = s_tex->tex_v / s_tex->tex_w * s_tex->tga->w;
				s_tex->dstrect.x = j;
				s_tex->dstrect.y = i;

				if ( (s_tex->srcrect.x + s_tex->srcrect.y * s_tex->tga->w) < 512 * 512)
				{
					if ((i * 1920 + j)   <  (1920 * 1080)   )
					{
						/* printf("%p || %p\n", (*pixel), (int*)(s_tex->tga->data)); */
						(*pixel)[i * 1920 + j] = ((int *)s_tex->tga->data)[(s_tex->srcrect.x + s_tex->srcrect.y * s_tex->tga->w)];
					}
				}
				j++;
				t += s_tex->tstep;
			}
			i++;
		}
	}
}
