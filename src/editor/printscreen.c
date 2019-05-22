/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printscreen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 11:07:03 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/12 13:01:36 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	showelem(t_win *wn)
{
	t_elem		*curr;
	t_point		*point;

	curr = wn->elem;
	while (curr != NULL)
	{
		point = curr->point;
		while (point != NULL && point->next != NULL)
		{
			SDL_SetRenderDrawColor(wn->rend, 255, 255, 255, 0);
			SDL_RenderDrawLine(wn->rend, point->x, point->y, point->next->x, point->next->y);
			SDL_SetRenderDrawColor(wn->rend, 0, 0, 0, 0);
			SDL_RenderDrawLine(wn->rend, point->x, point->y + 1, point->next->x, point->next->y + 1);
			point = point->next;
		}
		curr = curr->next;
	}
}

static void	showline2(t_win *wn)
{
	float		i;
	float		j;

	j = wn->map->y;
	i = wn->map->x;
	if (wn->map->size > 1)
	{
		SDL_SetRenderDrawColor(wn->rend, 50 + (wn->map->size * 20 / 6),
				50 + (wn->map->size * 20 / 6),
				50 + (wn->map->size * 20 / 6), 0);
		while (j <= wn->map->y + wn->map->h)
		{
			SDL_RenderDrawLine(wn->rend, wn->map->x, j,
					wn->map->w + wn->map->x, j);
			j += wn->map->h / 40;
		}
		j = wn->map->y;
		while (i <= wn->map->x + wn->map->w)
		{
			SDL_RenderDrawLine(wn->rend, i, wn->map->y, i,
					wn->map->h + wn->map->y);
			i += wn->map->w / 40;
		}
	}
}

static void	showline(t_win *wn)
{
	float		i;
	float		j;

	j = wn->map->y;
	i = wn->map->x;
	showline2(wn);
	SDL_SetRenderDrawColor(wn->rend, 150, 100, 100, 0);
	while (j <= wn->map->y + wn->map->h + 1)
	{
		SDL_RenderDrawLine(wn->rend, wn->map->x, j, wn->map->w + wn->map->x, j);
		j += wn->map->h / 10;
	}
	j = wn->map->y;
	while (i <= wn->map->x + wn->map->w + 1)
	{
		SDL_RenderDrawLine(wn->rend, i, wn->map->y, i, wn->map->h + wn->map->y);
		i += wn->map->w / 10;
	}
}

static void	showmap(t_win *wn)
{
	showline(wn);
	showelem(wn);
}

SDL_Color making_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	SDL_Color color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

void	load_color(t_win *wn)
{
	wn->color.noir = making_color(0, 0, 0, 0);
	wn->color.violetfonce = making_color(188, 7, 237, 0);
	wn->color.violet = making_color(199, 62, 236, 0);
	wn->color.violetrose = making_color(212, 115, 238, 0);
}

void create_text_texture(t_win *wn, SDL_Texture *texture, int x, SDL_Color color)
{
	texture != NULL ? SDL_DestroyTexture(texture) : 0;
	wn->editext.surface = TTF_RenderText_Solid(wn->fonts->arial, ft_itoa(x), color);
	texture = SDL_CreateTextureFromSurface(wn->rend, wn->editext.surface);
	SDL_QueryTexture(texture, NULL, NULL, &wn->editext.src.w, &wn->editext.src.h);
	SDL_FreeSurface(wn->editext.surface);
	if (SDL_RenderCopy(wn->rend, texture, NULL, &wn->editext.src) < 0)
		stop_exec("rendercopy failed\n", wn);
}

void		init_edit(t_win **wn)
{
	load_color(*wn);
	(*wn)->editext.texture_x = NULL;
	(*wn)->editext.texture_y = NULL;
	(*wn)->editext.texture_z = NULL;
	(*wn)->editext.on = 1;
	(*wn)->editext.map_w = 600;
	(*wn)->editext.map_h = 600;
}

void		print_x_y_z(t_win *wn)
{
	int x;
	int y;

	x = ((wn->input->x - wn->map->x) * wn->editext.map_w) / wn->map->w;
	y = ((wn->input->y - wn->map->y) * wn->editext.map_h) / wn->map->h;
	if (x >= 0 && x <= wn->editext.map_w && y <= wn->editext.map_h && y >= 0)
	{
		wn->editext.src.x = wn->input->x + 10;
		wn->editext.src.y = wn->input->y + 1;
		create_text_texture(wn, wn->editext.texture_x, x, wn->color.violetfonce);
		wn->editext.src.y = wn->input->y + wn->editext.src.h;
		create_text_texture(wn, wn->editext.texture_y, y, wn->color.violet);
		wn->editext.src.y += wn->editext.src.h;
		create_text_texture(wn, wn->editext.texture_z, 200, wn->color.violetrose);
	}
}

void		printeditor(t_win *wn)
{
	SDL_Surface 	*surface;
	SDL_Texture 	*texture;

	surface = SDL_CreateRGBSurface(0, wn->xscreen, wn->yscreen, 32, 0, 0, 0, 0);
	surface == NULL ? stop_exec("surface failed\n", wn) : 0;
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 66, 66, 66));
	texture = SDL_CreateTextureFromSurface(wn->rend, surface);
	SDL_FreeSurface(surface);
	if (SDL_RenderCopy(wn->rend, texture, NULL, NULL) < 0)
		stop_exec("rendercopy failed\n", wn);
	showmap(wn);
	which_cursor(wn);
	wn->editext.on == 1 ? print_x_y_z(wn) : 0;
}
