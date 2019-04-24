/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:46:50 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/22 11:54:23 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

SDL_Texture		*findtexture(t_win *wn, char *type, char *subtype, char *name)
{
	t_text	*loaded;

	loaded = wn->texture;
	while (loaded->next_type != NULL && ft_strcmp(loaded->type, type) != 0)
	{
		loaded = loaded->next_type;
		if (loaded == NULL || loaded->name == NULL)
			break ;
	}
	while (loaded->next_subtype != NULL
			&& ft_strcmp(loaded->subtype, subtype) != 0)
	{
		loaded = loaded->next_subtype;
		if (loaded == NULL || loaded->name == NULL)
			break ;
	}
	while (loaded->next != NULL && ft_strcmp(loaded->name, name) != 0)
	{
		loaded = loaded->next;
		if (loaded == NULL || loaded->name == NULL)
			break ;
	}
	if (loaded->name == NULL || loaded->txt == NULL)
		return (wn->txtnotload);
	return (loaded->txt);
}
