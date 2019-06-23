/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_affichage_bsp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:48:43 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/08 10:29:30 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <jeronemo.h>

void		ft_browse_the_bsp(t_mynode *s_node, char **tab,int decalage_pere, int decalage, int rang, int profondeur_max)
{
	int middle = 26;
	char		*value;

	value = ft_itoa((int)s_node->splitter->id);
	tab[rang][middle + decalage + decalage_pere] = value[0];
	decalage_pere = decalage + decalage_pere;
	if (s_node->front->is_leaf != TRUE)
		ft_browse_the_bsp(s_node->front, tab, decalage_pere, pow(2, profondeur_max - (rang + 1)) ,  rang + 1, profondeur_max);
	if (s_node->back->is_leaf != TRUE)
		ft_browse_the_bsp(s_node->back, tab, decalage_pere, -pow(2, profondeur_max - (rang + 1)) ,  rang + 1, profondeur_max);
}

void		ft_display_the_bsp(t_mynode *s_node, char **tab)
{
	(void)s_node;
	int i, j;

	i = j = 0;
	while (i < 50)
	{
		j = 0;
		while (j < 50)
		{
			printf("%c", tab[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void		ft_init_tab(char ***tab)
{
	int i, j;

	i = j = 0;
	*tab = (char**)malloc(sizeof(char*) * 51);
	while (i < 50)
	{
		(*tab)[i] = (char*)malloc(sizeof(char) * 50 );
		j = 0;
		while (j < 50)
		{
			(*tab)[i][j] = '_';
			j++;
		}
		printf("\n");
		i++;
	}
}

void		ft_afficher_le_bsp(t_mynode *s_node)
{
	char		**tab;
	int			decalage = 0;
	int			profondeur_maxi = 4;

	(void)decalage;
	(void)profondeur_maxi;
	ft_init_tab(&tab);
	ft_browse_the_bsp(s_node, tab,0, 0, 0, 4);
	ft_display_the_bsp(s_node, tab);
}
