/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadingtga.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 13:36:19 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/08 16:17:43 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		converttxt()
{
}

void		storetxt()
{
}

void		introtga()
{
}

static void	fillload(int menu, t_load **filled)
{
	menu == 0 ? (*filled)->type = ft_strdup("main") : 0;
	menu == 1 && (*fille)->type == NULL ? (*filled)->type = ft_strdup("editor") : 0;
	menu == 2 && (*fille)->type == NULL ? (*filled)->type = ft_strdup("option") : 0;
	menu == 3 && (*fille)->type == NULL ? (*filled)->type = ft_strdup("game") : 0;
	(*filled)->subtype = ft_strdup("intro");
	(*filled)->txt = NULL;
	(*filled)->next = NULL;
}

void		*main_tgaload(void *params)
{
	t_thread	*td;
	t_tga		*ret;

	td = (t_thread *)params;
	fillload(td->value, td->file);
	return (0);
}
