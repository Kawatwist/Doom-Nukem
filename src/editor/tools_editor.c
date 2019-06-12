/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:51:44 by llejeune          #+#    #+#             */
/*   Updated: 2019/06/11 14:51:47 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

SDL_Color 	making_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	SDL_Color color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

void		load_color(t_win *wn)
{
	wn->color.noir = making_color(0, 0, 0, 0);
	wn->color.violetfonce = making_color(188, 7, 237, 0);
	wn->color.violet = making_color(199, 62, 236, 0);
	wn->color.violetrose = making_color(212, 115, 238, 0);
	wn->color.red = making_color(255, 255, 255, 0);
}

SDL_Rect	define_rect(int x, int y, int w, int h)
{
	SDL_Rect 	rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}

t_point		create_t_point(int x, int y)
{
	t_point new;

	new.x = x;
	new.y = y;
	return (new);
}