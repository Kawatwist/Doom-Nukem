/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conso_list_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 08:09:16 by naali             #+#    #+#             */
/*   Updated: 2019/07/01 08:16:07 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "inventaire.h"

void			pushback_conso(t_consumable **start, t_consumable *node)
{
	t_consumable	*tmp;

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

int				conso_list_len(t_consumable **start)
{
	int				i;
	t_consumable	*tmp;
	t_consumable	*tmp_end;

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

t_consumable 	*get_conso_by_id(t_consumable **start, unsigned int id)
{
	unsigned int	id_cpy;
	t_consumable	*tmp;

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
