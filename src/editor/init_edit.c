/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:58:28 by llejeune          #+#    #+#             */
/*   Updated: 2019/06/11 14:58:31 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

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