/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser_polygons.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:54:18 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/30 10:31:19 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

void			ft_add_vertex(t_myvec **vertex_lst, t_myvec *vertex_node)
{
	t_myvec *keep;

	keep = *vertex_lst;
	if (*vertex_lst == NULL)
	{
		vertex_node->next = NULL;
		*vertex_lst = vertex_node;
	}
	else
	{
		while ((*vertex_lst)->next != NULL)
			*vertex_lst = (*vertex_lst)->next;
		vertex_node->next = NULL;
		(*vertex_lst)->next = vertex_node;
		*vertex_lst = keep;
	}
}

void			ft_go_to_first_vertex(char *line, int *j)
{
	while(line[*j] != ':' )
		*j = *j + 1;
	*j = *j + 1;
}

t_mypolygon	*ft_create_polygon_node(t_myvec *vertex_lst)
{
	t_mypolygon	*polygon_node;

	polygon_node = (t_mypolygon*)malloc(sizeof(t_mypolygon));
	polygon_node->vertex_lst = vertex_lst;
	return(polygon_node);
}

void	ft_add_polygon(t_mypolygon **polygon_lst, t_mypolygon *polygon_node)
{
	t_mypolygon		*keep;

	keep = *polygon_lst;
	if (*polygon_lst == NULL)
	{
		polygon_node->next = NULL;
		*polygon_lst = polygon_node;
	}
	else
	{
		while ((*polygon_lst)->next != NULL)
			*polygon_lst = (*polygon_lst)->next;
		polygon_node->next = NULL;
		(*polygon_lst)->next = polygon_node;
		*polygon_lst = keep;

		/* polygon_node->next = *polygon_lst; */
		/* *polygon_lst = polygon_node; */
	}
}

t_myvec			ft_get_vertex(char *line)
{
	int			k;
	char		nbr[1000];
	t_myvec		s_vertex;
	int			i;

	i = 2;
	k = 0;

	while(ft_isdigit(line[i]) || line[i] == '-' || line[i] == '.' )
	{
		nbr[k] = line[i];
		i++;
		k++;
	}
	nbr[k] = '\0';
	/* printf("le nombre =%s\n", nbr); */
	s_vertex.x = ft_atoi_comma(nbr);
	/* printf(" =%f\n", ft_atoi_comma(nbr)); */

	k = 0;
	while (line[i] == ' ')
		i++;
	while(ft_isdigit(line[i]) || line[i] == '-' || line[i] == '.' )
	{
		nbr[k] = line[i];
		i++;
		k++;
	}
	nbr[k] = '\0';
	s_vertex.y = ft_atoi_comma(nbr);
	/* printf(" =%f\n", ft_atoi_comma(nbr)); */

	k = 0;
	while (line[i] == ' ')
		i++;
	while(ft_isdigit(line[i]) || line[i] == '-' || line[i] == '.' )
	{
		nbr[k] = line[i];
		i++;
		k++;
	}
	nbr[k] = '\0';
	s_vertex.z = ft_atoi_comma(nbr);
	/* printf(" =%f\n", ft_atoi_comma(nbr)); */
	/* printf("\n\n"); */
	return (s_vertex);
}
int		ft_get_the_vertex_number(char *line, int *j)
{
	while (line[*j] != ' ')
		*j = *j + 1;
	*j = *j + 1;
	return (line[*j] - '0');
}


typedef struct		s_myfichier
{
	char				*line;
	struct s_myfichier	*next;
}					t_myfichier;


t_myfichier		*ft_create_line_node(char *line)
{
	t_myfichier		*fichier_node;

	fichier_node = (t_myfichier*)malloc(sizeof(t_myfichier));
	//line = (char*)malloc(sizeof(ft_strlen(line) + 10));
	line = ft_strdup(line);
	fichier_node->line = line;
	return (fichier_node);
}


void			ft_add_line_node(t_myfichier **fichier_lst, t_myfichier *fichier_node)
{
	t_myfichier		*keep;

	keep = *fichier_lst;
	if (*fichier_lst == NULL)
	{
		fichier_node->next = NULL;
		*fichier_lst = fichier_node;
	}
	else
	{
		while ((*fichier_lst)->next != NULL)
			*fichier_lst = (*fichier_lst)->next;
		fichier_node->next = NULL;
		(*fichier_lst)->next = fichier_node;
		*fichier_lst = keep;
	}
}

t_mypolygon		*ft_read_the_polygon_file(void)
{
	int				fd;
	char			*line = NULL;
	t_myvec			*vertex_node;
	t_myvec			*vertex_lst = NULL;
	t_mypolygon		*polygon_node;
	t_mypolygon		*polygon_lst = NULL;
	int				j;
	int				polygon_obj_indice;

	int i = -1;



	t_myfichier		*fichier_lst;
	t_myfichier		*fichier_node;

	fichier_lst = NULL;

	fd = open("src/jeronemo/dir_bsp/VideoShip.obj", O_RDWR);
	while(get_next_line(fd, &line))
	{
		fichier_node = ft_create_line_node(line);
		ft_add_line_node(&fichier_lst, fichier_node);
	}

	t_myfichier	*keep_fichier;

	keep_fichier = fichier_lst;
	while (fichier_lst != NULL)
	{

		printf("=%s\n", fichier_lst->line);
		fichier_lst = fichier_lst->next;
	}
	fichier_lst = keep_fichier;



	t_mypolygon	*keep;
	t_myvec		*keep_vec;

	/* printf("===> L'ecture des indices\n"); */
	polygon_obj_indice = 0;



	keep_fichier = fichier_lst;
	while(fichier_lst != NULL)
	{
		if (fichier_lst->line[0] == 'f' && fichier_lst->line[1] == ' ')
		{
			i++;
			printf("Polynome n=%d\n", i);
			j = 1;
			printf("les indices =");
			while (fichier_lst->line[j] != '\0')
			{
				j++;
				vertex_node = NULL;
				vertex_node = (t_myvec*)malloc(sizeof(t_myvec));
				vertex_node->obj_indice = (int)ft_atoi_comma(&(fichier_lst->line[j]));
				printf(" =%d  ", vertex_node->obj_indice);
				ft_add_vertex(&vertex_lst, vertex_node);
				while (fichier_lst->line[j] != ' ' && fichier_lst->line[j] != '\0')
					j++;
			}
			/* printf("\n"); */
			polygon_node = ft_create_polygon_node(vertex_lst);
			polygon_node->obj_indice = polygon_obj_indice;
			printf("On a ajouter le polygone =%d\n\n", polygon_node->obj_indice);
			polygon_obj_indice++;
			ft_add_polygon(&polygon_lst, polygon_node);
			vertex_lst = NULL;
		}
		fichier_lst = fichier_lst->next;
	}
	fichier_lst = keep_fichier;



	int vertex_add = 0;

	t_myvec		vertex;
	keep = polygon_lst;
	int		current_vertex;
	while (polygon_lst != NULL)
	{
		keep_vec = polygon_lst->vertex_lst;
		while (polygon_lst->vertex_lst != NULL)
		{
			current_vertex = 0;
			vertex_add = 0;
			keep_fichier = fichier_lst;
			while(fichier_lst != NULL && polygon_lst->vertex_lst != NULL && vertex_add == 0)
			{
				printf("==%s\n", fichier_lst->line);
				if (fichier_lst->line[0] == 'v' && fichier_lst->line [1] == ' ')
					current_vertex++;
				printf("=current vertex =%d\n", current_vertex);
				if (current_vertex == polygon_lst->vertex_lst->obj_indice)
				{
					printf("A Le polygone n =%d\n", polygon_lst->obj_indice);
					printf("B la ligne =%s\n", fichier_lst->line);
					printf("On ajoute le vecteur d'indice =%d\n", polygon_lst->vertex_lst->obj_indice);
					vertex = ft_get_vertex(fichier_lst->line);
					printf("vertex node x=%f\n", vertex.x);
					printf("vertex node y=%f\n", vertex.y);
					printf("vertex node z=%f\n", vertex.z);
					polygon_lst->vertex_lst->x =  vertex.x;
					polygon_lst->vertex_lst->y =  vertex.y;
					polygon_lst->vertex_lst->z =  vertex.z;
					printf("ladreese next =%p\n", polygon_lst->vertex_lst->next);
					polygon_lst->vertex_lst = polygon_lst->vertex_lst->next;
					printf("\n\n\n");
					vertex_add = 1;
				}
				fichier_lst = fichier_lst->next;
			}
			fichier_lst = keep_fichier;

		}
		polygon_lst->vertex_lst = keep_vec;
		polygon_lst = polygon_lst->next;
	}
	polygon_lst = keep;




	printf("PARSEUR FICHIER OBJ\n");

	keep = polygon_lst;
	while (polygon_lst != NULL)
	{
		printf("Polygon n=%d\n", polygon_lst->obj_indice);
		printf("La liste des indes \n");
		keep_vec = polygon_lst->vertex_lst;
		while (polygon_lst->vertex_lst != NULL)
		{
			printf(" =%d ", polygon_lst->vertex_lst->obj_indice);   
			printf("  x=%f  y=%f  z=%f   \n", polygon_lst->vertex_lst->x, polygon_lst->vertex_lst->y, polygon_lst->vertex_lst->z);
			polygon_lst->vertex_lst = polygon_lst->vertex_lst->next;
		}
		printf("\n");
		polygon_lst->vertex_lst = keep_vec;
		polygon_lst = polygon_lst->next;
	}
	polygon_lst = keep;

	return (polygon_lst);
}
