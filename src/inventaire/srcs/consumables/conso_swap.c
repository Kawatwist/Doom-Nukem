/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_conso.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 07:08:47 by naali             #+#    #+#             */
/*   Updated: 2019/07/01 08:22:19 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "inventaire.h"

static void		swap_conso(t_consumable **ptr1, t_consumable **ptr2)
{
	t_consumable	*tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

static void		conso_apply_swap(t_consumable **elem1, t_consumable **elem2)
{
	unsigned int	tmp;
	t_consumable	*tmp1;
	t_consumable	*tmp2;

	tmp1 = (*elem1)->previous;
	tmp2 = (*elem2)->previous;
	swap_conso(&((*elem1)->previous), &((*elem2)->previous));
	if ((*elem1)->previous == (*elem1))
		(*elem1)->previous = (*elem2);
	if ((*elem2)->previous == (*elem2))
		(*elem2)->previous = (*elem1);
	tmp1->next = (*elem2);
	tmp2->next = (*elem1);
	tmp1 = (*elem1)->next;
	tmp2 = (*elem2)->next;
	swap_conso(&((*elem1)->next), &((*elem2)->next));
	(*elem1)->next = ((*elem1)->next == (*elem1)) ? (*elem2) : (*elem1)->next;
	(*elem2)->next = ((*elem2)->next == (*elem2)) ? (*elem1) : (*elem2)->next;
	tmp1->previous = (*elem2);
	tmp2->previous = (*elem1);
	tmp = (*elem1)->id;
	(*elem1)->id = (*elem2)->id;
	(*elem2)->id = tmp;
}

void			conso_swap_elem(t_consumable **start, \
								unsigned int id1, unsigned int id2)
{
	t_consumable	*elem1;
	t_consumable	*elem2;

	elem1 = get_conso_by_id(start, id1);
	elem2 = get_conso_by_id(start, id2);
	if (elem1 != NULL && elem2 != NULL && elem1 != elem2)
		conso_apply_swap(&elem1, &elem2);
}
