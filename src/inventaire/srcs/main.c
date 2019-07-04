/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:47:34 by naali             #+#    #+#             */
/*   Updated: 2019/07/04 16:13:11 by naali            ###   ########.fr       */
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
/* PLAYER */
	init_player(&j, "Bob");

/* WEAPONS */
	/* pushback_weapons(&(j.inv->weapo), new_weapon("Explosif", ZONE, 4)); */
	/* pushback_weapons(&(j.inv->weapo), new_weapon("Lance", CAC, 1)); */
	/* pushback_weapons(&(j.inv->weapo), new_weapon("Explosif", ZONE, 4)); */
	/* pushback_weapons(&(j.inv->weapo), new_weapon("Lance", CAC, 1)); */
	/* pushback_weapons(&(j.inv->weapo), new_weapon("Explosif", ZONE, 4)); */
	/* pushback_weapons(&(j.inv->weapo), new_weapon("Lance", CAC, 1)); */
	if (j.inv->weapo != NULL)
	{
		printf("id = %d, name = %s, type = %d, dmg1 = %u\n", j.inv->weapo->id, j.inv->weapo->name, j.inv->weapo->type, j.inv->weapo->dmg[1]);
		j.inv->weapo->shoot();
		j.inv->weapo->previous->shoot();
		j.inv->weapo->previous->previous->shoot();
		j.inv->weapo->next->next->shoot();
	}

/* CONSUMABLE */
	pushback_conso(&(j.inv->conso), new_conso("potion", 3, &(j.inv->conso)));
	pushback_conso(&(j.inv->conso), new_conso("potion", 3, &(j.inv->conso)));
	pushback_conso(&(j.inv->conso), new_conso("potion", 3, &(j.inv->conso)));
	pushback_conso(&(j.inv->conso), new_conso("potion", 3, &(j.inv->conso)));
	pushback_conso(&(j.inv->conso), new_conso("potionV2", 3, &(j.inv->conso)));
	pushback_conso(&(j.inv->conso), new_conso("batterie", 5, &(j.inv->conso)));
	pushback_conso(&(j.inv->conso), new_conso("batterieV2", 5, &(j.inv->conso)));
	printf("qty = %d, used = %d\n", j.inv->conso->qty, j.inv->conso->used);
	j.inv->conso->use(&j, j.inv->conso);
	j.inv->conso->use(&j, j.inv->conso);
	j.inv->conso->use(&j, j.inv->conso);
	j.inv->conso->use(&j, j.inv->conso);
	j.inv->conso->use(&j, j.inv->conso);
	j.inv->conso->use(&j, j.inv->conso);
	j.inv->conso->next->use(&j, j.inv->conso->next);
	j.inv->conso->previous->use(&j, j.inv->conso->previous);

	printf("NB conso = %d\n", conso_list_len(&(j.inv->conso)));
	conso_swap_elem(&(j.inv->conso), 2, 4);
	conso_swap_elem(&(j.inv->conso), 3, 4);
	destroy_one_conso(&(j.inv->conso), 1);
	printf("NB conso = %d\n", conso_list_len(&(j.inv->conso)));
	printf("NB weapo = %d\n", weapo_list_len(&(j.inv->weapo)));
	destroy_conso_list(&(j.inv->conso));
	destroy_weapo_list(&(j.inv->weapo));
	return (0);
}
