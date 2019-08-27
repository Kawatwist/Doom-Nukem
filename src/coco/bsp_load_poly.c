//fonctions pout lire les polygone d'une scene et let mettre dans une liste chainee

// #include <bsp.h>
#include <doom.h>

t_poly* loadMap(char *file) // format Polygon : x1 y1 z1 ; x2 y2 z2 ; .... : "texture.tga"
{
	t_poly	*list;
	//int 	i;
	int		fd;
	char	*line;

	list = NULL;
	if (!(fd = open(file, O_RDONLY)) || read(fd, 0, 0) < 0)
		exit(0);
	while (get_next_line(fd, &line))
	{
		//printf("ADD\n");
		add_poly(&list, line);
		//printf("ENDADD\n");
		free(line);
	}
	close(fd);
	return (list);
}

void add_poly(t_poly **list, char *line)
{
	t_poly *new;
	t_poly *tmp;
	int i;

	if (!(new = (t_poly*)malloc(sizeof(t_poly))))
		exit(0);
	new->ver_list = NULL;
	new->nb_ver = 0;
	new->next = NULL;
	new->was_splitter = 0;
	i = 0;
	while (line[i] && line[i] != ':')
		i++;
	i++;
	add_vertices(new, line, i);
	if (*list == NULL)
	{
		//printf("ON RENTRE PAS LA\n");
		*list = new;
	}
	else
	{
		//printf("IN ThE ELSE %p\n", *new);
		tmp = *list;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
		//printf("OUT OF THE ELSE\n");
	}
}


int count_vertices(char *line, int i)
{
	int j;

	j = 0;
	while (line[i] && line[i] != ':')
	{
		//printf("ICI %d\n",i);
		if (line[i] == ';')
			i++;
		while (line[i] != ' ')
			i++;
		i++;
		while (line[i] != ' ')
			i++;
		i++;
		while (line[i] != ';' && line[i] != ':')
			i++;
		j++;
	}
	return (j);
}

void add_vertices(t_poly *new, char *line, int i)
{
	t_vec *vec;
	//t_vec *tmp;
	int x[5];

	new->nb_ver = count_vertices(line, i);
	//printf("ADD VERTICES %d\n", new->nb_ver);
	if (!(new->ver_list = (t_vec*)malloc(sizeof(t_vec) * new->nb_ver)))
		exit(0);
	x[3] = 0;
	while (line[i] && line[i] != ':')
	{
		//printf("ICI %d\n",i);
		if (line[i] == ';')
			i++;
		x[0] = ft_atoi(&(line[i]));
		while (line[i] != ' ')
			i++;
		i++;
		x[1] = ft_atoi(&(line[i]));
		while (line[i] != ' ')
			i++;
		i++;
		x[2] = ft_atoi(&(line[i]));
		while (line[i] != ';' && line[i] != ':')
			i++;
		vec = create_vec(x[0],x[1],x[2]);
		new->ver_list[x[3]] = *vec;
		x[3]++;
	}
}

void create_normal(t_poly *list)
{
	//direction correcte -> aiguilles du montre
	t_vec *e1;
	t_vec *e2;
	float mag;

	e1 = create_vec(list->ver_list[1].x - list->ver_list[0].x, list->ver_list[1].y - list->ver_list[0].y, list->ver_list[1].z - list->ver_list[0].z);
	e2 = create_vec(list->ver_list[list->nb_ver - 1].x - list->ver_list[0].x, list->ver_list[list->nb_ver - 1].y - list->ver_list[0].y, list->ver_list[list->nb_ver - 1].z - list->ver_list[0].z);
	list->normal.x = (e1->y * e2->z) - (e1->z * e2->y);
	list->normal.y = (e1->z * e2->x) - (e1->x * e2->z);
	list->normal.z = (e1->x * e2->y) - (e1->y * e2->x);
	free(e1);
	free(e2);
	mag = sqrt(list->normal.x * list->normal.x + list->normal.y * list->normal.y + list->normal.z * list->normal.z);
	list->normal.x /= mag;
	list->normal.y /= mag;
	list->normal.z /= mag;
}

void triangulize(t_poly *list) //ajoute les triangles dans indices
{
	t_poly *tmp;
	int i[4];

	tmp = list;
	while (tmp != NULL)
	{
		tmp->nb_indices = (tmp->nb_ver - 2) * 3;
		if (!(tmp->indices = (int*)malloc(sizeof(int) * tmp->nb_indices)))
			exit(0);
		i[0] = 0;
		while (i[0] < tmp->nb_indices / 3)
		{
			if (i[0] == 0)
			{
				i[1] = 0;
				i[2] = 1;
				i[3] = 2;
			}
			else
			{
				i[2] = i[3];
				i[3]++;
			}
			tmp->indices[i[0] * 3] = i[1];
			tmp->indices[(i[0] * 3) + 1] = i[2];
			tmp->indices[(i[0] * 3) + 2] = i[3];
			i[0]++;
		}
		create_normal(tmp);
		tmp = tmp->next;
	}
}

/**
typedef struct s_lo
{
	int fd;
	char *line;
	char **data;

}				t_lo;

typedef struct				s_mypolygon
{
	int						obj_indice;
	t_myvec					*vertex_lst;             //liste des vertex
	t_myvec					normal;                  //la normal au polygon
	int						number_of_vertex;        //nombre de vertex
	int						number_of_indices;       //nombre d'indices
	int						*indices;                //la listes des indices apres triangulasisation
	struct s_mypolygon		*next;                   //le prochain noeud dans la liste
}							t_mypolygon;

struct	s_poly //polygon
{
	t_vec		*ver_list;  //TAB
	t_vec			*ver_tmp; //@ LOIC
	t_vec		normal;
	int			nb_ver; //points du polygone
	int			nb_indices; 
	int			*indices; //liste de coordonnées des triangles qui forment le polygone
	t_poly		*next;
	char		was_splitter;
	int			texture;
};//				t_poly; **/

t_poly *load_obj(t_mypolygon *in)
{
	t_poly *out;
	t_poly *new;
	t_myvec *tmp;
	int i;

	out = NULL;
	while (in != NULL)
	{
		if (!(new = (t_poly*)malloc(sizeof(t_poly))))
			exit(0);
		//printf("TEST %d\n", in->number_of_vertex);
		if (!(new->ver_list = (t_vec*)malloc(sizeof(t_vec) * in->number_of_vertex)))
			exit(0);
		new->nb_ver = in->number_of_vertex;
		new->nb_indices = in->number_of_indices;
		i = 0;
		tmp = in->vertex_lst;
		while (i < new->nb_ver)
		{
			new->ver_list[i].x = tmp->x;
			new->ver_list[i].y = tmp->y;
			new->ver_list[i].z = tmp->z;
			new->ver_list[i].tx = tmp->u;
			new->ver_list[i].ty = tmp->v;
			new->ver_list[i].tz = tmp->w;
			tmp = tmp->next;
			i++;
		}
		i = 0;
		printf("TEST %d\n", new->nb_indices);
		if (!(new->indices = (int*)malloc(sizeof(int) * in->number_of_indices))) //MALLOC INDICES
			exit(0);
		while (i < new->nb_indices)
		{
			new->indices[i] = in->indices[i];
			i++;
		}
		new->normal.x = in->normal.x;
		new->normal.y = in->normal.y;
		new->normal.z = in->normal.z;
		new->was_splitter = 0;
		in = in->next;
		new->next = out;
		out = new;
	}
	return (out);
}

/**
struct	s_vec //vector
{
	float	x;
	float	y;
	float	z;
	//int tx;
	//int ty
	float		tx;
	float		ty;
	float 		tz;
};//				t_vec;


typedef struct		s_myvec
{
	float			x;
	float			y;
	float			z;
	float			w;
	float			u;  //pour texture x
	float			v;  //pour texture y
	int				obj_indice;
	int				obj_indice_texture;
	float			shade;
	struct s_myvec	*next;
}					t_myvec; **/