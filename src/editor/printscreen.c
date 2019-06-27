/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printscreen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 11:07:03 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/24 13:48:54 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	showelem(t_win *wn)
{
	t_elem		*curr;
	t_point		*point;
	t_point 	start;
	t_point 	end;

	curr = wn->elem;
	while (curr != NULL)
	{
		point = curr->point;
		SDL_SetRenderDrawColor(wn->rend, 255, 255, 255, 0);
		while (point != NULL && point->next != NULL)
		{
			start = create_t_point(point->x + wn->map->x, point->y + wn->map->y);
			end = create_t_point(point->next->x + wn->map->x, point->next->y + wn->map->y);
			bresenham(wn, &start, &end);
			point = point->next;
		}
		if (curr->next == NULL && point != NULL)
		{
			start = create_t_point(point->x + wn->map->x, point->y + wn->map->y);
			end = create_t_point(wn->input->x, wn->input->y);
			bresenham(wn, &start, &end);
		}
		curr = curr->next;
	}
}

static void	showline2(t_win *wn)
{
	float		i;
	float		j;
	t_point		start;
	t_point		end;

	j = wn->map->y;
	i = wn->map->x;
	if (wn->map->size > 1)
	{
		SDL_SetRenderDrawColor(wn->rend, 50 + (wn->map->size * 20 / 6),
				50 + (wn->map->size * 20 / 6),
				50 + (wn->map->size * 20 / 6), 0);
		while (j <= wn->map->y + wn->map->h)
		{
			start = create_t_point(wn->map->x, j);
			end = create_t_point(wn->map->w + wn->map->x, j);
			bresenham(wn, &start, &end);
			j += wn->map->h / 40;
		}
		j = wn->map->y;
		while (i <= wn->map->x + wn->map->w)
		{
			start = create_t_point(i, wn->map->y);
			end = create_t_point(i, wn->map->h + wn->map->y);
			bresenham(wn, &start, &end);
			i += wn->map->w / 40;
		}
	}
}

static void	showline(t_win *wn)
{
	float		i;
	float		j;
	t_point		start;
	t_point		end;

	j = wn->map->y;
	i = wn->map->x;
	showline2(wn);
	SDL_SetRenderDrawColor(wn->rend, 150, 100, 100, 0);
	while (j <= wn->map->y + wn->map->h + 1)
	{
		start = create_t_point(wn->map->x, j);
		end = create_t_point(wn->map->w + wn->map->x, j);
		bresenham(wn, &start, &end);
		j += wn->map->h / 10;
	}
	j = wn->map->y;
	while (i <= wn->map->x + wn->map->w + 1)
	{
		start = create_t_point(i, wn->map->y);
		end = create_t_point(i, wn->map->h + wn->map->y);
		bresenham(wn, &start, &end);
		i += wn->map->w / 10;
	}
}

void		showmap(t_win *wn)
{
	showline(wn);
	showelem(wn);
}

void		print_background_editor(t_win *wn)
{
	SDL_Surface		*surface;
	SDL_Texture		*texture;

	surface = SDL_CreateRGBSurface(0, wn->xscreen, wn->yscreen, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 66, 66, 66));
	texture = SDL_CreateTextureFromSurface(wn->rend, surface);
	SDL_FreeSurface(surface);
	if (SDL_RenderCopy(wn->rend, texture, NULL, NULL) < 0)
		stop_exec("rendercopy failed\n", wn);
}

int			is_between(double x, double min, double max)
{
	if (x >= min && x < max)
		return (0);
	return (1);
}

void		change_bloc(t_win *wn)
{
	int x;
	int y;

	x = wn->input->x;
	y = wn->input->y;
	if (is_between(x, 5.5 * wn->xscreen / 7, 5.75 * wn->xscreen / 7) == 0
		&& is_between(y, 0, 0.25 * wn->yscreen / 7) == 0)
		wn->edit_image.bgh = 1;
	else if (is_between(x, 5.5 * wn->xscreen / 7, 5.75 * wn->xscreen / 7) == 0
		&& is_between(y, 0.25, 0.5 * wn->yscreen / 7) == 0)
		wn->edit_image.bgh = 0;
	if (is_between(x, 6.75 * wn->xscreen / 7, wn->xscreen) == 0 && is_between(y, 3 *
		wn->yscreen / 7, 3.25 * wn->yscreen / 7) == 0 && wn->edit_image.in == 1)
		wn->edit_image.in = 0;
	else if (is_between(x, 6.75 * wn->xscreen / 7, wn->xscreen) == 0 && is_between(y, 5.75 *
		wn->yscreen / 7, 6 * wn->yscreen / 7) == 0 && wn->edit_image.in == 0)
		wn->edit_image.in = 1;
	if (is_between(x, 5.5 * wn->xscreen / 7, 5.75 * wn->xscreen / 7) == 0 && is_between(y, 3 *
		wn->yscreen / 7, 3.25 * wn->yscreen / 7) == 0 && wn->edit_image.in == 1)
		wn->edit_image.tbp = 0;
	if (is_between(x, 5.75 * wn->xscreen / 7, 6 * wn->xscreen / 7) == 0 && is_between(y, 3 *
		wn->yscreen / 7, 3.25 * wn->yscreen / 7) == 0 && wn->edit_image.in == 1)
		wn->edit_image.tbp = 1;
	if (is_between(x, 6 * wn->xscreen / 7, 6.25 * wn->xscreen / 7) == 0 && is_between(y, 3 *
		wn->yscreen / 7, 3.25 * wn->yscreen / 7) == 0 && wn->edit_image.in == 1)
		wn->edit_image.tbp = 2;
}

void		print_arrow(t_win *wn)
{
	SDL_Rect	dst;

	dst.x = 6.75 * wn->xscreen / 7;
	dst.w = 0.25 * wn->xscreen / 7;
	dst.h = 0.25 * wn->yscreen / 7;
	if (wn->edit_image.in == 1)
		dst.y = 3 * wn->yscreen / 7;
	else
		dst.y = 5.75 * wn->yscreen / 7;
	wn->edit_image.fleche = findtexture(wn, "editor", "affichage", "fleche");
	(wn->edit_image.fleche == NULL) ?
	stop_exec("fleche failed in print_arrow\n", wn) : 0;
	if (SDL_RenderCopy(wn->rend, wn->edit_image.fleche, NULL, &dst) < 0)
		stop_exec("rendercopy failed in print_arrow\n", wn);
}

void		print_tbp_editor(t_win *wn)
{
	SDL_Rect	src;
	SDL_Rect	dst;

	wn->edit_image.tbp == 0 ? wn->edit_image.texture_tbp =
	findtexture(wn, "editor", "affichage", "texts") : 0;
	wn->edit_image.tbp == 1 ? wn->edit_image.texture_tbp =
	findtexture(wn, "editor", "affichage", "blocs") : 0;
	wn->edit_image.tbp == 2 ? wn->edit_image.texture_tbp =
	findtexture(wn, "editor", "affichage", "params") : 0;
	(wn->edit_image.texture_tbp == NULL) ?
	stop_exec("texture params failed in print_tbp\n", wn) : 0;
	SDL_QueryTexture(wn->edit_image.texture_tbp, NULL, NULL, &src.w, &src.h);
	if (wn->edit_image.in == 1)
	{
		src.x = 0;
		src.y = 0;
		dst = define_rect(5.5 * wn->xscreen / 7, 3 * wn->yscreen / 7,
			1.5 * wn->xscreen / 7, 3 * wn->yscreen / 7);
	}
	else 
	{
		src.x = 0;
		src.y = 0;
		src.h = 0.25 * src.h / 7;
		dst = define_rect(5.5 * wn->xscreen / 7, 5.75 * wn->yscreen / 7,
			1.5 * wn->xscreen / 7, 0.25 * wn->yscreen / 7);
	}
	if (SDL_RenderCopy(wn->rend, wn->edit_image.texture_tbp, &src, &dst) < 0)
		stop_exec("render copy failed in print_tbp\n", wn);
	print_arrow(wn);
}

void		print_tools_editor(t_win *wn)
{
	SDL_Rect	dst;

	dst.x = 0;
	dst.y = wn->yscreen / 7 * 6;
	dst.w = wn->xscreen;
	dst.h = wn->yscreen / 7;
	wn->edit_image.texture_tools =
	findtexture(wn, "editor", "affichage", "tools");
	if (wn->edit_image.texture_tools == NULL)
		stop_exec("texture print_tools_editor failed\n", wn);
	if (SDL_RenderCopy(wn->rend, wn->edit_image.texture_tools, NULL, &dst) < 0)
		stop_exec("rendercopy failed in print_tools_editor\n", wn);
}

void		printeditor(t_win *wn)
{
	print_background_editor(wn);
	// (is_path_ok(wn, wn->bg_map.path) == 0 && wn->edit_image.bgh == 0) ? load_background(wn) : 0;
	showmap(wn);
	which_cursor(wn);
	print_tools_editor(wn);
	print_bgh_editor(wn);
	print_tbp_editor(wn);
	wn->editext.on == 1 ? print_x_y_z(wn) : 0;
}
