/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_textured_triangle.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:09:20 by jchardin          #+#    #+#             */
/*   Updated: 2019/08/21 11:18:42 by jchardin         ###   ########.fr       */
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

//



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
	*b = *a;
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
	(void)texture;
	//sorting base on the y coordinate
	ft_order_point(
			&x1, &y1, &u1, &v1, &w1,
			&x2, &y2, &u2, &v2, &w2,
			&x3, &y3, &u3, &v3, &w3);
	/* printf("Le triangle order : %d < %d < %d\n", y1, y2, y3); */
	/* printf("u1  %f u2  %f u3 %f\n", u1, u2, u3); */
	/* printf("v1  %f v2 %f  v3 %f\n", v1, v2, v3); */



	 printf("x1=%d y1=%d u1=%f v1=%f\n", x1, y1, u1, v1);
	 printf("x2=%d y2=%d u2=%f v2=%f\n", x2, y2, u2, v2);
	 printf("x3=%d y3=%d u3=%f v3=%f\n", x3, y3, u3, v3);

	int		j;
	int		i;
	int		dy1;			float	dv1;
	int		dx1;			float	du1;
	int		dy2;			float	dv2;
	int		dx2;			float	du2;
	float	dax_step = 0;	float	du1_step = 0;	float	dv1_step = 0;
	float	dbx_step = 0;	float	du2_step = 0;	float	dv2_step = 0;
	int		ax;				//float	au;
	int		bx;				//float	bu;

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
/*	on draw le triangle du haut             to half        en bleu                          */ 
/* ************************************************************************** */

/* ########             DRAWING                         #########################*/

	int count = 0;

	if (dy1 > 0)
	{
		printf("NEW TRIANGLE =============================================\n");
		printf("UV MAP 1 = %f || %f\n", u1,v1);
		printf("UV MAP 2 = %f || %f\n", u2,v2);
		printf("UV MAP 3 = %f || %f\n", u3,v3);
		printf("on draw le triangle du haut (flat bottom)\n");
		SDL_SetRenderDrawColor(wn->rend, 0, 0, 255, 255);
		i = y1;
		while (i < y2)
		{
			/* printf("new line ########################################################################3\n"); */
			ax = x1 + (float)(i - y1) * dax_step;
			bx = x1 + (float)(i - y1) * dbx_step;

			float tex_su = u1 + (float)(i - y1) * du1_step;
			float tex_sv = v1 + (float)(i - y1) * dv1_step;
			/* float tex_sw = w1 + (float)(i - y1) * dw1_step; */

			float tex_eu = u1 + (float)(i - y1) * du2_step;
			float tex_ev = v1 + (float)(i - y1) * dv2_step;
			/* float tex_ew = w1 + (float)(i - y1) * dw2_step; */
			if (ax > bx)
			{
				ft_swap_int(&ax, &bx);
				ft_swap_float(&tex_su, &tex_eu);
				ft_swap_float(&tex_sv, &tex_ev);
				/* ft_swap_float(tex_sw, tex_ew); */
			}

			tex_u = tex_su;
			tex_v = tex_sv;
			tstep = 1.0 / ((float)(bx - ax));
			/* printf("le step =%f\n", tstep); */
			float t = 0.0;


			j = ax;
			while (j < bx)
			 {
				 //on draw
				 //metre ici le render copy au lieu du draw point
				SDL_RenderDrawPoint(wn->rend, j, i);

				 tex_u = (1.0 - t) * tex_su + t * tex_eu;
				 tex_v = (1.0 - t) * tex_sv + t * tex_ev;
				 t += tstep;
				 srcrect.x = tex_u * 512;//image_x = tex_u * length_x;
				 srcrect.y = tex_v * 512;//image_y = tex_v * length_y;
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
			//SDL_Delay(200);
				 /* printf("le u =%f\n", tex_u); */
				 /* printf("le v =%f\n", tex_v); */
				 /* printf("le x image = %d", srcrect.x); */
				 /* printf("le y image = %d\n", srcrect.y); */
				i++;/* i += 5; */
		}
	}

/* ************************************************************************** */
/*	on draw le triangle du bas                                                */
/* ************************************************************************** */
	dy1 = y3 - y2;
	dx1 = x3 - x2;




	if (dy1)
		dax_step = dx1 / (float)abs(dy1);
	if (dy2)
		dbx_step = dx2 / (float)abs(dy2);
/* ########             DRAWING       green                  #########################*/
	if (dy1 > 0)
	{
		printf("on draw le triangle du bas (flat up)\n");
		SDL_SetRenderDrawColor(wn->rend, 0, 255, 0, 255);
		i = y2;
		while (i < y3)
		{
			ax = x2 + (float)(i - y2) * dax_step;
			bx = x1 + (float)(i - y1) * dbx_step;


			/* float tex_su = u2 + (float)(i - y2) * du1_step; */
			/* float tex_sv = v2 + (float)(i - y2) * dv1_step; */
			/* float tex_sw = w2 + (float)(i - y2) * dw1_step; */

			/* float tex_eu = u1 + (float)(i - y1) * du2_step; */
			/* float tex_ev = v1 + (float)(i - y1) * dv2_step; */
			/* float tex_ew = w1 + (float)(i - y1) * dw2_step; */
			if (ax > bx)
			{
				ft_swap_int(&ax, &bx);
				/* ft_swap_float(tex_su, tex_eu); */
				/* ft_swap_float(tex_sv, tex_ev); */
				/* ft_swap_float(tex_sw, tex_ew); */
			}
			j = ax;
			while (j < bx)
			{
				//on draw
				//metre ici le render copy au lieu du draw point
				SDL_RenderDrawPoint(wn->rend, j, i);
				j++;
			}
			i += 5;
		}
	}
// 	if (((t_myraster *)wn->rasterizer->tmp)->debug)
// 	{
// 		SDL_RenderPresent(wn->rend);
// 		char *line;

// line = NULL;
// 		get_next_line(0, &line);
// 	}
}
