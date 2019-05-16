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
	wn->color.rouge = making_color(255, 0, 0, 0);
	wn->color.vert = making_color(6, 141, 33, 0);
	wn->color.bleu = making_color(0, 0, 255, 0);
}

void create_text_texture(t_win *wn, SDL_Texture *texture, int x, SDL_Color color)
{
	wn->editext.surface = TTF_RenderText_Solid(wn->editext.police, ft_itoa(x), color);
	texture = SDL_CreateTextureFromSurface(wn->rend, wn->editext.surface);
	SDL_QueryTexture(texture, NULL, NULL, &wn->editext.src.w, &wn->editext.src.h);
	SDL_FreeSurface(wn->editext.surface);
	if (SDL_RenderCopy(wn->rend, texture, NULL, &wn->editext.src) < 0)
		stop_exec("rendercopy failed\n", wn);
}

void		print_x_y_z(t_win *wn)
{
	SDL_Texture *texture_x;
	SDL_Texture *texture_y;
	SDL_Texture *texture_z;
	int x;
	int y;

	texture_x = NULL;
	texture_y = NULL;
	texture_z = NULL;
	x = wn->input->x + wn->editext.countx;
	y = wn->input->y + wn->editext.county;
	x = (x * 600) / wn->map->w;
	y = (y * 600) / wn->map->h;
	if (x >= 0 && x <= wn->map->w && y <= wn->map->h && y >= 0)
	{
		wn->editext.src.x = wn->input->x + 10;
		wn->editext.src.y = wn->input->y + 1;
		create_text_texture(wn, texture_x, x, wn->color.rouge);
		wn->editext.src.y = wn->input->y + wn->editext.src.h;
		create_text_texture(wn, texture_y, y, wn->color.bleu);
		wn->editext.src.y += wn->editext.src.h;
		create_text_texture(wn, texture_z, 200, wn->color.vert);
	}
}

void		printeditor(t_win *wn)
{
	t_text	*bg;

	bg = findpostxt(wn, "editor", "intro", "119");
	bg != NULL && bg->txt != NULL ? SDL_RenderCopy(wn->rend, bg->txt, NULL, NULL) : 0;
	showmap(wn);
	print_x_y_z(wn);
}
