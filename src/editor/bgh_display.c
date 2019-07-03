/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bgh_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:25:35 by llejeune          #+#    #+#             */
/*   Updated: 2019/06/05 17:25:39 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		print_bgh_editor(t_win *wn)
{
	SDL_Rect		dst;

	dst = define_rect(5.5 * wn->xscreen / 7, 0,
		1.5 * wn->xscreen / 7, 3 * wn->yscreen / 7);
	if (wn->edit_image.bgh == 1)
		wn->edit_image.texture_bgh =
			findtexture(wn, "editor", "affichage", "history");
	else if (wn->edit_image.bgh == 0)
		wn->edit_image.texture_bgh =
			findtexture(wn, "editor", "affichage", "background_map");
	if (wn->edit_image.texture_bgh == NULL)
		stop_exec("texture bgh failed in print_bgh\n", wn);
	if (SDL_RenderCopy(wn->rend, wn->edit_image.texture_bgh, NULL, &dst) < 0)
		stop_exec("rendercopy failed in print_history\n", wn);
	bg_or_h(wn);
}

void		print_path(t_win *wn, char *s, int posi_x, int posi_y)
{
	int				w;
	int				h;
	int				x;
	SDL_Rect		position;

	x = 0;
	TTF_SizeText(wn->fonts->arial_path, s, &w, &h);
	position.x = posi_x;
	position.y = posi_y - 5;
	position.h = h;
	SDL_QueryTexture(wn->edit_image.bg_path, NULL, NULL, &w, &h);
	x = w - wn->edit_image.bg.w - 5;
	if (w < (wn->edit_image.bg.w - 5))
	{
		position.w = w;
		wn->edit_image.pos_path = define_rect(0, 0, w, h);
		print_text_with_arial_path(wn, s, wn->color.noir, position);
	}
	else
	{
		position.w = wn->edit_image.bg.w - 5;
		wn->edit_image.pos_path = define_rect(x, 0, w, h);
		print_text_with_arial_path(wn, s, wn->color.noir, position);
	}
}

static void		text_for_bg(t_win *wn)
{
	SDL_Rect	position;
	int			w;
	int			h;

	TTF_SizeText(wn->fonts->arial_path, "Load a background image :", &w, &h);
	position = define_rect(wn->edit_image.bg.x, wn->edit_image.bg.y - h - 20, w, h);
	TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD);
	print_text_with_arial_path_full(wn, "Load a background image :", wn->color.noir, position);
	TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_NORMAL);
	TTF_SizeText(wn->fonts->arial, "no special character allowed except / . ~", &w, &h);
	position = define_rect(wn->edit_image.bg.x, wn->edit_image.bg.y - h - 2, w, h);
	TTF_SetFontStyle(wn->fonts->arial, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
	print_text_with_arial_font(wn, "no special character allowed except / . ~", wn->color.noir, position);
	TTF_SetFontStyle(wn->fonts->arial, TTF_STYLE_NORMAL);
}

void		bg_or_h(t_win *wn)
{
	if (wn->edit_image.bgh == 0)
		print_bg(wn);
	// else if (wn->edit_image.bgh == 1)
	// 	print_history(wn);
}

int			is_path_ok(t_win *wn, char *path)
{
	if (path == NULL)
		return (1);
	wn->load = ft_strdup(path);
	if (load_texture(wn, "editor", "affichage", path) == 1)
		message_bg_editor(wn, "This path doesn't exist.");
	else
	{
		message_bg_editor(wn, "Image downloaded.");
		return (0);
	}
	free(wn->load);
	return (1);
}

void		load_background(t_win *wn)
{
	static			SDL_Texture 	*texture = NULL;
	int				w;
	int				h;
	SDL_Rect		dst;

	if (texture == NULL)
	{
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
		dst = define_rect(0, 0, w, h);
		texture = findtexture(wn, "editor", "affichage", wn->bg_map.path);
	}
	if (texture == NULL)
		return ;
	if (SDL_RenderCopy(wn->rend, texture, NULL, (dst.x != 0) ? &dst : NULL) < 0)
		stop_exec("render copy failed in load_bg\n", wn);
}

void		message_bg_editor(t_win *wn, char *message)
{
	int			w;
	int			h;
	SDL_Rect	position;

	TTF_SizeText(wn->fonts->arial_path, message, &w, &h);
	position = define_rect(wn->edit_image.bg.x,
		wn->edit_image.bg.y + wn->edit_image.bg.h + 10, w, h);
	TTF_SetFontStyle(wn->fonts->arial, TTF_STYLE_ITALIC);
	print_text_with_arial_font(wn, message, wn->color.red, position);
	TTF_SetFontStyle(wn->fonts->arial, TTF_STYLE_NORMAL);
}

// void		manage_tilde(char *path)
// {
// 	char *tmp;
// 	char *login;

// 	free(path);
// 	path = ft_strjoinfree("/Users/", getlogin_r(login, 8), 16);
// 	tmp = ft_strdup(path);
// 	free(path);
// 	path = ft_strjoinfree(tmp, "/", ft_strlen(tmp) + 2);
// }

void		print_bg(t_win *wn)
{
	static char		*path = NULL;

	if (path == NULL)
		path = ft_strdup("/Users/llejeune/Doom/texture/skybox/\0");
	// (path[0] == '~') ? manage_tilde(path) : 0;
	text_for_bg(wn);
	wn->edit_image.bg = define_rect(5.6 * wn->xscreen / 7,
		1.5 * wn->yscreen / 7, 1.30 * wn->xscreen / 7, 26);
	SDL_SetRenderDrawColor(wn->rend, 250, 250, 250, 0);
	(SDL_RenderFillRect(wn->rend, &wn->edit_image.bg) < 0) ?
	stop_exec("fillrect failed in print_bg\n", wn) : 0;
	path = printable_input(wn, path);
	if ((key_pressed(wn, SDL_SCANCODE_BACKSPACE)) &&
		path != NULL && ft_strlen(path))
		path[ft_strlen(path) - 1] = 0;
	if ((path != NULL) && ft_strlen(path))
		print_path(wn, path, wn->edit_image.bg.x + 5, wn->edit_image.bg.y + 5);
	if (key_pressed(wn, SDL_SCANCODE_RETURN))
	{
		wn->bg_map.path = ft_strdup(path);
		// load_background(wn);//charger command si lien valide sinon message d'erreur "<command> doesn't exist."
		free(path); // ajouter free(path) et path = NULL dans fonction chargement bg
		path = NULL; // faire ternaire (path != NULL) ? load_bg : ft_pr_mess_err_bg
	}
}
