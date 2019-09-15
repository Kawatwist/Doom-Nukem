/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bgh_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:25:35 by llejeune          #+#    #+#             */
/*   Updated: 2019/07/24 17:35:24 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include <header_game_engine.h>

static void		text_for_bg(t_win *wn, t_edit *edit)
{
	SDL_Rect	position;
	int			w;
	int			h;

	TTF_SizeText(wn->fonts->arial_path, "Load a background image :", &w, &h);
	position = define_rect(edit->tab->bg.x, edit->tab->bg.y - h - 20, w, h);
	TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD);
	print_text_with_arial_path_full(wn, "Load a background image :", wn->color.noir, position);
	TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_NORMAL);
	TTF_SizeText(wn->fonts->arial, "no special character allowed except / . ~", &w, &h);
	position = define_rect(edit->tab->bg.x, edit->tab->bg.y - h - 2, w, h);
	TTF_SetFontStyle(wn->fonts->arial, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
	print_text_with_arial_font(wn, "no special character allowed except / . ~", wn->color.noir, position);
	TTF_SetFontStyle(wn->fonts->arial, TTF_STYLE_NORMAL);
}


int			is_path_ok(t_win *wn, char *path)
{
	if (path == NULL)
		return (1);
	wn->load = ft_strdup(path);
	if (load_texture(wn, "editor", "affichage", path) == 1)
		message_bg_editor(wn, wn->edit, "This path doesn't exist.");
	else
	{
		message_bg_editor(wn, wn->edit, "Image downloaded.");
		return (0);
	}
	free(wn->load);
	return (1);
}


void		message_bg_editor(t_win *wn, t_edit *edit, char *message) // NEED TO CHANGE
{
	int			w;
	int			h;
	SDL_Rect	position;

	TTF_SizeText(wn->fonts->arial_path, message, &w, &h);
	position = define_rect(edit->tab->bg.x,
		edit->tab->bg.y + edit->tab->bg.h + 10, w, h);
	TTF_SetFontStyle(wn->fonts->arial, TTF_STYLE_ITALIC);
	print_text_with_arial_font(wn, message, wn->color.red, position);
	TTF_SetFontStyle(wn->fonts->arial, TTF_STYLE_NORMAL);
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
		((t_edit *)(*wn).edit)->tab->bg_pics = findtexture(wn, "editor", "affichage", ((t_edit *)wn->edit)->loadbg->path);
	}
	if (texture == NULL)
		return ;
	//if (SDL_RenderCopy(wn->rend, texture, NULL, (dst.x != 0) ? &dst : NULL) < 0)
	//	stop_exec("render copy failed in load_bg\n", wn);
}

void		manage_tilde(char **path)
{
	char login[9];

	free(*path);
	getlogin_r(login, 9);
	*path = ft_strjoinfree(ft_strdup("/Users/"), login, 1);
	*path = ft_strjoinfree(*path, "/", 1);
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
	//SDL_QueryTexture(((t_edit *)wn->edit)->tab->bg_path, NULL, NULL, &w, &h);
	x = w - ((t_edit *)wn->edit)->tab->bg.w - 5;
	if (w < (((t_edit *)wn->edit)->tab->bg.w - 5))
	{
		position.w = w;
		((t_edit *)wn->edit)->tab->pos_path = define_rect(0, 0, w, h);
		print_text_with_arial_path(wn, s, wn->color.noir, position);
	}
	else
	{
		position.w = ((t_edit *)wn->edit)->tab->bg.w - 5;
		((t_edit *)wn->edit)->tab->pos_path = define_rect(x, 0, w, h);
		print_text_with_arial_path(wn, s, wn->color.noir, position);
	}
}

static void	extract_obj(t_win *wn, t_edit *edit)
{
	SDL_Rect	position;
	SDL_Rect	save;
	SDL_Rect	cursor;
	
	position = define_rect(((t_edit *)wn->edit)->tab->bg.x, ((t_edit*)wn->edit)->tab->bg.y + 200, ((t_edit*)wn->edit)->tab->bg.w - 50, ((t_edit*)wn->edit)->tab->bg.h);
	save = define_rect(((t_edit *)wn->edit)->tab->bg.x + ((t_edit*)wn->edit)->tab->bg.w - 100, ((t_edit*)wn->edit)->tab->bg.y + 200, 50, ((t_edit*)wn->edit)->tab->bg.h);	
	cursor.x = wn->input->x;
	cursor.y = wn->input->y;
	if (boxhitbox(wn->rend, &cursor, &(position), 1) || boxhitbox(wn->rend, &cursor, &(save), 1))
	{
		save_panel(wn, edit);
	}
}

void		print_bg(t_win *wn, t_edit *edit)
{
	static char		*path = NULL;

	if (path == NULL)
		path = ft_strdup("~\0");
	(path[0] == '~') ? manage_tilde(&path) : 0;
	text_for_bg(wn, edit);
	edit->tab->bg = define_rect(5.6 * wn->xscreen / 7,
		1.5 * wn->yscreen / 7, 1.30 * wn->xscreen / 7, 26);
	SDL_SetRenderDrawColor(wn->rend, 250, 250, 250, 0);
	(SDL_RenderFillRect(wn->rend, &edit->tab->bg) < 0) ?
	stop_exec("fillrect failed in print_bg\n", wn) : 0;
	if (edit->loadbg->flag & WRITE)
	{
		path = printable_input(wn, path);
		if ((key_pressed(wn, SDL_SCANCODE_BACKSPACE)) && path != NULL && ft_strlen(path))
			path[ft_strlen(path) - 1] = 0;
	}
	if ((path != NULL) && ft_strlen(path))
		print_path(wn, path, edit->tab->bg.x + 5, edit->tab->bg.y + 5);
	if (key_pressed(wn, SDL_SCANCODE_RETURN))
	{
		if (edit->loadbg->path != NULL)
			free(edit->loadbg->path);
		edit->loadbg->path = ft_strdup(path);
		is_path_ok(wn, path);
		((t_edit *)(*wn).edit)->tab->bg_pics = findtexture(wn, "editor", "affichage", ((t_edit *)wn->edit)->loadbg->path);
		free(path); // ajouter free(path) et path = NULL dans fonction chargement bg
		path = NULL; // faire ternaire (path != NULL) ? load_bg : ft_pr_mess_err_bg
	}
	extract_obj(wn, edit);
}

/*void		bg_or_h(t_win *wn, t_edit *edit)
{
	if (edit->tab->bgh == 0)
	{
		print_bg(wn, edit);
	}
}

void		print_bgh_editor(t_win *wn, t_edit *edit)
{
	SDL_Rect		dst;

	dst = define_rect(5.5 * wn->xscreen / 7, 0,
		1.5 * wn->xscreen / 7, 3 * wn->yscreen / 7);
	if (edit->tab->onglet == 3)
		edit->tab->texture_bgh =
			findtexture(wn, "editor", "affichage", "history");
	else if (edit->tab->bgh == 0)
		edit->tab->texture_bgh =
			findtexture(wn, "editor", "affichage", "background_map");
	if (edit->tab->texture_bgh == NULL)
		stop_exec("texture bgh failed in print_bgh\n", wn);
	if (SDL_RenderCopy(wn->rend, edit->tab->texture_bgh, NULL, &dst) < 0)
		stop_exec("rendercopy failed in print_history\n", wn);
	bg_or_h(wn, edit);
}*/