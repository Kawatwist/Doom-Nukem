/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapo_swap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 08:22:00 by naali             #+#    #+#             */
/*   Updated: 2019/07/01 08:23:09 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "inventaire.h"

static void		swap_weapo(t_weapons **ptr1, t_weapons **ptr2)
{
	t_weapons	*tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

static void		weapo_apply_swap(t_weapons **elem1, t_weapons **elem2)
{
	unsigned int	tmp;
	t_weapons	*tmp1;
	t_weapons	*tmp2;

	tmp1 = (*elem1)->previous;
	tmp2 = (*elem2)->previous;
	swap_weapo(&((*elem1)->previous), &((*elem2)->previous));
	if ((*elem1)->previous == (*elem1))
		(*elem1)->previous = (*elem2);
	if ((*elem2)->previous == (*elem2))
		(*elem2)->previous = (*elem1);
	tmp1->next = (*elem2);
	tmp2->next = (*elem1);
	tmp1 = (*elem1)->next;
	tmp2 = (*elem2)->next;
	swap_weapo(&((*elem1)->next), &((*elem2)->next));
	(*elem1)->next = ((*elem1)->next == (*elem1)) ? (*elem2) : (*elem1)->next;
	(*elem2)->next = ((*elem2)->next == (*elem2)) ? (*elem1) : (*elem2)->next;
	tmp1->previous = (*elem2);
	tmp2->previous = (*elem1);
	tmp = (*elem1)->id;
	(*elem1)->id = (*elem2)->id;
	(*elem2)->id = tmp;
}

void			weapo_swap_elem(t_weapons **start, \
								unsigned int id1, unsigned int id2)
{
	t_weapons	*elem1;
	t_weapons	*elem2;

	elem1 = get_weapo_by_id(start, id1);
	elem2 = get_weapo_by_id(start, id2);
	if (elem1 != NULL && elem2 != NULL && elem1 != elem2)
		weapo_apply_swap(&elem1, &elem2);
}
