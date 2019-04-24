/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:35:20 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/22 11:53:36 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/tga_reader.h"

static void		fillpos(t_text *curr, char *type, char *subtype, char *name)
{
	curr->type = ft_strdup(type);
	curr->subtype = ft_strdup(subtype);
	curr->name = ft_strdup(name);
	curr->next_type = NULL;
	curr->next_subtype = NULL;
	curr->next = NULL;
}

t_text			*findpostxt(t_win *wn, char *type, char *subtype, char *name)
{
	t_text	*curr;

	curr = wn->texture;
	while (curr->next_type != NULL && ft_strcmp(type, curr->type))
		curr = curr->next_type;
	while (curr->next_subtype != NULL && ft_strcmp(subtype, curr->subtype)
			&& !ft_strcmp(type, curr->type))
		curr = curr->next_subtype;
	while (curr->next != NULL && ft_strcmp(name, curr->name)
			&& !ft_strcmp(type, curr->type)
			&& !ft_strcmp(subtype, curr->subtype))
		curr = curr->next;
	return (curr);
}

t_text			*findpos(t_win *wn, char *type, char *subtype, char *name)
{
	t_text	*curr;

	curr = wn->texture;
	while (curr->next_type != NULL && ft_strcmp(type, curr->type))
		curr = curr->next_type;
	while (curr->next_subtype != NULL && ft_strcmp(subtype, curr->subtype)
			&& !ft_strcmp(type, curr->type))
		curr = curr->next_subtype;
	while (curr->next != NULL && ft_strcmp(name, curr->name)
			&& !ft_strcmp(type, curr->type)
			&& !ft_strcmp(subtype, curr->subtype))
		curr = curr->next;
	if (ft_strcmp(curr->type, type))
	{
		(curr->next_type = malloc(sizeof(t_text))) == NULL
			? stop_exec("Malloc Failed\n", wn) : 0;
		curr->next_type->before = curr;
		curr = curr->next_type;
	}
	else if (ft_strcmp(curr->subtype, subtype))
	{
		(curr->next_subtype = malloc(sizeof(t_text))) == NULL
			? stop_exec("Malloc Failed\n", wn) : 0;
		curr->next_subtype->before = curr;
		curr = curr->next_subtype;
	}
	else
	{
		(curr->next = malloc(sizeof(t_text))) == NULL
			? stop_exec("Malloc Failed\n", wn) : 0;
		curr->next->before = curr;
		curr = curr->next;
	}
	fillpos(curr, type, subtype, name);
	return (curr);
}

static int		tga2sur(t_tga *tga, t_win *wn, t_text *place)
{
	tga->surface = SDL_CreateRGBSurfaceWithFormatFrom(tga->data,
			tga->w, tga->h, 32, 4 * (tga->w), SDL_PIXELFORMAT_ARGB32);
	if (tga->surface != NULL)
		place->txt = SDL_CreateTextureFromSurface(wn->rend, tga->surface);
	else
	{
		free(place->name);
		free(place->subtype);
		free(place->type);
		place = NULL;
	}
	SDL_FreeSurface(tga->surface);
	return (0);
}

int				load_texture(t_win *wn, char *type, char *subtype, char *name)
{
	t_tga		*tga;
	t_text		*txt;
	int			i;

	if (ft_strcmp("main", type) == 0)
		i = 0;
	else if (ft_strcmp("editor", type) == 0)
		i = 1;
	else if (ft_strcmp("option", type) == 0)
		i = 2;
	else
		i = 3;
	tga = NULL;
	txt = NULL;
	if (!(tga = (t_tga *)malloc(sizeof(t_tga))))
		stop_exec("Cant malloc tga\n", wn);
	if ((tga = load_tga(wn->tmp[i])) == NULL)
	{
		free_tga(tga);
		return (1);
	}
	txt = findpos(wn, type, subtype, name);
	tga2sur(tga, wn, txt);
	return (0);
}
