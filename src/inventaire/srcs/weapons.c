/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:05:26 by naali             #+#    #+#             */
/*   Updated: 2019/06/27 20:44:06 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "inventaire.h"

void			init_names_n_dmg(char ***names, unsigned int (*dmg)[12][3]);
void			free_tab_names(char ***n);

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

t_weapons		*new_weapon(char *name, int type, int max_ammo)
{
	t_weapons			*weap;
	char				**names;
	unsigned int		dmg[12][3];
	static unsigned int	id;
	int					i;

	i = -1;
	if ((weap = (t_weapons*)malloc(sizeof(t_weapons))) == NULL)
	{
		ft_putstr("erreur de malloc dans new_weap\n");// Modifier fonction d'erreur...
		exit(-1);
	}
	init_names_n_dmg(&names, &dmg);
	if ((i = select_damage(name, names)) < 0)
	{
		free(weap);
		return (NULL);
	}
	weap->dmg[0] = dmg[i][0];
	weap->dmg[1] = dmg[i][1];
	weap->dmg[2] = dmg[i][2];
	id++;
	weap->id = id;
	weap->name = name;
	weap->type = type;
	free_tab_names(&names);
	weap->munition = max_ammo;
	weap->max_ammo = max_ammo;
	weap->shoot = NULL;// A modifier
	weap->reload = NULL;// A modifier
	weap->next = NULL;
	weap->previous = NULL;
}
