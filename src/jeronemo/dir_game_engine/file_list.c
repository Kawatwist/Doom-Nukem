/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 17:43:53 by lomasse           #+#    #+#             */
/*   Updated: 2019/08/25 16:56:37 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <header_game_engine.h>

// CALCUL ZBUFF
// SI LST == NULL CREATE NEW MAILLONT
// ELSE 
// 		FIND_PLACE
// 		ADD /!\ CHECK IF THE FIRST TRIANGLE CAN BE CHANGED (I DONT THINK)

static float	calcul_zbuff(t_mytriangle *triangle)
{
	return ((triangle->vertice[0].z + triangle->vertice[1].z + triangle->vertice[2].z) / 3);
}

void			ft_store_in_lst(t_mytriangle *toadd, t_mytriangle **head)
{
	t_mytriangle *curr;
	/* t_mytriangle *tmp; */

	toadd->zbuff = calcul_zbuff(toadd);
	if (*head == NULL)
		*head = toadd;
	else
	{
		curr = *head;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = toadd;
		toadd->next = NULL;



		/* while (curr->next != NULL && toadd->zbuff > curr->next->zbuff) */
		/* 	curr = curr->next; */
		/* if (curr->next == NULL) */
		/* 	curr->next = toadd; */
		/* else */
		/* { */
		/* 	if (curr == *head) */
		/* 	{ */
		/* 		*head = toadd; */
		/* 		(*head)->next = curr; */
		/* 	} */
		/* 	else */
		/* 	{ */
		/* 		tmp = curr->next; */
		/* 		curr->next = toadd; */
		/* 		toadd->next = tmp; */
		/* 	} */
		/* } */
	}
}
