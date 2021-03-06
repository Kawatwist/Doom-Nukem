/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_textured_triangle.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:09:20 by jchardin          #+#    #+#             */
/*   Updated: 2019/08/25 19:41:52 by jchardin         ###   ########.fr       */
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
		int *x1, int *y1, float *u1, float *v1, float *w1,
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

void correct_limits(float *value, float min, float max) //focntion qui s'assure que la valeur est bien dans les bonnes limites
{
	if (*value < min)
		*value = min;
	if (*value > max)
		*value = max;
}

void	ft_draw_textured_triangle(t_mytriangle *tri, t_mytext *s_tex, float *depth_buffer)
{

	int		x1 = tri->vertice[0].x;
	int		y1 = tri->vertice[0].y;
	float	u1 = tri->texture[0].u;
	float	v1 = tri->texture[0].v;
	float	w1 = tri->texture[0].w;
	int		x2 = tri->vertice[1].x;
	int		y2 = tri->vertice[1].y;
	float	u2 = tri->texture[1].u;
	float	v2 = tri->texture[1].v;
	float	w2 = tri->texture[1].w;
	int		x3 = tri->vertice[2].x;
	int		y3 = tri->vertice[2].y;
	float	u3 = tri->texture[2].u;
	float	v3 = tri->texture[2].v;
	float	w3 = tri->texture[2].w;
	int		j;
	int		i;
	float	t;

	// printf("le u1=%f le v1=%f le w1=%f\n", u1, v1, w1); 
	// printf("le u2=%f le v2=%f le w2=%f\n", u2, v2, w2); 
	// printf("le u3=%f le v3=%f le w3=%f\n", u3, v3, w3); 

	s_tex->dax_step = 0;
	s_tex->dbx_step = 0;
	s_tex->du1_step = 0;
	s_tex->dv1_step = 0;
	s_tex->du2_step = 0;
	s_tex->dv2_step = 0;
	s_tex->dw1_step = 0;
	s_tex->dw2_step = 0;

	ft_order_point( &x1, &y1, &u1, &v1, &w1, &x2, &y2, &u2, &v2, &w2, &x3, &y3, &u3, &v3, &w3);

	/* ************************************************************************/
	/*	on draw le triangle du haut        bleu                               */
	/* ************************************************************************/
	s_tex->dy1 = y2 - y1;
	s_tex->dv1 = v2 - v1;
	s_tex->dx1 = x2 - x1;
	s_tex->du1 = u2 - u1;
	s_tex->dw1 = w2 - w1;
	s_tex->dy2 = y3 - y1;
	s_tex->dv2 = v3 - v1;
	s_tex->dx2 = x3 - x1;
	s_tex->du2 = u3 - u1;
	s_tex->dw2 = w3 - w1;

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
		i = y1;
		while (i < y2)
		{
			s_tex->ax = x1 + (float)(i - y1) * s_tex->dax_step;
			if (s_tex->ax < 0)//pour evietr overflow
				s_tex->ax = 0;
			if (s_tex->ax > 1919)
				s_tex->ax = 1919;
			s_tex->bx = x1 + (float)(i - y1) * s_tex->dbx_step;
			if (s_tex->bx < 0)
				s_tex->bx = 0;
			if (s_tex->bx > 1919)
				s_tex->bx = 1919;

			s_tex->tex_su = u1 + (float)(i - y1) * s_tex->du1_step;
			s_tex->tex_sv = v1 + (float)(i - y1) * s_tex->dv1_step;
			s_tex->tex_sw = w1 + (float)(i - y1) * s_tex->dw1_step;

			s_tex->tex_eu = u1 + (float)(i - y1) * s_tex->du2_step;
			s_tex->tex_ev = v1 + (float)(i - y1) * s_tex->dv2_step;
			s_tex->tex_ew = w1 + (float)(i - y1) * s_tex->dw2_step;

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

		/**	//optimisation coco

			s_tex->tex_u = (1.0f - t) * s_tex->tex_su + t * s_tex->tex_eu;
			s_tex->tex_v = (1.0f - t) * s_tex->tex_sv + t * s_tex->tex_ev;
			s_tex->tex_w = (1.0f - t) * s_tex->tex_sw + t * s_tex->tex_ew;
			s_tex->tex_u_step = ((1.0f - (t + s_tex->tstep)) * s_tex->tex_su + (t + s_tex->tstep) * s_tex->tex_eu) -
								((1.0f - t) * s_tex->tex_su + t * s_tex->tex_eu);
			s_tex->tex_v_step = ((1.0f - (t + s_tex->tstep)) * s_tex->tex_sv + (t + s_tex->tstep) * s_tex->tex_ev) -
								((1.0f - t) * s_tex->tex_sv + t * s_tex->tex_ev);
			s_tex->tex_w_step = ((1.0f - (t + s_tex->tstep)) * s_tex->tex_sw + (t + s_tex->tstep) * s_tex->tex_ew) -
								((1.0f - t) * s_tex->tex_sw + t * s_tex->tex_ew); **/

			while (j < s_tex->bx)
			{
				s_tex->tex_w = (1.0 - t) * s_tex->tex_sw + t * s_tex->tex_ew;

				if (s_tex->tex_w > depth_buffer[i * XSCREEN + j])
				{
					s_tex->tex_u = (1.0 - t) * s_tex->tex_su + t * s_tex->tex_eu;
					s_tex->tex_v = (1.0 - t) * s_tex->tex_sv + t * s_tex->tex_ev;
					//s_tex->tex_w = (1.0 - t) * s_tex->tex_sw + t * s_tex->tex_ew;

					/** s_tex->tex_u = s_tex->tex_u + s_tex->tex_u_step;
					s_tex->tex_v = s_tex->tex_v + s_tex->tex_v_step;
					s_tex->tex_w = s_tex->tex_w + s_tex->tex_w_step; **/
				
				//printf("PRE %f %f %f %d\n", s_tex->tex_u, s_tex->tex_v, s_tex->tex_w, s_tex->tga->w);
					s_tex->srcrect.x = s_tex->tex_u / s_tex->tex_w * s_tex->tga->w;
					if (s_tex->srcrect.x > 511)
						s_tex->srcrect.x = 511;
					if (s_tex->srcrect.x < 0)
						s_tex->srcrect.x = 0; 
					s_tex->srcrect.y = s_tex->tex_v / s_tex->tex_w * s_tex->tga->w;
					if (s_tex->srcrect.y > 511)
						s_tex->srcrect.y = 511;
					if (s_tex->srcrect.y < 0)
						s_tex->srcrect.y = 0; 
					s_tex->dstrect.x = j;
					s_tex->dstrect.y = i;
					//printf("DEBUG %d %d %d\n", s_tex->bx , s_tex->ax, s_tex->tga->w);

					//if ((s_tex->srcrect.x + s_tex->srcrect.y * s_tex->tga->w) < 512 * 512)
					//{
						//if (s_tex->tex_w > depth_buffer[i * XSCREEN + j] )
					 	//{
					 		//printf("DEBUG %f %f %f\n", tri->vertice[0].z, tri->vertice[1].z, tri->vertice[2].z);
							s_tex->m_pPixels[i * XSCREEN + j] = ((int *)s_tex->tga->data)[(s_tex->srcrect.x + s_tex->srcrect.y * s_tex->tga->w)];
							depth_buffer[i * XSCREEN + j] = s_tex->tex_w;
						//}
					//}
				}
				t += s_tex->tstep;
				// s_tex->m_pPixels[i * 1920 + j] = 0x00FF00FF;

			/* printf("s_tex->tex_w=%f\n", s_tex->tex_w); */

				/* SDL_RenderCopy(wn->rend, texture, &(s_tex->srcrect), &(s_tex->dstrect)); */
				j++;
			}
			i++;
		}
	}
	/**************************************************************************/
	/*	on draw le triangle du bas                                            */
	/**************************************************************************/
	s_tex->dy1 = y3 - y2;
	s_tex->dx1 = x3 - x2;
	s_tex->dv1 = v3 - v2;
	s_tex->du1 = u3 - u2;
	s_tex->dw1 = w3 - w2;
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
		i = y2;
		while (i < y3)
		{
			s_tex->ax = x2 + (float)(i - y2) * s_tex->dax_step;
			if (s_tex->ax < 0)//pour evietr overflow
				s_tex->ax = 0;
			if (s_tex->ax > 1919)
				s_tex->ax = 1919;
			s_tex->bx = x1 + (float)(i - y1) * s_tex->dbx_step;
			if (s_tex->bx < 0)
				s_tex->bx = 0;
			if (s_tex->bx > 1919)
				s_tex->bx = 1919;
			s_tex->tex_su = u2 + (float)(i - y2) * s_tex->du1_step;
			s_tex->tex_sv = v2 + (float)(i - y2) * s_tex->dv1_step;
			s_tex->tex_sw = w2 + (float)(i - y2) * s_tex->dw1_step;

			s_tex->tex_eu = u1 + (float)(i - y1) * s_tex->du2_step;
			s_tex->tex_ev = v1 + (float)(i - y1) * s_tex->dv2_step;
			s_tex->tex_ew = w1 + (float)(i - y1) * s_tex->dw2_step;
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

		/**	//optimisation coco

			s_tex->tex_u = (1.0f - t) * s_tex->tex_su + t * s_tex->tex_eu;
			s_tex->tex_v = (1.0f - t) * s_tex->tex_sv + t * s_tex->tex_ev;
			s_tex->tex_w = (1.0f - t) * s_tex->tex_sw + t * s_tex->tex_ew;
			s_tex->tex_u_step = ((1.0f - (t + s_tex->tstep)) * s_tex->tex_su + (t + s_tex->tstep) * s_tex->tex_eu) -
								((1.0f - t) * s_tex->tex_su + t * s_tex->tex_eu);
			s_tex->tex_v_step = ((1.0f - (t + s_tex->tstep)) * s_tex->tex_sv + (t + s_tex->tstep) * s_tex->tex_ev) -
								((1.0f - t) * s_tex->tex_sv + t * s_tex->tex_ev);
			s_tex->tex_w_step = ((1.0f - (t + s_tex->tstep)) * s_tex->tex_sw + (t + s_tex->tstep) * s_tex->tex_ew) -
								((1.0f - t) * s_tex->tex_sw + t * s_tex->tex_ew); **/

			while (j < s_tex->bx)
			{
				s_tex->tex_w = (1.0f - t) * s_tex->tex_sw + t * s_tex->tex_ew;

				if (s_tex->tex_w > depth_buffer[i * XSCREEN + j])
				{
					s_tex->tex_u = (1.0f - t) * s_tex->tex_su + t * s_tex->tex_eu;
					s_tex->tex_v = (1.0f - t) * s_tex->tex_sv + t * s_tex->tex_ev;
					//s_tex->tex_w = (1.0f - t) * s_tex->tex_sw + t * s_tex->tex_ew;

				/**s_tex->tex_u = s_tex->tex_u + s_tex->tex_u_step;
				s_tex->tex_v = s_tex->tex_v + s_tex->tex_v_step;
				s_tex->tex_w = s_tex->tex_w + s_tex->tex_w_step; **/

					s_tex->srcrect.x = s_tex->tex_u / s_tex->tex_w * s_tex->tga->w;
					if (s_tex->srcrect.x > 511)
						s_tex->srcrect.x = 511;
					if (s_tex->srcrect.x < 0)
						s_tex->srcrect.x = 0;
					s_tex->srcrect.y = s_tex->tex_v / s_tex->tex_w * s_tex->tga->w;
					if (s_tex->srcrect.y > 511)
						s_tex->srcrect.y = 511;
					if (s_tex->srcrect.y < 0)
						s_tex->srcrect.y = 0;
					s_tex->dstrect.x = j;
					s_tex->dstrect.y = i;
				/* s_tex->m_pPixels[i * 1920 + j] = 0x00FF00FF; */


					//if ((s_tex->srcrect.x + s_tex->srcrect.y * s_tex->tga->w) < 512 * 512)
					//{
						// if (s_tex->tex_w > depth_buffer[i * XSCREEN + j])
					 	//{
							s_tex->m_pPixels[i * XSCREEN + j] = ((int *)s_tex->tga->data)[(s_tex->srcrect.x + s_tex->srcrect.y * s_tex->tga->w)];
							depth_buffer[i * XSCREEN + j] = s_tex->tex_w;
					 	//}
					//}
				// s_tex->m_pPixels[i * 1920 + j] = 0x00FF00FF;
				}
				/* SDL_RenderCopy(wn->rend, texture, &(s_tex->srcrect), &(s_tex->dstrect)); */
				j++;
				t += s_tex->tstep;
			}
			i++;
		}
	}
}
