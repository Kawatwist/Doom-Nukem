/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:05:26 by naali             #+#    #+#             */
/*   Updated: 2019/06/28 14:23:01 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "inventaire.h"

static int		select_damage(char *name, char **tab)
{
	int		i;

	i = 0;
	while (i < 12 && tab[i] != NULL)
	{
		if (ft_strcmp(name, tab[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void		malloc_free_weapon(t_weapons **weap, int choice)
{
	if (choice == 1)
	{
		if ((*weap = (t_weapons*)malloc(sizeof(t_weapons))) == NULL)
		{
			ft_putstr("Erreur de malloc dans new_weap\n");// Modifier fonction d'erreur...
			exit(-1);
		}
	}
	else if (choice == -1)
	{
		free(*weap);
		*weap = NULL;
		ft_putstr("Erreur de nom d'arme\n");// Modifier fonction d'erreur...
	}
}

t_weapons		*new_weapon(char *name, int type, int max_ammo)
{
	t_weapons			*weap;
	char				**names;
	unsigned int		dmg[12][3];
	static unsigned int	id;
	int					i;

	i = -1;
	malloc_free_weapon(&weap, 1);
	init_names_n_dmg(&names, &dmg);
	((i = select_damage(name, names)) < 0) ? malloc_free_weapon(&weap, -1) : 0;
	if (i < 0)
		return (NULL);
	weap->dmg[0] = dmg[i][0];
	weap->dmg[1] = dmg[i][1];
	weap->dmg[2] = dmg[i][2];
	weap->id = ++id;
	weap->name = name;
	weap->type = type;
	free_tab_names(&names);
	weap->munition = max_ammo;
	weap->max_ammo = max_ammo;
	select_shot_reload(weap, weap->type);
	weap->next = NULL;
	weap->previous = NULL;
	return (weap);
}
