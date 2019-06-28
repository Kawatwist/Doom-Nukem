/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consumable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:15:05 by naali             #+#    #+#             */
/*   Updated: 2019/06/28 17:38:24 by naali            ###   ########.fr       */
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


static int		check_nodes(t_consumable **start, t_consumable *node, int qty, int *id)
{
	t_consumable	*tmp;

	if (start == NULL || *start == NULL)
		return (0);
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
		*id -= 1;
		return (1);
	}
	return (0);
}

t_consumable	*new_conso(char *name, unsigned int qty, t_consumable **start)
{
	t_consumable			*conso;
	static unsigned int		id = 0;

	if ((conso = (t_consumable*)malloc(sizeof(t_consumable))) == NULL)
	{
		ft_putstr("erreur de malloc dans new_conso\n");// Modifier fonction d'erreur...
		exit(-1);
	}
	conso->id = ++id;
	(name != NULL) ? ft_strcpy(conso->name, name) \
		: ft_putstr("error conso name\n");// Modifier fonction erreur...
	conso->type = (ft_strncmp(name, "potion", 6) == 0) ? 1 : 2;
	if (conso->type == 1)
		conso->used = (ft_strlen(conso->name) <= 7) ? 30 : 50;
	else
		conso->used = (ft_strlen(conso->name) <= 8) ? 50 : 100;
	conso->qty = qty;
	conso->use = (conso->type == 1) ? &use_potion : &use_battery;
	conso->next = NULL;
	conso->previous = NULL;
	if (check_nodes(start, conso, conso->qty, &id) != 0)
		return (NULL);
	return (conso);
}

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

int			conso_list_len(t_consumable **start)
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

static void	swap_ptr(t_consumable **ptr1, t_consumable **ptr2)
{
	t_consumable	*tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

static t_consumable *get_conso_by_id(t_consumable **start, unsigned int id)
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

void		conso_swap_elem(t_consumable **start, unsigned int id1, unsigned int id2)
{
	t_consumable	*elem1;
	t_consumable	*elem2;
	t_consumable	*tmp1;
	t_consumable	*tmp2;

	elem1 = get_conso_by_id(start, id1);
	elem2 = get_conso_by_id(start, id2);
	if (elem1 != NULL && elem2 != NULL)
	{
		/* tmp1 = *start; */
		/* while (tmp1->next != *start) */
		/* { */
		/* 	printf("id = %d, name = %s\n", tmp1->id, tmp1->name); */
		/* 	tmp1 = tmp1->next; */
		/* } */
		/* printf("id = %d, name = %s\n", tmp1->id, tmp1->name); */

		/* tmp1 = &(elem1->previous); */
		/* tmp2 = &(elem2->previous); */

		/* printf("next1 = %p, next2 = %p\n", elem1->next, elem2->next); */
		/* swap_ptr(&(elem1->next), &(elem2->next)); */
		/* printf("next1 = %p, next2 = %p\n\n", elem1->next, elem2->next); */
		/* printf("prev1 = %p, prev2 = %p\n", *tmp1, *tmp2); */
		/* swap_ptr(tmp1, tmp2); */
		/* printf("prev1 = %p, prev2 = %p\n\n", *tmp1, *tmp2); */

		tmp1 = elem1->previous;
		tmp2 = elem2->previous;

		swap_ptr(&(elem1->previous), &(elem2->previous));
		if (elem1->previous == elem1)
			elem1->previous = elem2;
		if (elem2->previous == elem2)
			elem2->previous = elem1;

		tmp1->next = elem2;
		tmp2->next = elem1;
		tmp1 = elem1->next;
		tmp2 = elem2->next;

		swap_ptr(&(elem1->next), &(elem2->next));
		if (elem1->next == elem1)
			elem1->next = elem2;
		if (elem2->next == elem2)
			elem2->next = elem1;

		tmp1->previous = elem2;
		tmp2->previous = elem1;

		/* printf("elem1 = %p, elem2 = %p\n", elem1, elem2); */
		/* swap_ptr(&elem1, &elem2); */
		/* printf("elem1 = %p, elem2 = %p\n\n", elem1, elem2); */
		elem1->id = id2;
		elem2->id = id1;
		tmp1 = *start;
		while (tmp1->next != *start)
		{
			printf("id = %d, name = %s\n", tmp1->id, tmp1->name);
			tmp1 = tmp1->next;
		}
		printf("id = %d, name = %s\n", tmp1->id, tmp1->name);
	}
}

void		destroy_conso_list(t_consumable **start)
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
