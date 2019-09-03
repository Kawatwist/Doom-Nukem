/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventaire_init_weapons.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 18:21:44 by naali             #+#    #+#             */
/*   Updated: 2019/09/03 11:20:36 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "inventaire.h"

static void		init_weapon_names(char ***wp)
{
	int		i;

	i = 0;
	if ((*wp = (char**)malloc(sizeof(char*) * 12)) == NULL)
		return ;
	(*wp)[0] = ft_strdup("Poignard");
	(*wp)[1] = ft_strdup("Trident");
	(*wp)[2] = ft_strdup("Arc");
	(*wp)[3] = ft_strdup("Arc Futuriste");
	(*wp)[4] = ft_strdup("Boomrang");
	(*wp)[5] = ft_strdup("Shotgun laser");
	(*wp)[6] = ft_strdup("Harpon");
	(*wp)[7] = ft_strdup("Shuriken");
	(*wp)[8] = ft_strdup("Lance");
	(*wp)[9] = ft_strdup("Kunai");
	(*wp)[10] = ft_strdup("Filet");
	(*wp)[11] = ft_strdup("Explosif");
}

static void		init_weapon_damages(unsigned int (*wp)[12][3])
{
	/* Poignard */
	(*wp)[0][0] = 60; (*wp)[0][1] = 65; (*wp)[0][2] = 70;
	/* Trident */
	(*wp)[1][0] = 80; (*wp)[1][1] = 85; (*wp)[1][2] = 90;
	/* Arc */
	(*wp)[2][0] = 40; (*wp)[2][1] = 50; (*wp)[2][2] = 60;
	/* Arc futuriste */
	(*wp)[3][0] = 50; (*wp)[3][1] = 70; (*wp)[3][2] = 90;
	/* Boomrang */
	(*wp)[4][0] = 80; (*wp)[4][1] = 85; (*wp)[4][2] = 90;
	/* Shotgun laser */
	(*wp)[5][0] = 70; (*wp)[5][1] = 80; (*wp)[5][2] = 90;
	/* Harpon */
	(*wp)[6][0] = 70; (*wp)[6][1] = 75; (*wp)[6][2] = 80;
	/* Shuriken */
	(*wp)[7][0] = 80; (*wp)[7][1] = 85; (*wp)[7][2] = 90;
	/* Lance */
	(*wp)[8][0] = 60; (*wp)[8][1] = 65; (*wp)[8][2] = 70;// Range = CaC + 20
	/* Kunai */
	(*wp)[9][0] = 40; (*wp)[9][1] = 45; (*wp)[9][2] = 50;// Range = CaC + 20
	/* Filet */
	(*wp)[10][0] = 0; (*wp)[10][1] = 5; (*wp)[10][2] = 10;// Slow * lvl
	/* Explosif */
	(*wp)[11][0] = 60; (*wp)[11][1] = 65; (*wp)[11][2] = 70;// Zone d'explosion 3
}

void			free_tab_names(char ***n)
{
	int		i;

	i = 0;
	if (n != NULL && *n != NULL)
	{
		while (i < 12 && (*n)[i] != NULL)
		{
			free((*n)[i]);
			(*n)[i] = NULL;
			i++;
		}
		free(*n);
		*n = NULL;
	}
}

void			init_names_n_dmg(char ***names, unsigned int (*dmg)[12][3])
{
	init_weapon_names(names);
	init_weapon_damages(dmg);
}
