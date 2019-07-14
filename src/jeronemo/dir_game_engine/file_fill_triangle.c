/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_fill_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 19:59:02 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/14 17:43:43 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>
#include <header_bresenham.h>

void	ft_order_triangle_vertice(t_myvec *v1, t_myvec *v2, t_myvec *v3)
{
	t_myvec		temp;
	int			j;
	int			i;
	t_myvec		tab[3];

	tab[0] =  *v1;
	tab[1] =  *v2;
	tab[2] =  *v3;
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 2)
		{
			if (tab[j].y > tab[j + 1].y)
			{
				temp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = temp;
				i = 0;
			}
			j++;
		}
		i++;
	}
	*v1 = tab[0];
	*v2 = tab[1];
	*v3 = tab[2];
}

void	ft_fill_bottom_flat_triangle(t_myvec *v1, t_myvec *v2, t_myvec *v3, t_win *wn)
{
	float				invslope1;
	float				invslope2;
	float				curx1;
	float				curx2;
	t_myputtheline		s_line;;
	int					scanline_y;

	invslope1 = (v2->x - v1->x) / (v2->y - v1->y);
	invslope2 = (v3->x - v1->x) / (v3->y - v1->y);
	curx1 = v1->x;
	curx2 = v1->x;
	scanline_y = v1->y;
	while (scanline_y < v2->y - 1)
	{
		s_line.un.a = (int)curx1;
		s_line.un.b = scanline_y;
		s_line.deux.a = (int)curx2;
		s_line.deux.b = scanline_y;
		ft_draw_line(wn, &s_line);
		curx1 += invslope1;
		curx2 += invslope2;
		scanline_y++;
	}
}

void	ft_fill_top_flat_triangle(t_myvec *v1, t_myvec *v2, t_myvec *v3, t_win *wn)
{
	float	invslope1 = (v3->x - v1->x) / (v3->y - v1->y);
	float	invslope2 = (v3->x - v2->x) / (v3->y - v2->y);

	float	curx1 = v3->x;
	float	curx2 = v3->x;
	t_myputtheline		s_line;;

	int		scanline_y = v3->y;
	while (scanline_y > v1->y)
	{
		s_line.un.a = (int)curx1;
		s_line.un.b = scanline_y;
		s_line.deux.a = (int)curx2;
		s_line.deux.b = scanline_y;
		ft_draw_line(wn, &s_line);
		curx1 -= invslope1;
		curx2 -= invslope2;
		scanline_y--;
	}
}

void	ft_fill_triangle_one_color(t_myvec *v1, t_myvec *v2, t_myvec *v3, t_win *wn)
{
	t_myvec				v4;
	t_myputtheline		s_line;;

	if (v2->y == v3->y)
		ft_fill_bottom_flat_triangle(v1, v2, v3, wn);
	else if (v1->y == v2->y)
		ft_fill_top_flat_triangle(v1, v2, v3, wn);
	else
	{
		v4.y = v2->y;
		v4.x = v1->x + ((v2->y - v1->y) / (v3->y - v1->y)) * (v3->x - v1->x);
		s_line.un.a = v2->x;
		s_line.un.b = v2->y;
		s_line.deux.a = v4.x;
		s_line.deux.b = v4.y;
		ft_draw_line(wn, &s_line);
		ft_fill_bottom_flat_triangle(v1, v2, &v4, wn);
		ft_fill_top_flat_triangle(v2, &v4, v3, wn);
	}
}

// TEST WITH COLOR
void	ft_fill_triangle_shade(t_mytriangle t, t_win *wn, float shade)
{
	t_myvec				v4;
	t_myputtheline		s_line;;

	//color = ft_setcolor(GREEN);
	ft_order_triangle_vertice(&t.vertice[0], &t.vertice[1], &t.vertice[2]);
	if (shade > 0)
		shade *= 165;
	else
		shade = 150;
	printf("COLOR => %d\n", t.ft_color);
	t.ft_color = 103 ? SDL_SetRenderDrawColor(wn->rend, 0, 255 - shade, 0, 255) : 0;
	t.ft_color = 114 ? SDL_SetRenderDrawColor(wn->rend, 255 - shade, 0, 0, 255) : 0;
	t.ft_color = 67 ? SDL_SetRenderDrawColor(wn->rend, 0, 0, 255 - shade, 255) : 0;
	if (t.vertice[1].y == t.vertice[2].y)
		ft_fill_bottom_flat_triangle(&t.vertice[0], &t.vertice[1], &t.vertice[2], wn);
	else if (t.vertice[0].y == t.vertice[1].y)
		ft_fill_top_flat_triangle(&t.vertice[0], &t.vertice[1], &t.vertice[2], wn);
	else
	{
		v4.y = t.vertice[1].y;
		v4.x = t.vertice[0].x + ((t.vertice[1].y - t.vertice[0].y) / (t.vertice[2].y - t.vertice[0].y)) * (t.vertice[2].x - t.vertice[0].x);
		s_line.un.a = t.vertice[1].x;
		s_line.un.b = t.vertice[1].y;
		s_line.deux.a = v4.x;
		s_line.deux.b = v4.y;
		ft_draw_line(wn, &s_line);
		ft_fill_bottom_flat_triangle(&t.vertice[0], &t.vertice[1], &v4, wn);
		ft_fill_top_flat_triangle(&t.vertice[1], &v4, &t.vertice[2], wn);
	}
}

/*
void	ft_fill_triangle_shade(t_myvec v1, t_myvec v2, t_myvec v3, t_win *wn, float shade)
{
	t_myvec				v4;
	t_myputtheline		s_line;;
	t_mycolor			color;

	color = ft_setcolor(GREEN);
	ft_order_triangle_vertice(&v1, &v2, &v3);
	if (shade > 0)
	{
		shade *= 165;
	}
	else
	{
		shade = 150;
	}
	SDL_SetRenderDrawColor(wn->rend, 0, color.ggg - shade, 0, 255);
	if (v2.y == v3.y)
		ft_fill_bottom_flat_triangle(&v1, &v2, &v3, wn);
	else if (v1.y == v2.y)
		ft_fill_top_flat_triangle(&v1, &v2, &v3, wn);
	else
	{
		v4.y = v2.y;
		v4.x = v1.x + ((v2.y - v1.y) / (v3.y - v1.y)) * (v3.x - v1.x);
		s_line.un.a = v2.x;
		s_line.un.b = v2.y;
		s_line.deux.a = v4.x;
		s_line.deux.b = v4.y;
		ft_draw_line(wn, &s_line);
		ft_fill_bottom_flat_triangle(&v1, &v2, &v4, wn);
		ft_fill_top_flat_triangle(&v2, &v4, &v3, wn);
	}
}
*/
