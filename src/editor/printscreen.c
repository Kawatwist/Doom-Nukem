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
	// t_point 	start;
	// t_point 	end;

	curr = wn->elem;
	while (curr != NULL)
	{
		point = curr->point;
		while (point != NULL && point->next != NULL)
		{
			printf("next x = %d, y = %d\n", point->next->x, point->next->y);
			SDL_SetRenderDrawColor(wn->rend, 255, 255, 255, 0);
			// start = create_t_point(point->x, point->y);
			// if (point->next != NULL)
				SDL_RenderDrawLine(wn->rend, point->x, point->y, point->next->x, point->next->y);
			// 	end = create_t_point(point->next->x, point->next->y);
			// else
				// SDL_RenderDrawLine(wn->rend, point->x, point->y, wn->input->x, wn->input->y);
			// 	end = create_t_point(point->x + 10, point->y + 10);
			// bresenham(wn, &start, &end);
			// SDL_SetRenderDrawColor(wn->rend, 0, 0, 0, 0);
			// start = create_t_point(point->x, point->y + 1);
			// if (point->next != NULL)
				// SDL_RenderDrawLine(wn->rend, point->x, point->y, point->next->x, point->next->y + 1);
			// 	end = create_t_point(point->next->x + 1, point->next->y + 2);
			// else
				// SDL_RenderDrawLine(wn->rend, point->x, point->y, wn->input->x, wn->input->y + 1);
			// 	end = create_t_point(point->x + 10, point->y + 11);
			// // end = create_t_point(point->next->x, point->next->y + 1);
			// bresenham(wn, &start, &end);
			point = point->next;
		}
		curr = curr->next;
	}
}

static void	showline2(t_win *wn)
{
	float		i;
	float		j;
	t_point start;
	t_point end;

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
	t_point start;
	t_point end;

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

SDL_Rect	define_rect(int x, int y, int w, int h)
{
	SDL_Rect 	rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
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
	(*wn)->edit_image.texture_tools = NULL;
	(*wn)->editext.on = 1;
	(*wn)->editext.map_w = 600;
	(*wn)->editext.map_h = 600;
	(*wn)->load = ft_strdup("./texture/editor/texture_bas_editor.tga");
	load_texture(*wn, "editor", "affichage", "tools") == 1 ? stop_exec("load texture tools failed\n", *wn) : 0;
	free((*wn)->load);
	(*wn)->load = ft_strdup("./texture/editor/texture_edit.tga");
	load_texture(*wn, "editor", "affichage", "history");
	free((*wn)->load);
	(*wn)->load = ft_strdup("./texture/editor/background_map.tga");
	load_texture(*wn, "editor", "affichage", "background_map");
	free((*wn)->load);
	(*wn)->load = ft_strdup("./texture/editor/params_edit.tga");
	load_texture(*wn, "editor", "affichage", "params");
	free((*wn)->load);
	(*wn)->load = ft_strdup("./texture/editor/blocs_edit.tga");
	load_texture(*wn, "editor", "affichage", "blocs");
	free((*wn)->load);
	(*wn)->load = ft_strdup("./texture/editor/texts_edit.tga");
	load_texture(*wn, "editor", "affichage", "texts");
	free((*wn)->load);
	(*wn)->load = ft_strdup("./texture/editor/fleche.tga");
	load_texture(*wn, "editor", "affichage", "fleche");
	free((*wn)->load);
	(*wn)->edit_image.bgh = 1;
	(*wn)->edit_image.in = 1;
	(*wn)->edit_image.tbp = 2;
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

void 		print_background_editor(t_win *wn)
{
	SDL_Surface 	*surface;
	SDL_Texture 	*texture;

	surface = SDL_CreateRGBSurface(0, wn->xscreen, wn->yscreen, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 66, 66, 66));
	texture = SDL_CreateTextureFromSurface(wn->rend, surface);
	SDL_FreeSurface(surface);
	if (SDL_RenderCopy(wn->rend, texture, NULL, NULL) < 0)
		stop_exec("rendercopy failed\n", wn);
}

void		change_bloc(t_win *wn)
{
	if (wn->input->x >= (5.5 * wn->xscreen / 7) && wn->input->x <= (5.75 * wn->xscreen / 7) && wn->input->y >= 0 && wn->input->y <= (0.25 * wn->yscreen / 7))
		wn->edit_image.bgh = 1;
	else if (wn->input->x >= (5.5 * wn->xscreen / 7) && wn->input->x <= (5.75 * wn->xscreen / 7) && wn->input->y > 0.25 && wn->input->y <= (0.5 * wn->yscreen / 7))
		wn->edit_image.bgh = 0;
	if (wn->input->x >= (6.75 * wn->xscreen / 7) && wn->input->x < wn->xscreen && wn->input->y >= (3 * wn->yscreen / 7) && wn->input->y < (3.25 * wn->yscreen / 7) && wn->edit_image.in == 1)
		wn->edit_image.in = 0;
	else if (wn->input->x >= (6.75 * wn->xscreen / 7) && wn->input->x < wn->xscreen && wn->input->y >= (5.75 * wn->yscreen / 7) && wn->input->y < (6 * wn->yscreen / 7) && wn->edit_image.in == 0)
		wn->edit_image.in = 1;
	if (wn->input->x >= (5.5 * wn->xscreen / 7) && wn->input->x < (5.75 * wn->xscreen / 7) && wn->input->y >= (3 * wn->yscreen / 7) && wn->input->y < (3.25 * wn->yscreen / 7) && wn->edit_image.in == 1)
		wn->edit_image.tbp = 0;
	if (wn->input->x >= (5.75 * wn->xscreen / 7) && wn->input->x < (6 * wn->xscreen / 7) && wn->input->y >= (3 * wn->yscreen / 7) && wn->input->y < (3.25 * wn->yscreen / 7) && wn->edit_image.in == 1)
		wn->edit_image.tbp = 1;
	if (wn->input->x >= (6 * wn->xscreen / 7) && wn->input->x < (6.25 * wn->xscreen / 7) && wn->input->y >= (3 * wn->yscreen / 7) && wn->input->y < (3.25 * wn->yscreen / 7) && wn->edit_image.in == 1)
		wn->edit_image.tbp = 2;
}

void 		print_arrow(t_win *wn)
{
	SDL_Rect 	dst;

	dst.x = 6.75 * wn->xscreen / 7;
	dst.w = 0.25 * wn->xscreen / 7;
	dst.h = 0.25 * wn->yscreen / 7;
	if (wn->edit_image.in == 1)
		dst.y = 3 * wn->yscreen / 7;
	else
		dst.y = 5.75 * wn->yscreen / 7; 
	wn->edit_image.fleche = findtexture(wn, "editor", "affichage", "fleche");
	(wn->edit_image.fleche == NULL) ? stop_exec("fleche failed in print_arrow\n", wn) : 0;
	if (SDL_RenderCopy(wn->rend, wn->edit_image.fleche, NULL, &dst) < 0)
		stop_exec("rendercopy failed in print_arrow\n", wn);
}

void 		print_tbp_editor(t_win *wn)
{
	SDL_Rect 	src;
	SDL_Rect 	dst;

	wn->edit_image.tbp == 0 ? wn->edit_image.texture_tbp = findtexture(wn, "editor", "affichage", "texts") : 0;
	wn->edit_image.tbp == 1 ? wn->edit_image.texture_tbp = findtexture(wn, "editor", "affichage", "blocs") : 0;
	wn->edit_image.tbp == 2 ? wn->edit_image.texture_tbp = findtexture(wn, "editor", "affichage", "params") : 0;
	(wn->edit_image.texture_tbp == NULL) ? stop_exec("texture params failed in print_tbp\n", wn) : 0;
	SDL_QueryTexture(wn->edit_image.texture_tbp, NULL, NULL, &src.w, &src.h);
	if (wn->edit_image.in == 1)
	{
		src.x = 0;
		src.y = 0;
		dst.x = 5.5 * wn->xscreen / 7;
		dst.y = 3 * wn->yscreen / 7;
		dst.w = 1.5 * wn->xscreen / 7;
		dst.h = 3 * wn->yscreen / 7;
	}
	else 
	{
		src.x = 0;
		src.y = 0;
		src.h = 0.25 * src.h / 7;
		dst.x = 5.5 * wn->xscreen / 7;
		dst.y = 5.75 * wn->yscreen / 7;
		dst.w = 1.5 * wn->xscreen / 7;
		dst.h = 0.25 * wn->yscreen / 7;
	}
	if (SDL_RenderCopy(wn->rend, wn->edit_image.texture_tbp, &src, &dst) < 0)
		stop_exec("render copy failed in print_tbp\n", wn);
	print_arrow(wn);
}

void		print_tools_editor(t_win *wn)
{
	SDL_Rect 		dst;

	dst.x = 0;
	dst.y = wn->yscreen / 7 * 6;
	dst.w = wn->xscreen;
	dst.h = wn ->yscreen / 7;
	wn->edit_image.texture_tools = findtexture(wn, "editor", "affichage", "tools");
	(wn->edit_image.texture_tools == NULL) ? stop_exec("texture print_tools_editor failed\n", wn) : 0;
	if (SDL_RenderCopy(wn->rend, wn->edit_image.texture_tools, NULL, &dst) < 0)
		stop_exec("rendercopy failed in print_tools_editor\n", wn);
}	

void		stop_editor(t_win *wn)
{
	(wn->editext.texture_x != NULL) ? SDL_DestroyTexture(wn->editext.texture_x) : 0;
	(wn->editext.texture_y != NULL) ? SDL_DestroyTexture(wn->editext.texture_y) : 0;
	(wn->editext.texture_z != NULL) ? SDL_DestroyTexture(wn->editext.texture_z) : 0;
	(wn->edit_image.texture_tools != NULL) ? SDL_DestroyTexture(wn->edit_image.texture_tools) : 0;
	(wn->edit_image.texture_bgh != NULL) ? SDL_DestroyTexture(wn->edit_image.texture_bgh) : 0;
	(wn->edit_image.texture_tbp != NULL) ? SDL_DestroyTexture(wn->edit_image.texture_tbp) : 0;
	(wn->edit_image.fleche != NULL) ? SDL_DestroyTexture(wn->edit_image.fleche) : 0;
	wn->fonts->arial != NULL ? TTF_CloseFont(wn->fonts->arial) : 0;	
}

void		printeditor(t_win *wn)
{
	print_background_editor(wn);
	showmap(wn);
	which_cursor(wn);
	print_tools_editor(wn);
	print_bgh_editor(wn);
	print_tbp_editor(wn);
	wn->editext.on == 1 ? print_x_y_z(wn) : 0;
}
