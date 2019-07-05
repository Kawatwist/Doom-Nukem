/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initwn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:15:15 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/05 18:48:47 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

static void	inittext(t_win **wn)
{
	((*wn)->texture = malloc(sizeof(t_text))) == NULL
		? stop_exec("malloc failed\n", *wn) : 0;
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

static void	initmap(t_win **wn)
{
	((*wn)->map = malloc(sizeof(t_map))) == NULL ? exit(0) : 0;
	(*wn)->map->x = 0.1;
	(*wn)->map->y = 0.1;
	(*wn)->map->w = 600;
	(*wn)->map->h = 600;
	(*wn)->map->size = 1;
}

static void	initelem(t_win **wn)
{
	((*wn)->elem = malloc(sizeof(t_elem))) == NULL ? stop_exec("Elem malloc failed\n", *wn) : 0;
	((*wn)->elem->point = malloc(sizeof(t_point))) == NULL ? stop_exec("point malloc failed\n", *wn) : 0;
	(*wn)->elem->next = NULL;
	(*wn)->elem->point->next = NULL;
}

static void	initmenu(t_win **wn)
{
	((*wn)->menu = malloc(sizeof(t_menu))) == NULL ? exit(0) : 0;
	(*wn)->menu->choice = 0;
}

static void initconsole(t_win **wn)
{
	(*wn)->console = (t_console*)malloc(sizeof(t_console)); // 'free codes' not written yet
	if ((*wn)->console == NULL)
		stop_exec("malloc failed in initconsole()", *wn);
	ft_bzero((*wn)->console, sizeof(t_console));
	(*wn)->console->history = (char**)malloc(sizeof(char*) * (CONSOLE_MAX_LINE_NB)); // 'free codes' not written yet
	if ((*wn)->console->history == NULL)
		stop_exec("malloc failed in initconsole(): history", *wn);
	ft_bzero((*wn)->console->history, sizeof(char**));
}

void		initwn(t_win **wn)
{
	ft_bzero(*wn, sizeof(t_win));
	(*wn)->interface = MENU;
	(*wn)->oldinterface = MENU;
	(*wn)->xscreen = XSCREEN;
	(*wn)->yscreen = YSCREEN;
	initconsole(wn);
	initmap(wn);
	initelem(wn);
	initmenu(wn);
	inittext(wn);
	initmutex(wn);
	(*wn)->flag = 0;
	(*wn)->sky = 1;
}
