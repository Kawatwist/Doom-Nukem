/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_to_voidptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 15:27:36 by naali             #+#    #+#             */
/*   Updated: 2019/11/05 14:09:06 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cpy_to_voidptr.h"

/************/
/* todolist */
/************/

/*
  - Formatage des infos DONE
  - mettre le code en relation avec doom IN PROGRESS
  - verifier que la recuperation depuis le client ou le serveur se fait correctement IN PROGRESS
*/

/************/

/***********************************************/
/* ATTENTION MEMCPY A TRANSFORMER EN FT_MEMCPY */
/***********************************************/

/* recuperation de la taille en fonction de l'id */
short	get_type_size(int flg, void *cmd)
{
	short	sz;

	sz = 0;
	if (flg == 1 || flg == 2 || flg == 3)	// Type message ou commande texte
		sz = /*ft_*/strlen((char*)cmd);
	else if (flg == 4)						// Type position en float
		sz = sizeof(float) * 3;
	return (sz);
}

/* Type a envoyer vers la commande  */
int		voidptr_to_string(char **dst, void *src, size_t len)
{
	if (dst != NULL && src != NULL)
	{
		*dst = NULL;
		if ((*dst = (char*)malloc(len)) == NULL)
			return (STCPY_ERROR);
		/*ft_*/memcpy((void*)(*dst), src, len);
	}
	else
		return (STCPY_ERROR);
	return (STCPY_SUCCESS);
}

/* Commande recu vers le type correspondant  */
void		*string_to_voidptr(char *s, size_t len)
{
	void	*ret;

	ret = NULL;
	if ((s == NULL) || ((ret = malloc(len)) == NULL))
		return (NULL);
	/*ft_*/memcpy(ret, (void*)s, len);
	return (ret);
}

/***************************************/
/* Test de formatage de commande DEBUT */
/***************************************/

char		*ft_memcat(char *s1, char *s2, size_t len1, size_t len2)
{
	char			*ret;
	unsigned int	i;

	if ((ret = malloc(sizeof(char) * (len1 + len2 + 2))) == NULL)
		return (NULL);
	i = -1;
	while (++i < len1)
		ret[i] = s1[i];
	i = -1;
	while (++i < len2)
		ret[i + len1] = s2[i];
	return (ret);
}

/* Sera tres certainement MODIFIER pour feat avec les differents type, ou pas!!!!!!! */
char		*cmd_format(char id, short len, void *info)
{
	char			*ret;
	char			tmp[4];
	unsigned int	sz_max;

	ret = NULL;
	if (id <= 0 || len == 0 || info == NULL)
		return (ret);
	sz_max = 6 + len;
	tmp[0] = ';';
	tmp[1] = id;
	tmp[2] = (len >> 8) & 0xFF;
	tmp[3] = len & 0xFF;
	ret = ft_memcat(tmp, info, 4, len);
	ret[sz_max - 2] = ';';
	ret[sz_max - 1] = '\0';
	if (id > 0 && id < 4)
	{
		free(info);
		info = NULL;
	}
	return (ret);
}

char		*pos_to_tab(float x, float y, float z)
{
	char	*ret;
	float	tab[3];

	ret = NULL;
	tab[0] = x;
	tab[1] = y;
	tab[2] = z;
	ret = cmd_format(4, sizeof(float) * 3, (void*)tab);
	return (ret);
}

char		*pos_player_to_tab(t_joueur *j)
{
	char	*ret;
	float	tab[3];

	ret = NULL;
	tab[0] = (float)(j->x);
	tab[1] = (float)(j->y);
	tab[2] = (float)(j->z);
	ret = cmd_format(4, sizeof(float) * 3, (void*)tab);
	return (ret);
0}

/*************************************/
/* Test de formatage de commande FIN */
/*************************************/

/*********************/
/* 3eme Main de test */
/*********************/

int		main()
{
	int		i;
	int		id;
	int		size;
	char	*info;
	char	*test;

	i = 0;
	id = -1;
	test = NULL;
	if (id <= 0)
		test = cmd_format(id, 0, NULL);
	else if (id == 4)
	{
		test = pos_to_tab(0.42f, 4.2f, 42.0f);
		size = 6 + (sizeof(float) * 3);
	}
	else
	{
		info = strdup("test 42");
		size = 6 + strlen(info);
		test = cmd_format(id, size - 6, info);
	}
	while (i < size)
	{
		if (id == 4)
			printf("%d == %d\n", i, test[i]);
		else
			printf("%d == %c\n", i, test[i]);
		i++;
	}
	if (id <= 0)
		printf("%s\n", test);
	free(test);
	test = NULL;
	return (0);
}

/*********************/
/* 2eme Main de test */
/*********************/

/* #include <string.h> */
/* #include <stdio.h> */

/* int		main(int ac, char **av) */
/* { */
/* 	short	size; */
/* 	char	*info; */
/* 	void	*ptr; */

/* 	size = 0; */
/* 	info = NULL; */
/* 	ptr = NULL; */
/* 	if (ac < 2) */
/* 		return (0); */
/* 	info = strdup(av[1]); */
/* 	size = (short)strlen(info); */
/* 	info = cmd_format(1, size, info); */
/* 	if (size > 0) */
/* 		printf("id = |%d|\nlen = |%d|\nstr = |%s|\n",					\ */
/* 			info[1], ((short)(info[2]) << 8) + (short)(info[3]), &info[4]); */
/* 	free(info); */
/* 	info = NULL; */
/* 	return (0); */
/* } */

/*********************/

/***************************************/
/* MAIN d'exemple avec MEMCPY + STRUCT */
/** Pointeur retourner n'est pas FREE **/
/*********** dans l'exemple ************/
/***************************************/

/*
int		main()
{
	int		i = 42;
	float	f = 54687451323545468745.465687f;
	double	d = 534568.54648687864654132135478;
	char	*src = "salut les ami(e)s";
	char	*dst;

	if (voidptr_to_string(&dst, (void*)(&i), sizeof(i)) == -1)
		return (STCPY_ERROR);
	printf("string_to_voidptr int = %d\n\n", *(int*)string_to_voidptr(dst, sizeof(i)));

	free(dst);
	dst = NULL;

	if (voidptr_to_string(&dst, (void*)(&f), sizeof(f)) == -1)
		return (STCPY_ERROR);
	printf("string_to_voidptr float = %.3f\n\n", *(float*)string_to_voidptr(dst, sizeof(f)));

	free(dst);
	dst = NULL;

	if (voidptr_to_string(&dst, (void*)(&d), sizeof(d)) == -1)
		return (STCPY_ERROR);
	printf("string_to_voidptr double = %.40f\n\n", *(double*)string_to_voidptr(dst, sizeof(d)));

	free(dst);
	dst = NULL;

	if (voidptr_to_string(&dst, (void*)(src), strlen(src)) == -1)
		return (STCPY_ERROR);
	printf("string_to_voidptr string = |%s|\n\n", (char*)string_to_voidptr(dst, strlen(src)));
	return (STCPY_SUCCESS);
}
*/
