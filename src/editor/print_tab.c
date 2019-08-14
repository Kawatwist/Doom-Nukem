/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 13:31:05 by llejeune          #+#    #+#             */
/*   Updated: 2019/08/08 13:31:08 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void    display_tab(t_win *wn, t_edit *edit)
{
    edit->tab->onglet == 0 ? edit->tab->texture_tab =
	findtexture(wn, "editor", "affichage", "params") : 0;
	edit->tab->onglet == 1 ? edit->tab->texture_tab =
	findtexture(wn, "editor", "affichage", "texts") : 0;
	edit->tab->onglet == 2 ? edit->tab->texture_tab =
	findtexture(wn, "editor", "affichage", "blocs") : 0;
	edit->tab->onglet == 3 ? edit->tab->texture_tab =
	findtexture(wn, "editor", "affichage", "background_map") : 0;
	(edit->tab->texture_tab == NULL) ?
	stop_exec("texture params failed in print_tab\n", wn) : 0;
}

void    exec_tab(t_win *wn, t_edit *edit)
{
    // edit->tab->onglet == 0 && edit->tab->in == 1 ? fonction textures : 0;
	// edit->tab->onglet == 1 && edit->tab->in == 1 ? fonction persos : 0;
	// edit->tab->onglet == 2 && edit->tab->in == 1 ? fonction coordonnees : 0;
	edit->tab->onglet == 3 && edit->tab->in == 1 ? print_bg(wn, edit) : 0;
	(edit->tab->texture_tab == NULL) ?
	stop_exec("texture params failed in print_tab\n", wn) : 0;
}