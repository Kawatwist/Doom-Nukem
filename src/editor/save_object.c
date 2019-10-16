#include <doom.h>
#include <editor.h>

static int  *ft_storepoint(int i, int j, int k, int l)
{
    int *ret;

    ret = malloc(sizeof(int) * 4); // NEED SECURE
    ret[0] = i;
    ret[1] = j;
    ret[2] = k;
    ret[3] = l;
    return (ret);
}

static void ft_putface_fd(int *f, int *t, int len,int fd)
{
    int n;

    n = 0;
    ft_putstr_fd("f ", fd);
    while (n < len)
    {
        ft_putnbr_fd(f[n], fd);
        ft_putchar_fd('/', fd);
        ft_putnbr_fd(t[n], fd);
        if (n < len-1)
            ft_putchar_fd(' ', fd);
        n++;
    }
    free(f);
    free(t);
    ft_putchar_fd('\n', fd);
}

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
        ft_putstr_fd("/1", fd);
        if (i < nb1)
            ft_putchar_fd(' ', fd);
        i++;
    }
    i--;
    // CREATE REVERSE
    ft_putstr_fd("\nf ", fd);
    while (i > 0) // ATTENTION SI NB1 != NB2
    {
        ft_putnbr_fd(i + currnb, fd);
        ft_putstr_fd("/1", fd);
        if (i > 1)
            ft_putchar_fd(' ', fd);
        i--;
    }
    i = nb1 + 1;
    ft_putstr_fd("\nf ", fd);
    while (i < (nb2 + nb1) + 1)
    {
        ft_putnbr_fd(i + currnb, fd);
        ft_putstr_fd("/1", fd);
        if (i < nb2 + nb1)
            ft_putchar_fd(' ', fd);
        i++;
    }
    i--;
    //CREATE REVERSE
    ft_putstr_fd("\nf ", fd);
    while (i > nb1) // ATTENTION SI NB1 != NB2
    {
        ft_putnbr_fd(i + currnb, fd);
        ft_putstr_fd("/1", fd);
        if (i > nb1 + 1)
            ft_putchar_fd(' ', fd);
        i--;
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
        ft_putstr_fd("/1 ", fd);
        ft_putnbr_fd(i + 1 + currnb, fd);
        ft_putstr_fd("/1 ", fd);
        ft_putnbr_fd(nb1 + i + 1 + currnb, fd);
        ft_putstr_fd("/1 ", fd);
        ft_putnbr_fd(nb1 + i + currnb, fd);
        ft_putstr_fd("/1\n", fd);

        // CREATE REVERSE
        ft_putstr_fd("f ", fd);
        ft_putnbr_fd(nb1 + i + currnb, fd);
        ft_putstr_fd("/1 ", fd);
        ft_putnbr_fd(nb1 + i + currnb + 1, fd);
        ft_putstr_fd("/1 ", fd);
        ft_putnbr_fd(i + 1 + currnb, fd);
        ft_putstr_fd("/1 ", fd);
        ft_putnbr_fd(i + currnb, fd);
        ft_putstr_fd("/1\n", fd);
        i++;
    }
    ft_putstr_fd("f ", fd);
    ft_putnbr_fd(currnb + 1, fd);
    ft_putstr_fd("/1 ", fd);
    ft_putnbr_fd(nb1 + currnb, fd);
    ft_putstr_fd("/1 ", fd);
    ft_putnbr_fd(nb2 + nb1 + currnb, fd);
    ft_putstr_fd("/1 ", fd);
    ft_putnbr_fd(nb1 + 1 + currnb, fd);
    ft_putstr_fd("/1\n", fd);

    // CREATE REVERSE

    ft_putstr_fd("f ", fd);
    ft_putnbr_fd(currnb + 1 + nb1, fd);
    ft_putstr_fd("/1 ", fd);
    ft_putnbr_fd(nb1 + currnb + nb2, fd);
    ft_putstr_fd("/1 ", fd);
    ft_putnbr_fd(nb1 + currnb, fd);
    ft_putstr_fd("/1 ", fd);
    ft_putnbr_fd(1 + currnb, fd);
    ft_putstr_fd("/1\n", fd);
}

static void close_map(Uint32 nb, Uint32 nbvt, int fd)
{
    ft_putstr_fd("g Skybox\n", fd);
    ft_putstr_fd("mtllib master.mtl\n", fd);
    ft_putstr_fd("usemtl blue\n", fd);
    ft_putstr_fd("v 0.0 0.0 60.0\nv 60.0 0.0 60.0\nv 60.0 0.0 0.0\nv 0.0 0.0 0.0\nv 0.0 60.0 60.0\nv 60.0 60.0 60.0\nv 60.0 60.0 0.0\nv 0.0 60.0 0.0\n", fd);
    ft_putstr_fd("vt 0.0 0.0\nvt 512.0 0.0\nvt 1024.0 0.0\nvt 1536.0 0.0\n", fd);
    ft_putstr_fd("vt 0.0 512.0\nvt 512.0 512.0\nvt 1024.0 512.0\nvt 1536.0 512.0\n", fd);
    ft_putstr_fd("vt 0.0 1022.0\nvt 512.0 1022.0\nvt 1024.0 1022.0\nvt 1536.0 1022.0\n", fd);
    ft_putface_fd(ft_storepoint(nb + 1, nb + 2, nb + 3, nb + 4), ft_storepoint( nbvt + 1, nbvt + 2, nbvt + 6, nbvt + 5), 4, fd);
    ft_putface_fd(ft_storepoint(nb + 2, nb + 6, nb + 7, nb + 3), ft_storepoint( nbvt + 2, nbvt + 3, nbvt + 7, nbvt + 6), 4, fd);
    ft_putface_fd(ft_storepoint(nb + 6, nb + 5, nb + 8, nb + 7), ft_storepoint( nbvt + 3, nbvt + 4, nbvt + 8, nbvt + 7), 4, fd);
    ft_putface_fd(ft_storepoint(nb + 5, nb + 1, nb + 4, nb + 8), ft_storepoint( nbvt + 6, nbvt + 5, nbvt + 10, nbvt + 9), 4, fd);
    ft_putface_fd(ft_storepoint(nb + 6, nb + 2, nb + 1, nb + 5), ft_storepoint( nbvt + 7, nbvt + 6, nbvt + 11, nbvt + 10), 4, fd);
    ft_putface_fd(ft_storepoint(nb + 4, nb + 3, nb + 7, nb + 8), ft_storepoint( nbvt + 8, nbvt + 9, nbvt + 12, nbvt + 11), 4, fd);
}

static void fill_file(t_edit *edit, int fd)
{
    t_elem  *curr_elem;
    Uint32  nb;
    Uint32  nb_ver1;
    Uint32  nb_ver2;
    Uint32  currnb;
    Uint32  currvt;

    curr_elem = edit->elem;
    nb = 1;
    currnb = 0;
    currvt = 0;
    while (curr_elem != NULL && curr_elem->point != NULL && curr_elem->point->next != NULL)
    {
        ft_putstr_fd("g Polygon.", fd);
        // ft_putnbr_fd(nb, fd);
        // ft_putchar_fd('\n', fd);
        nb_ver1 = store_vertice(curr_elem, fd);
        nb_ver2 = store_vertice(curr_elem->next, fd);
        // ft_putstr_fd("vt 1.0 1.0 1.0\n", fd);
        ft_putstr_fd("s off\n", fd);
        create_basic_face(nb_ver1, nb_ver2, fd, currnb);
        create_face(nb_ver1, nb_ver2, fd, currnb);
        curr_elem = curr_elem->next->next;
        currnb += nb_ver1 + nb_ver2;
        nb++;
    }
    close_map(currnb, currvt, fd);
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
        ft_putchar_fd('#', fd);
        ft_putstr_fd(name, fd);
        ft_putchar_fd('\n', fd);
        fill_file(edit, fd);
    }
    else
        ft_putstr("File's creation failed\n");
}

void        save_panel(t_win *wn, t_edit *edit)
{
   static char *map_name = NULL;
   static int   prompt = 0;
   SDL_Rect    position;
   SDL_Rect     mouse;
   
   position = define_rect(((t_edit *)wn->edit)->tab->bg.x + ((t_edit*)wn->edit)->tab->bg.w - 100, ((t_edit*)wn->edit)->tab->bg.y + 200, 50, ((t_edit*)wn->edit)->tab->bg.h);
   map_name = text_box_prompt(wn, map_name, &prompt); /// Prompt mis en place mais pas d'affichage
   if (map_name != NULL && map_name[0] != '\0')
       ((t_edit *)wn->edit)->map->name = map_name;
   else
        ((t_edit *)wn->edit)->map->name = "Untitled(1)";
   mouse.x = wn->input->x;
    mouse.y = wn->input->y;
   if (edit->elem != NULL && map_name != NULL && boxhitbox(wn->rend, &mouse, &position, 1) && mouse_pressed(wn, SDL_BUTTON_LEFT))
   {
       map_name = ft_strjoinfree(map_name, ".obj", 1);
       create_obj(edit, map_name);
       printf("Map save will be called %s\n", map_name);
   }
}