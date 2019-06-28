/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:24:02 by naali             #+#    #+#             */
/*   Updated: 2019/06/28 15:23:02 by naali            ###   ########.fr       */
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

void		destroy_weapo_list(t_weapons **start)
{
	t_weapons	*tmp;
	t_weapons	*tmp_end;

	if (start != NULL && *start != NULL)
	{
		tmp_end = (*start)->previous;
		tmp = *start;
		while (*start != tmp_end)
		{
			tmp = tmp->next;
			free(*start);
			*start = NULL;
			*start = tmp;
		}
		if (*start != NULL)
			free(*start);
		*start = NULL;
	}
}
