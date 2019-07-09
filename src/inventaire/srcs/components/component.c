/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:11:50 by naali             #+#    #+#             */
/*   Updated: 2019/07/09 12:27:45 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inventaire.h"

static int			check_nodes(t_component **start, char *name, int qty, unsigned int id)
{
	t_component		*tmp;

	if (start != NULL || *start != NULL)
	{
	}
	return (0);
}

t_component			*new_compo(char *name, unsigned int qty, t_consumable **start)
{
	t_component			*compo;
	static unsigned int	id = 0;

	if (check_nodes(start, name, qty, &id) != 0)
		return (NULL);
	if ((compo = (t_component*)malloc(sizeof(t_component))) == NULL)
		return (NULL);
	compo->id = ++id;
	compo->name = ft_strdup(name);
	compo->qty = qty;
	compo->next = NULL;
	compo->previous = NULL;
	return (compo);
}
