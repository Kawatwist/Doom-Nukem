/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consumable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:15:05 by naali             #+#    #+#             */
/*   Updated: 2019/06/26 17:09:50 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "inventaire.h"

static void		use_potion(t_joueurs *p, t_consumable *c)
{
	if (p->vie < 100 && c->qty > 0)
	{
		c->qty -= 1;
		p->vie += c->used;
	}
	if (p->vie >= 100)
		p->vie = 100;
	printf("Vie du joueur %s = %d, utilisation restante = %d\n", p->name, p->vie, c->qty);
}

static void		use_battery(t_joueurs *p, t_consumable *c)
{
	if (p->energie < 100 && c->qty > 0)
	{
		c->qty -= 1;
		p->energie += c->used;
	}
	if (p->energie >= 100)
		p->energie = 100;
	printf("Energie du joueur %s = %d, utilisation restante = %d\n", p->name, p->energie, c->qty);
}


static int		check_nodes(t_consumable **start, t_consumable *node, int qty)
{
	t_consumable	*tmp;

	tmp = *start;
	tmp = tmp->next;
	while (tmp != *start)
	{
		if (ft_strcmp(tmp->name, node->name) == 0)
		{
			tmp->qty += qty;
			destroy_conso_list(&node);
			return (1);
		}
		tmp = tmp->next;
	}
	if (ft_strcmp(tmp->name, node->name) == 0)
	{
		tmp->qty += qty;
		destroy_conso_list(&node);
		return (1);
	}
	return (0);
}

t_consumable	*new_conso(char *name, unsigned int qty)
{
	t_consumable			*conso;
	static unsigned int		id = 0;

	if ((conso = (t_consumable*)malloc(sizeof(t_consumable))) == NULL)
	{
		ft_putstr("erreur de malloc dans new_conso\n");// Modifier fonction d'erreur...
		exit(-1);
	}
	id++;
	conso->id = id;
	(name != NULL) ? ft_strcpy(conso->name, name) : ft_putstr("error conso name\n");// Modifier fonction erreur...
	conso->type = (ft_strncmp(name, "potion", 6) == 0) ? 1 : 2;
	if (conso->type == 1)
		conso->used = (ft_strlen(conso->name) <= 7) ? 30 : 50;
	else
		conso->used = (ft_strlen(conso->name) <= 8) ? 50 : 100;
	conso->qty = qty;
	if (conso->type == 1)
		conso->use = &use_potion;
	else
		conso->use = &use_battery;
	conso->next = NULL;
	conso->previous = NULL;
	return (conso);
}

void			pushback_conso(t_consumable **start, t_consumable *node)
{
	t_consumable	*tmp;

	if (start != NULL && *start != NULL)
	{
		if (check_nodes(start, node, node->qty) != 0)
			return ;
		tmp = *start;
		tmp = tmp->previous;
		node->previous = tmp;
		tmp->next = node;
		node->next = *start;
		(*start)->previous = node;
	}
	else if (start != NULL && *start == NULL)
	{
		*start = node;
		node->next = *start;
		node->previous = *start;
	}
}

void		destroy_conso_list(t_consumable **start)
{
	t_consumable	*tmp;

	if (start != NULL && *start != NULL)
	{
		tmp = *start;
		while (tmp != NULL)
		{
			*start = tmp->next;
			free(tmp);
			tmp = NULL;
			tmp = *start;
		}
		*start = NULL;
	}
}
