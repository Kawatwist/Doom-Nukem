/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initwn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:15:15 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/20 19:19:22 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	inittext2(t_win **wn, int parts, char *type, char *subtype)
{
	t_text	*text;
	text = (*wn)->texture;
	if (parts == 1)
	{
		while (text->next_type != NULL)
			text = text->next_type;
		text->next_type = malloc(sizeof(t_text));
		text = text->next_type;
		text->next_type = NULL;
		text->next_subtype = NULL;
		text->next = NULL;
		text->before = NULL;
		text->type = ft_strdup(type);
		text->subtype = ft_strdup(subtype);
		text->name = ft_strdup("none");
	}
	else
		while (text->next_subtype != NULL)
			text = text->next_subtype;
}

static void inittext(t_win **wn)
{
	((*wn)->texture = malloc(sizeof(t_text))) == NULL ? stop_exec("malloc failed\n", *wn): 0;
	(*wn)->texture->type = ft_strdup("main");
	(*wn)->texture->subtype = ft_strdup("intro");
	(*wn)->texture->name = ft_strdup("none");
	(*wn)->texture->next_type = NULL;
	(*wn)->texture->next_subtype = NULL;
	(*wn)->texture->next = NULL;
	(*wn)->texture->before = NULL;
	inittext2(wn, 1, "editor", "intro");
	inittext2(wn, 1, "game", "intro");
	inittext2(wn, 1, "option", "intro");
}

static void	initelem(t_win **wn)
{
	t_elem	*new;


	((*wn)->elem = malloc(sizeof(t_elem))) == NULL ? exit(0) : 0;
	(*wn)->elem->name = ft_strdup("Line");
	(*wn)->elem->x1 = 0;
	(*wn)->elem->x2 = 200;
	(*wn)->elem->y1 = 0;
	(*wn)->elem->y2 = 200;
	((*wn)->elem->next = malloc(sizeof(t_elem))) == NULL ? exit(0) : 0;
	(*wn)->elem->next->name = ft_strdup("Rect");
	(*wn)->elem->next->x1 = 200;
	(*wn)->elem->next->y1 = 50;
	(*wn)->elem->next->x2 = 50;
	(*wn)->elem->next->y2 = 50;
	((*wn)->elem->next->next = malloc(sizeof(t_elem))) == NULL ? exit(0) : 0;
	new = (*wn)->elem->next->next;
	new->name = ft_strdup("Rect");
	new->x1 = 200;
	new->y1 = 200;
	new->x2 = 200;
	new->y2 = 200;
	new->next = NULL;
}

static void	initmap(t_win **wn)
{
	((*wn)->map = malloc(sizeof(t_map))) == NULL ? exit(0) : 0;
	(*wn)->map->x = 0.1;
	(*wn)->map->y = 0.1;
	(*wn)->map->w = 600;
	(*wn)->map->h = 600;
	(*wn)->map->size = 1;
}

static void	initmenu(t_win **wn)
{
	((*wn)->menu = malloc(sizeof(t_menu))) == NULL ? exit(0) : 0;
	(*wn)->menu->choice = 0;
}

void	initwn(t_win **wn)
{
	ft_bzero(*wn, sizeof(t_win));
	(*wn)->interface = MENU;
	(*wn)->oldinterface = MENU;
	initmap(wn);
	initelem(wn);
	initmenu(wn);
	inittext(wn);
	(*wn)->debug = -1;
}
