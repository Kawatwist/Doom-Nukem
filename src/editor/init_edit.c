/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:58:28 by llejeune          #+#    #+#             */
/*   Updated: 2019/07/24 18:01:52 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

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
	free((*wn)->load);
}

void			init_edit(t_win **wn)
{
	(*wn)->editext.texture_x = NULL;
	(*wn)->editext.texture_y = NULL;
	(*wn)->editext.texture_z = NULL;
	(*wn)->edit_image.texture_tools = NULL;
	(*wn)->editext.on = 1;
	(*wn)->editext.map_w = 60;
	(*wn)->editext.map_h = 60;
	(*wn)->edit_image.bgh = 0;
	(*wn)->edit_image.in = 1;
	(*wn)->edit_image.tbp = 2;
	(*wn)->bg_map.path = NULL;
	(*wn)->editext.val_z = 200;
	load_edit_texture(wn);
}

void			stop_editor(t_win *wn)
{
	if (wn->editext.texture_x != NULL)
		SDL_DestroyTexture(wn->editext.texture_x);
	if (wn->editext.texture_y != NULL)
		SDL_DestroyTexture(wn->editext.texture_y);
	if (wn->editext.texture_z != NULL)
		SDL_DestroyTexture(wn->editext.texture_z);
	if (wn->edit_image.texture_tools != NULL)
		SDL_DestroyTexture(wn->edit_image.texture_tools);
	if (wn->edit_image.texture_bgh != NULL)
		SDL_DestroyTexture(wn->edit_image.texture_bgh);
	if (wn->edit_image.texture_tbp != NULL)
		SDL_DestroyTexture(wn->edit_image.texture_tbp);
	if (wn->edit_image.fleche != NULL)
		SDL_DestroyTexture(wn->edit_image.fleche);
	wn->fonts->arial != NULL ? TTF_CloseFont(wn->fonts->arial) : 0;
}
