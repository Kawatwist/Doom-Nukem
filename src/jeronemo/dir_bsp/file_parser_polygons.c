/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser_polygons.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:54:18 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/08 19:45:24 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h> 

/* t_myvec			*ft_get_and_create_vertex_node(char *line, int *j) */
/* { */
/* 	int			k; */
/* 	char		nbr[1000]; */
/* 	t_myvec		*s_vertex; */

/* 	s_vertex = (t_myvec*)malloc(sizeof(t_myvec)); */
/* 	k = 0; */
/* 	while(ft_isdigit(line[*j]) || line[*j] == '-' || line[*j] == '.' ) */
/* 	{ */
/* 		nbr[k] = line[*j]; */
/* 		*j = *j + 1; */
/* 		k++; */
/* 	} */
/* 	nbr[k] = '\0'; */
/* 	//printf("le nombre =%s\n", nbr); */
/* 	s_vertex->x = ft_atoi_comma(nbr); */
/* 	//printf(" =%f\n", ft_atoi_comma(nbr)); */

/* 	k = 0; */
/* 	while (line[*j] == ' ') */
/* 		*j = *j + 1; */
/* 	while(ft_isdigit(line[*j]) || line[*j] == '-' || line[*j] == '.' ) */
/* 	{ */
/* 		nbr[k] = line[*j]; */
/* 		*j = *j + 1; */
/* 		k++; */
/* 	} */
/* 	nbr[k] = '\0'; */
/* 	s_vertex->y = ft_atoi_comma(nbr); */
/* 	//printf(" =%f\n", ft_atoi_comma(nbr)); */

/* 	k = 0; */
/* 	while (line[*j] == ' ') */
/* 		*j = *j + 1; */
/* 	while(ft_isdigit(line[*j]) || line[*j] == '-' || line[*j] == '.' ) */
/* 	{ */
/* 		nbr[k] = line[*j]; */
/* 		*j = *j + 1; */
/* 		k++; */
/* 	} */
/* 	nbr[k] = '\0'; */
/* 	s_vertex->z = ft_atoi_comma(nbr); */
/* 	//printf(" =%f\n", ft_atoi_comma(nbr)); */
/* 	//printf("\n\n"); */
/* 	return (s_vertex); */
/* } */

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
	if (*polygon_lst == NULL)
	{
		polygon_node->next = NULL;
		*polygon_lst = polygon_node;
	}
	else
	{
		polygon_node->next = *polygon_lst;
		*polygon_lst = polygon_node;
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
	printf("le nombre =%s\n", nbr);
	s_vertex.x = ft_atoi_comma(nbr);
	printf(" =%f\n", ft_atoi_comma(nbr));

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
	printf(" =%f\n", ft_atoi_comma(nbr));

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
	printf(" =%f\n", ft_atoi_comma(nbr));
	printf("\n\n");
	return (s_vertex);
}
int		ft_get_the_vertex_number(char *line, int *j)
{
	while (line[*j] != ' ')
		*j = *j + 1;
	*j = *j + 1;
	return (line[*j] - '0');
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


	t_mypolygon	*keep;
	t_myvec		*keep_vec;

	printf("===> L'ecture des indices\n");
	polygon_obj_indice = 0;
	fd = open("src/jeronemo/dir_bsp/two_square.obj", O_RDWR);
	while(get_next_line(fd, &line))
	{
		if (line[0] == 'f' && line[1] == ' ')
		{
			i++;
			printf("Polynome n=%d\n", i);
			j = 1;
			printf("les indices =");
			while (line[j] != '\0')
			{
				j++;
				vertex_node = NULL;
				vertex_node = (t_myvec*)malloc(sizeof(t_myvec));
				vertex_node->obj_indice = (int)ft_atoi_comma(&(line[j]));
				printf(" =%d  ", vertex_node->obj_indice);
				ft_add_vertex(&vertex_lst, vertex_node);
				while (line[j] != ' ' && line[j] != '\0')
					j++;
			}
			printf("\n");
			polygon_node = ft_create_polygon_node(vertex_lst);
			polygon_node->obj_indice = polygon_obj_indice;
			printf("On a ajouter le polygone =%d\n\n", polygon_node->obj_indice);
			polygon_obj_indice++;
			ft_add_polygon(&polygon_lst, polygon_node);
			vertex_lst = NULL;
		}
	}
	close(fd);


	keep = polygon_lst;
	while (polygon_lst != NULL)
	{
		printf("Polygon n=%d\n", polygon_lst->obj_indice);
		printf("La liste des indes ");
		keep_vec = polygon_lst->vertex_lst;
		while (polygon_lst->vertex_lst != NULL)
		{
			printf(" =%d ", polygon_lst->vertex_lst->obj_indice);   
			polygon_lst->vertex_lst = polygon_lst->vertex_lst->next;
		}
		printf("\n");
		polygon_lst->vertex_lst = keep_vec;
		polygon_lst = polygon_lst->next;
	}
	polygon_lst = keep;

	exit(0);

	t_myvec		vertex;
	keep = polygon_lst;
	int		current_vertex;
	while (polygon_lst != NULL)
	{
		keep_vec = polygon_lst->vertex_lst;
		while (polygon_lst->vertex_lst != NULL)
		{
			fd = open("src/jeronemo/dir_bsp/two_square.obj", O_RDWR);
			current_vertex = 0;
			while(get_next_line(fd, &line) && polygon_lst->vertex_lst != NULL)
			{
				if (line[0] == 'v' && line [1] == ' ')
					current_vertex++;
				if (current_vertex == polygon_lst->vertex_lst->obj_indice)
				{
					printf("ZZZZ Le polygone n =%d\n", polygon_lst->obj_indice);
					printf("AAAAA la ligne =%s\n", line);
					printf("On ajoute le vecteur d'indice =%d\n", polygon_lst->vertex_lst->obj_indice);
					vertex = ft_get_vertex(line);
					printf("vertex node x=%f\n", vertex.x);
					printf("vertex node y=%f\n", vertex.y);
					printf("vertex node z=%f\n", vertex.z);
					polygon_lst->vertex_lst->x =  vertex.x;
					polygon_lst->vertex_lst->y =  vertex.y;
					polygon_lst->vertex_lst->z =  vertex.z;
					//printf("ladreese next =%p\n", polygon_lst->vertex_lst->next);
					polygon_lst->vertex_lst = polygon_lst->vertex_lst->next;
				}
			}
			close (fd);
		}
		polygon_lst->vertex_lst = keep_vec;
		polygon_lst = polygon_lst->next;
	}
	polygon_lst = keep;

	//ON affiche la list
	keep = polygon_lst;
	while (polygon_lst != NULL)
	{
		keep_vec = polygon_lst->vertex_lst;
		printf("POLYGON n=%d\n", polygon_lst->obj_indice);
		while (polygon_lst->vertex_lst != NULL)
		{
			printf("l'indice obj =%d\n", polygon_lst->vertex_lst->obj_indice);
			printf("vertex x =%f\n", polygon_lst->vertex_lst->x);
			polygon_lst->vertex_lst = polygon_lst->vertex_lst->next;
		}
		polygon_lst->vertex_lst = keep_vec;
		exit (0);
		polygon_lst = polygon_lst->next;
	}
	polygon_lst = keep;
	return (polygon_lst);
}
