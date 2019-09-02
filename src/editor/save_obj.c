#include <doom.h>
#include <editor.h>

// static t_point  *find_before(t_elem *elem, t_point *tofind)
// {
//     t_point *curr;
    
//     curr = elem->point;
//     while (curr != NULL && curr != tofind && curr->next != tofind)
//         curr = curr->next;
//     return (curr == tofind ? NULL : curr);
// }

// static int  store_reverse_vertice(t_elem *elem, int fd)
// {
//     int     nb_ver;
//     t_point *curr;
    
//     nb_ver = 0;
//     curr = elem->point;
//     while (curr->next != NULL)
//         curr = curr->next;
//     while (curr != NULL)
//     {
//         ft_putstr_fd("v ", fd);
//         ft_ftoafd(curr->x, fd); // NEED TO CHECK THIS FUNCTION
//         ft_putchar_fd(' ', fd);
//         ft_ftoafd(curr->y, fd); // NEED TO CHECK THIS FUNCTION
//         ft_putchar_fd(' ', fd);
//         ft_ftoafd(curr->z, fd); // NEED TO CHECK THIS FUNCTION
//         ft_putchar_fd('\n', fd);
//         nb_ver += 1;
//         if (curr == elem->next->point)
//             break;
//         curr = find_before(elem, curr);
//     }
//     return (nb_ver);
// }

static int  store_vertice(t_elem *elem, int fd)
{
    int     nb_ver;
    t_point *curr;
    
    nb_ver = 0;
    curr = elem->point;
    while (curr != NULL)
    {
        ft_putstr_fd("v ", fd);
        ft_ftoafd(curr->x, fd); // NEED TO CHECK THIS FUNCTION
        ft_putchar_fd(' ', fd);
        ft_ftoafd(curr->y, fd); // NEED TO CHECK THIS FUNCTION
        ft_putchar_fd(' ', fd);
        ft_ftoafd(curr->z, fd); // NEED TO CHECK THIS FUNCTION
        ft_putchar_fd('\n', fd);
        nb_ver += 1;
        curr = curr->next;
    }
    return (nb_ver);
}

static void create_basic_face(Uint32 nb1, Uint32 nb2, int fd, Uint32 currnb)
{
    Uint32 i;
    
    i = 1;
    ft_putstr_fd("f ", fd);
    while (i < (nb1 + 1)) // ATTENTION SI NB1 != NB2
    {
        ft_putnbr_fd(i + currnb, fd);
        ft_putchar_fd(' ', fd);
        i++;
    }
    ft_putstr_fd("\nf ", fd);
    while (i < (nb2 + nb1) + 1)
    {
        ft_putnbr_fd(i + currnb, fd);
        ft_putchar_fd(' ', fd);
        i++;
    }
    ft_putchar_fd('\n', fd);
}

static void create_face(Uint32 nb1, Uint32 nb2, int fd, Uint32 currnb)
{
    Uint32 i;
    
    (void)nb2;
    i = 1;
    while (i < (nb1)) // ATTENTION SI NB1 != NB2
    {
        ft_putstr_fd("f ", fd);
        ft_putnbr_fd(i + currnb, fd);
        ft_putchar_fd(' ', fd);
        ft_putnbr_fd(i + 1 + currnb, fd);
        ft_putchar_fd(' ', fd);
        ft_putnbr_fd(nb1 + i + 1 + currnb, fd);
        ft_putchar_fd(' ', fd);
        ft_putnbr_fd(nb1 + i + currnb, fd);
        ft_putchar_fd('\n', fd);
        i++;
    }
    ft_putstr_fd("f ", fd);
    ft_putnbr_fd(currnb + 1, fd);
    ft_putchar_fd(' ', fd);
    ft_putnbr_fd(nb1 + currnb, fd);
    ft_putchar_fd(' ', fd);
    ft_putnbr_fd(nb2 + nb1 + currnb, fd);
    ft_putchar_fd(' ', fd);
    ft_putnbr_fd(nb1 + 1 + currnb, fd);
    ft_putchar_fd('\n', fd);
}

static void fill_file(t_edit *edit, int fd)
{
    t_elem  *curr_elem;
    Uint32  nb;
    Uint32  nb_ver1;
    Uint32  nb_ver2;
    Uint32  currnb;

    curr_elem = edit->elem;
    nb = 1;
    currnb = 0;
    while (curr_elem != NULL && curr_elem->point != NULL && curr_elem->point->next != NULL)
    {
        ft_putstr_fd("o Polygon.", fd);
        ft_putnbr_fd(nb, fd);
        ft_putchar_fd('\n', fd);
        nb_ver1 = store_vertice(curr_elem, fd);
        nb_ver2 = store_vertice(curr_elem->next, fd);
        create_basic_face(nb_ver1, nb_ver2, fd, currnb);
        create_face(nb_ver1, nb_ver2, fd, currnb);
        ft_putstr_fd("s off\n", fd);
        curr_elem = curr_elem->next->next;
        currnb += nb_ver1 + nb_ver2;
        nb++;
    }
    ft_putstr_fd("# ", fd); // DONT NEED THIS BUT COULD BE USEFUL
    ft_putnbr_fd(nb - 1, fd);
    ft_putstr_fd(" elements", fd);
}

static void create_obj(t_edit *edit, char *name)
{
   int fd;

   fd = 0;
    if ((fd = creat(name, S_IRWXU | S_IRWXG | S_IRWXO)) != -1)
    {
        ft_putstr_fd(name, fd);
        ft_putchar_fd('\n', fd);
        fill_file(edit, fd);
    }
    else
        ft_putstr("File's creation failed\n");
}

void        save_panel(t_win *wn, t_edit *edit)
{
    (void)wn;
   static char *map_name = NULL;
   SDL_Rect    position;
   position = define_rect(((t_edit *)wn->edit)->tab->bg.x + ((t_edit*)wn->edit)->tab->bg.w - 100, ((t_edit*)wn->edit)->tab->bg.y + 200, 50, ((t_edit*)wn->edit)->tab->bg.h);
   SDL_Rect	check = define_rect(wn->input->x, wn->input->y, 0, 0);
   map_name = text_box(wn, map_name);
   if (edit->elem != NULL && map_name != NULL && boxhitbox(wn->rend, &check, &position, 1) && mouse_pressed(wn, SDL_BUTTON_LEFT))
   {
       map_name = ft_strjoinfree(map_name, ".obj", 1);
       create_obj(edit, map_name);
       printf("Map save will be called %s\n", map_name);
   }
}