/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:35:20 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/07 13:27:37 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "tga_reader.h"

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
