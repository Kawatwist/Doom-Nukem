/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consumable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:15:05 by naali             #+#    #+#             */
/*   Updated: 2019/06/24 10:55:31 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inventaire.h"

static void		use_potion(t_joueur *p, t_consumable *c)
{
	if (p->vie < 100)
	{
		c->qty -= 1;
		p->vie += c->used;
	}
	if (p->vie > 100)
		p->vie == 100;
}

static void		use_battery(t_joueur *p, t_consumable *c)
{
	if (p->energie < 100)
	{
		c->qty -= 1;
		p->energie += c->used;
	}
	if (p->energie > 100)
		p->energie == 100;
}

t_consumable	*new_conso(char *name, unsigned int qty)
{
	t_consumable			*conso;
	static unsigned int		id = 0;

	if ((conso = (t_consumble*)malloc(sizeof(t_consumable))) == NULL)
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
		conso->use = NULL;// Modifier NULL par l'addresse de la fonction d'utilisation des potions
	else
		conso->use = NULL;// Modifier NULL par l'addresse de la fonction d'utilisation des batteries
	conso->next = NULL;
	conso->previous = NULL;
	return (conso);
}

void			pushback_conso(t_consumable **start, t_consumable *node)
{
	t_consumable	*tmp;

	if (start != NULL && *start != NULL)
	{
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

void		drestroy_conso_list(t_consumable **start)
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
