/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:58:28 by llejeune          #+#    #+#             */
/*   Updated: 2019/08/12 17:01:49 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

static void		load_edit_texture(t_win **wn)
{
	(*wn)->load = ft_strdup("./texture/editor/texture_bas_editor.tga");
	load_texture(*wn, "editor", "affichage", "tools");
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
	(*wn)->load = ft_strdup("./texture/editor/cursor.tga");
	load_texture(*wn, "editor", "affichage", "cursor_panel");
	free((*wn)->load);
}

static void	initmap(t_win *wn, t_edit *edit)
{
	edit->map->size = 1.6;
	edit->map->w = 1000;
	edit->map->h = 1000;
	edit->map->x = (wn->xscreen / 3) - (edit->map->w / 2);
	edit->map->y = (wn->yscreen / 3) - ((edit->map->h / 2));
}

static void	initelem(t_edit *edit)
{
	edit->elem->point = NULL;
	edit->elem->next = malloc(sizeof(t_elem)); // MALLOC SECURE
	edit->elem->next->point = NULL;
	edit->elem->next->next = NULL;
}

static void	init_editor_fct(t_edit *edit)
{
	edit->cursor_fct[CURSOR] = cursor;
	edit->cursor_fct[DRAW] = draw_cursor;
	edit->cursor_fct[ERASE] = erase_cursor;
	edit->cursor_fct[ZOOM] = zoom_cursor;
	edit->cursor_fct[HAND] = hand_cursor;
	edit->cursor_fct[SELECT] = select_cursor;
	edit->cursor_fct[WAND] = wand_cursor;
	edit->cursor_fct[FORM] = form_cursor;
	edit->cursor_fct[SWAP] = swap_cursor;
	edit->cursor_fct[RESIZE] = resize_cursor;
}

void		init_edit(t_win **wn)
{
	t_edit *edit;

	(*wn)->edit = malloc(sizeof(t_edit));
	edit = ((t_edit *)(*wn)->edit);
	edit->map = malloc(sizeof(t_map));
	edit->elem = malloc(sizeof(t_elem));
	edit->loadbg = malloc(sizeof(t_loadbg));
	edit->tab = malloc(sizeof(t_tab));
	edit->indice = malloc(sizeof(t_indice));
	edit->var = malloc(sizeof(t_var));
	edit->indice->texture_x = NULL;
	edit->indice->texture_y = NULL;
	edit->indice->texture_z = NULL;
	edit->indice->on = 1;
	edit->indice->map_w = 600;
	edit->indice->map_h = 600;
	edit->indice->val_z = 20;
	edit->tab->texture_tools = NULL;
	edit->tab->bgh = 0;
	edit->tab->in = 1;
	edit->tab->onglet = 2;
	edit->loadbg->path = NULL;
	edit->var->cursor = 1;
	edit->var->swapvar = 0;
	edit->var->nb_point = 1;
	edit->var->map_saved = 0;
	edit->selected = NULL;
	initmap(*wn, edit);
	initelem(edit);
	init_editor_fct(edit);
	load_edit_texture(wn);
}

void			stop_editor(t_win *wn)
{
	t_edit 	*edit;

	edit = ((t_edit *)(*wn).edit);
	if (edit->indice->texture_x != NULL)
		SDL_DestroyTexture(edit->indice->texture_x);
	if (edit->indice->texture_y != NULL)
		SDL_DestroyTexture(edit->indice->texture_y);
	if (edit->indice->texture_z != NULL)
		SDL_DestroyTexture(edit->indice->texture_z);
	if (edit->tab->texture_tools != NULL)
		SDL_DestroyTexture(edit->tab->texture_tools);
	// if (edit->tab->texture_bgh != NULL)
	// 	SDL_DestroyTexture(edit->tab->texture_bgh);
	if (edit->tab->texture_tab != NULL)
		SDL_DestroyTexture(edit->tab->texture_tab);
	if (edit->tab->fleche != NULL)
		SDL_DestroyTexture(edit->tab->fleche);
	wn->fonts->arial != NULL ? TTF_CloseFont(wn->fonts->arial) : 0;
}
