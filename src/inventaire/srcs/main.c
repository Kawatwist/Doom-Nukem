/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:47:34 by naali             #+#    #+#             */
/*   Updated: 2019/06/27 20:46:21 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "inventaire.h"

void		init_player(t_joueurs *j, char *name)
{
	if ((j->inv = (t_inventaire*)malloc(sizeof(t_inventaire))) == NULL)
		exit(-1);
	j->inv->conso = NULL;
	j->inv->weapo = NULL;
	j->name = name;
	j->vie = 50;
	j->energie = 50;
}

int			main(void)
{
	t_joueurs		j;

	init_player(&j, "Bob");
	j.inv->weapo = new_weapon("Explosif", ZONE, 4);
	if (j.inv->weapo != NULL)
	{
		printf("id = %d, name = %s, type = %d, dmg1 = %u\n", j.inv->weapo->id, j.inv->weapo->name, j.inv->weapo->type, j.inv->weapo->dmg[1]);
	}
	pushback_conso(&(j.inv->conso), new_conso("potion", 3));
	pushback_conso(&(j.inv->conso), new_conso("potion", 3));
	pushback_conso(&(j.inv->conso), new_conso("potion", 3));
	pushback_conso(&(j.inv->conso), new_conso("potion", 3));
	pushback_conso(&(j.inv->conso), new_conso("batterie", 5));
	printf("qty = %d, used = %d\n", j.inv->conso->qty, j.inv->conso->used);
	j.inv->conso->use(&j, j.inv->conso);
	j.inv->conso->use(&j, j.inv->conso);
	j.inv->conso->use(&j, j.inv->conso);
	j.inv->conso->use(&j, j.inv->conso);
	j.inv->conso->use(&j, j.inv->conso);
	j.inv->conso->use(&j, j.inv->conso);
	j.inv->conso->next->use(&j, j.inv->conso->next);
	j.inv->conso->previous->use(&j, j.inv->conso->previous);
	return (0);
}
