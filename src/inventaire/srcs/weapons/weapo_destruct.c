/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapo_destruct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 08:15:17 by naali             #+#    #+#             */
/*   Updated: 2019/07/01 08:17:52 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "inventaire.h"

void			destroy_one_weapo(t_weapons **start, unsigned int id)
{
	unsigned int	i;
	unsigned int	max;
	t_weapons	*tmp;
	t_weapons	*prev;

	if (start != NULL && *start != NULL)
		tmp = get_weapo_by_id(start, id);
	if (tmp != NULL)
	{
		i = 1;
		prev = tmp->previous;
		prev->next = tmp->next;
		tmp->next->previous = prev;
		free(tmp);
		tmp = NULL;
		while (prev->id > prev->previous->id)
			prev = prev->previous;
		*start = prev;
		max = weapo_list_len(start);
		while (i < max + 1)
		{
			prev->id = i++;
			prev = prev->next;
		}
	}
}

void			destroy_weapo_list(t_weapons **start)
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
