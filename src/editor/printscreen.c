/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printscreen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 11:07:03 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/05 16:45:42 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	showelem(t_win *wn)
{
	t_elem		*curr;
	SDL_Rect	rect;

	curr = wn->elem;
	while (curr != NULL)
	{
		SDL_SetRenderDrawColor(wn->rend, 200, 200, 200, 0);
		if (ft_strcmp(curr->name, "Line") == 0)
		{
			SDL_RenderDrawLine(wn->rend,
					(curr->x1 * wn->map->size) + wn->map->x,
					(curr->y1 * wn->map->size) + wn->map->y,
					(curr->x2 * wn->map->size) + wn->map->x,
					(curr->y2 * wn->map->size) + wn->map->y);
		}
		else if (ft_strcmp(curr->name, "Rect") == 0)
		{
			rect.x = (curr->x1 * wn->map->size) + wn->map->x;
			rect.y = (curr->y1 * wn->map->size) + wn->map->y;
			rect.h = (curr->x2 * wn->map->size);
			rect.w = (curr->y2 * wn->map->size);
			SDL_RenderDrawRect(wn->rend, &rect);
		}
		if (curr->next == NULL)
			break ;
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

static void		print_x_y_z(t_win *wn)
{
	SDL_Color color;
	TTF_Font *police;
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Rect 	src;

	color.a = 0;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	src.x = wn->input->x;
	src.y = wn->input->y;
	if (!(police = TTF_OpenFont("./texture/arial.ttf", 14)))
		stop_exec("police failed\n", wn);
	surface = TTF_RenderText_Solid(police, ft_itoa(wn->input->x), color);
	texture = SDL_CreateTextureFromSurface(wn->rend, surface);
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
	if (SDL_RenderCopy(wn->rend, texture, NULL, &src) < 0)
		stop_exec("rendercopy failed\n", wn);
}

void		printeditor(t_win *wn)
{
	t_text	*bg;

	bg = findpostxt(wn, "editor", "intro", "119");
	bg != NULL && bg->txt != NULL ? SDL_RenderCopy(wn->rend, bg->txt, NULL, NULL) : 0;
	showmap(wn);
	print_x_y_z(wn);
}
