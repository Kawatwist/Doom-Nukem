/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conso_destruct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 07:54:33 by naali             #+#    #+#             */
/*   Updated: 2019/07/04 16:28:46 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "inventaire.h"

void			destroy_one_conso(t_consumable **start, unsigned int id)
{
	unsigned int	i;
	unsigned int	max;
	t_consumable	*tmp;
	t_consumable	*prev;

	tmp = NULL;
	if (start != NULL && *start != NULL)
		tmp = get_conso_by_id(start, id);
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
		max = conso_list_len(start);
		while (i < max + 1)
		{
			prev->id = i++;
			prev = prev->next;
		}
	}
}

void			destroy_conso_list(t_consumable **start)
{
	t_consumable	*tmp;
	t_consumable	*tmp_end;

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
