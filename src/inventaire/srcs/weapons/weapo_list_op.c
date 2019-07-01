/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:24:02 by naali             #+#    #+#             */
/*   Updated: 2019/07/01 08:17:26 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "inventaire.h"

void		pushback_weapons(t_weapons **start, t_weapons *node)
{
	t_weapons	*tmp;

	if (start != NULL && *start != NULL && node != NULL)
	{
		tmp = *start;
		tmp = tmp->previous;
		node->previous = tmp;
		tmp->next = node;
		node->next = *start;
		(*start)->previous = node;
	}
	else if (start != NULL && *start == NULL && node != NULL)
	{
		*start = node;
		node->next = *start;
		node->previous = *start;
	}
}

int			weapo_list_len(t_weapons **start)
{
	int			i;
	t_weapons	*tmp;
	t_weapons	*tmp_end;

	i = 1;
	if (start != NULL && *start != NULL)
	{
		tmp_end = (*start)->previous;
		tmp = *start;
		while (tmp != tmp_end)
		{
			tmp = tmp->next;
			i++;
		}
	}
	else
		return (0);
	return (i);
}

t_weapons	*get_weapo_by_id(t_weapons **start, unsigned int id)
{
	unsigned int	id_cpy;
	t_weapons	*tmp;

	if (start != NULL && *start != NULL)
	{
		tmp = *start;
		id_cpy = (*start)->previous->id;
		while (tmp->id != id && tmp->id != id_cpy)
			tmp = tmp->next;
		if (tmp->id == id)
			return (tmp);
	}
	return (NULL);
}
