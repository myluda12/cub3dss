/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajrhou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 21:57:55 by ayajrhou          #+#    #+#             */
/*   Updated: 2019/10/31 22:14:02 by ayajrhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>


void *mlx_ptr;
void *win_ptr;

//design morba3 (map 2D)
char **line;
int y_len;
int x;
int y;
int k = 0;
int remaind = 50;
int none = 1;
//wall
int wall = 50;

int swiitch = 1;
// Player movement
int X_player;
int Y_player;   
int radian = 3;
float rotationAngle = - (M_PI / 2);
float rotationSpeed = 3;
int len_angle = 30;
float turnDirection = 0;
int walkDirection = 0;
int j;
float rotation;

float rot;
//DATA COLLECTION FOR IMAGE 
int g_a;
int g_b;
int g_c;
int *g_data;
void *g_image;


//int k = 0;
//Remainding the old position of X && Y Player
int Y_remainder;
int X_remainder;
//Ray Intersaction && steps
 float xintercept;
 float yintercept;

 float ystep;
 float xstep;

 float nextHoriX;
 float nextHoriY;
 //check if wall is hited
 float wallHoriHit;
 float wallVertHit;
 float HorizwallHitX;
 float HorizwallHitY;
 float VertwallHitX;
 float VertwallHitY;
 
 //delete
 int pc = 0;

 float WallHitX;
 float WallHitY;
// Ray Direction 
int rayFacingDown;
int rayFacingUp;
int rayFacingRight;
int rayFacingLeft;

// Distance between Vertical && Horizontal
float HorzHitDistance;
float VertHitDistance;
float distance;
float wasHitVertical;
//COLOR RENDERING
int alpha;
//key UP / DOWN
int up;
int down;
int left;
int right;
//Rendering 3D MAP
float correctWallDistance;
float distanceProjectionPlan;
float wallStripHeight;
float WallStripWidth = 1;
//color
unsigned int DarkColor;
//bullshit variables for data (LEARN LATER)
int tab[20];
void *img1;
void *img2;
void *img3;
void *img4;
unsigned int *textu0;
unsigned int *textu1;
unsigned int *textu2;
unsigned int *textu3;
float xOfsset;
float yOffset;
int g_mhah;
float g_pourcent;
int copystart;
int g_rightleftupdown;
//The Raycasting variables
//indicateur pour le stockage
int g_f;
//float isRaydown = ;
int calculparam_x = 50 / 2;
int calculparam_y = 50 / 2;
    int sprite;
int distance_center;



typedef struct s_mhah
{
    int x;
    int y;
    int distance;
    struct s_mhah *next;
}               t_mhah;

t_mhah *myah;
t_mhah *myih;


t_mhah		*ft_lstnew(int x, int y,int distance)
{
	t_mhah	*list;

	list = malloc(sizeof(t_mhah));
	if (list)
	{
		list->x = x;
		list->y = y;
        list->distance = distance;
		list->next = NULL;
		return (list);
	}
	return (NULL);
}


t_mhah		*ft_lstlast(t_mhah *lst)
{
	t_mhah	*loop;

	loop = lst;
	if (loop)
		while (loop->next)
			loop = loop->next;
	return (loop);
}

void		ft_lstadd_back(t_mhah **alst, t_mhah *new)
{
	t_mhah	*temp;

	if (alst && *alst && new)
	{
		temp = ft_lstlast(*alst);
		temp->next = new;
		new->next = NULL;
	}
	else if (!*alst)
	{
		*alst = new;
		new->next = NULL;
	}
}

int     design_morba3(int i, unsigned int color, char **line, int j)
{
    int save;
    int y_copy;
    int center_x;
    int center_y;

    y_copy = y;
    save = k;

   // i = i + 1;

    while (k < x)
    {
        if(swiitch == 0)
            mlx_pixel_put(mlx_ptr, win_ptr, k, y, color);
        if (line[j][i] == '2')
        {
            center_x = calculparam_x + save;
            center_y = y_copy - calculparam_y;
            if (center_x == k && center_y == y)
            {
                if(swiitch == 0)
                    mlx_pixel_put(mlx_ptr, win_ptr, k, y, 0xff8833);
                distance_center = sqrtf(powf(Y_player - y,2) + powf(X_player - k,2));
            }
        }
        k++;
        if (k == x)
        {
            k = save;
            y = y - 1;
            if (y == remaind - wall - 1)
            {
                k += wall;
                break;
                }
            }
    }

    if (line[j][i] == 'N' && none == 1)
    {
        if (swiitch == 1)
            mlx_pixel_put(mlx_ptr, win_ptr, k, y, 0x000000);
        X_player = k;
        Y_player = y;
        none++;
    }
    y = y_copy;
    x = x + wall;
    return k;
}

void ft_morba3(char **line)
{
    int i;
    unsigned int color;

   
    i = 0;
    j = 0;
    while(line[j][i])
    {
        if (line[j][i] == '1')
        {
            color = 0x6f665d;
            design_morba3(i, color, line, j);
        }
        else if(line[j][i] == '0' || line[j][i] == 'N')
        {
            color = 0xFFFFFF;
            design_morba3(i, color, line, j);
        }
        else if(line[j][i] == '2')
        {
            color = 0xdcd3f6;
            design_morba3(i, color, line, j);
        }
        i++;
        if (line[j][i] == '\0')
        {
            i = 0;
            if (line[j + 1] != NULL)
            {
                j++;
                y = y + wall;
                x = wall;
                remaind = remaind + wall;
                k = 0;
            }
            else
                break;
        }    
    }
}





int abs (int n)
{ 
    return ( (n>0) ? n : ( n * (-1))); 
}

unsigned int    *ft_texture(char     *file, unsigned int *texture)
{
    int c = 63;
    int i= 0;
    img1 = mlx_xpm_file_to_image(mlx_ptr,file,&tab[g_f],&tab[g_f + 1]);
    texture= (unsigned int *)mlx_get_data_addr(img1,&tab[g_f + 2],&tab[g_f + 3], &tab[g_f + 4]);
    g_f = g_f + 5;
    return texture;
}

void     text(void)
{
    g_f = 0;
    textu0 = ft_texture("shanks.xpm", textu0);
    textu1 = ft_texture("ayoub.xpm", textu1);
    textu2 = ft_texture("hani.xpm", textu2);
    textu3 = ft_texture("maroc.xpm", textu3);
}

//DDA Function for line generation 
void DDA(int X0, int Y0, int X1, int Y1) 
{ 
    // calculate dx & dy 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
  
    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    // calculate increment in x & y for each steps 
    float Xinc = dx / (float) steps; 
    float Yinc = dy / (float) steps; 
  
    // Put pixel for each step 
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) 
    { 
       
        if(X >= 0 && X <= 650 && Y >= 0 && Y <= 300)
        {
            if(swiitch == 0)
           mlx_pixel_put(mlx_ptr, win_ptr, X, Y, 0xFF0000);
        }
        X += Xinc;           // increment in x at each step 
        Y += Yinc;           // increment in y at each step 
         // for visualization of line- 
                             // generation step by step 
    } 
} 
//FUNCTION TO COVERT HEXA TO RGB
unsigned int    convert_rgb(int r, int g, int b)
{
    unsigned int color;
    color = r;
    color = (color << 8) + g;
    color = (color << 8) + b;
    return (color);
} 
unsigned int    check_opacity(unsigned int hexcolor)
{
    double red;
    double green;
    double blue;
    float oppasity;

    oppasity = (distance / 822) > 1 ? 1 : 1 - (distance / 822) ;
    red = ((hexcolor >> 16) & 255) * oppasity;
    green = ((hexcolor >> 8) & 255) * oppasity;
    blue = (hexcolor & 255) * oppasity;
    return (convert_rgb(red, green, blue));
}

int wall_checker()
{
    int X_pos;
    int Y_pos;

    X_pos = nextHoriX / wall;
    Y_pos = nextHoriY / wall;
    //printf("\n|==>|'%c'||\n",line[Y_pos][X_pos]);
    if ((X_pos >= 0 &&  X_pos < 13) && (Y_pos >= 0 &&  Y_pos < 6))
    {
        if (line[Y_pos][X_pos] == '2')
            sprite = 1;
        if (line[Y_pos][X_pos] == '1' || line[Y_pos][X_pos] == '2')
            return (1);
        
    }
    return 0;

}
 int wall_collision()
{
    int X_pos;
    int Y_pos;

    X_pos = X_remainder / wall;
    Y_pos = Y_remainder / wall;
   // printf("\n|==>|'%c'||\n",line[Y_pos][X_pos]);
    if (line[Y_pos][X_pos] == '1' || line[Y_pos][X_pos] == '2')
    {
        return (1);
    }
    return 0;

}

float ft_normalize_angle(float angle)
{
    while (angle > 2 * M_PI)
        angle -= 2 * M_PI;
    if (angle < 0)
    {
        angle += (2 * M_PI);
    }
    return (angle);
}

void ft_nizar_calcul()
{
     if(g_mhah)
    {
        if (rayFacingDown)
        {
           g_rightleftupdown = 1;
        }
        else if (rayFacingUp)
        {
          g_rightleftupdown = 2;
        }
    }
    else if(!g_mhah)
    {
        if (rayFacingLeft)
        {
           g_rightleftupdown = 3;
        }
        else if (rayFacingRight)
        {
           g_rightleftupdown = 4;
        }
    }
}
void render_column1(int i)
{
        int start;
    int j;
    int p = 0;
    j = 0;
    start = (1000 / 2) - (wallStripHeight / 2);
    //if (start < 0)
       // start = 0;
    // modification is here
    
    while(j < start)
    {
        g_data[1000 * j + i] = 0x00FFFF;//+ pc;
         j++;
    }
    while(j < start + wallStripHeight && j < 1000)
    {
        g_pourcent = (j - start) / wallStripHeight;
            yOffset = 50 * g_pourcent;
         
            g_data[1000 * j + i] = 0;
               

            if(swiitch == 0)
                mlx_pixel_put(mlx_ptr,win_ptr,i,j,0x006400);
        j++;
    }
    while(j < 1000)
    {
         g_data[1000 * j + i] = 0x808080;// + pc;
         j++;
    }
pc++;

}
void render_colomn(int i)
{
    int start;
    int j;
    int p = 0;
    j = 0;
    start = (1000 / 2) - (wallStripHeight / 2);
    //if (start < 0)
       // start = 0;
    // modification is here
    
    while(j < start)
    {
        g_data[1000 * j + i] = 0x00FFFF;//+ pc;
         j++;
    }
    while(j < start + wallStripHeight && j < 1000)
    {
        g_pourcent = (j - start) / wallStripHeight;
            yOffset = 50 * g_pourcent;
            if(g_rightleftupdown == 1)
            {
                g_data[1000 * j + i] = check_opacity(textu0[(int)yOffset * 50 + (int)xOfsset]);
                //printf("1\n");
            }
            else if(g_rightleftupdown == 2)
            {
                g_data[1000 * j + i] = check_opacity(textu1[(int)yOffset * 50 + (int)xOfsset]);
                //printf("2\n");
            }
            else if(g_rightleftupdown == 3)
            {
                g_data[1000 * j + i] = check_opacity(textu2[(int)yOffset * 50 + (int)xOfsset]);
                //printf("3\n");
            }
            else if(g_rightleftupdown == 4)
            {
                g_data[1000 * j + i] = check_opacity(textu3[(int)yOffset * 50 + (int)xOfsset]);
               // printf("4\n");
            }
            else if(sprite == 1)
            {
                g_data[1000 * j + i] = 0;

            }

            if(swiitch == 0)
                mlx_pixel_put(mlx_ptr,win_ptr,i,j,0x006400);
        j++;
    }
    while(j < 1000)
    {
         g_data[1000 * j + i] = 0x808080;// + pc;
         j++;
    }
pc++;
}
void render_map3D(int i)
{
    correctWallDistance = distance * cos(rotation - rotationAngle);
   // alpha = 80 / correctWallDistance;
    distanceProjectionPlan = (1000 / 2) / tan(rad(45) / 2); //here delete cos
    wallStripHeight = (50 / correctWallDistance) * distanceProjectionPlan;
    xOfsset = g_mhah == 1 ? fmod(WallHitX,50) : fmod(WallHitY,50);
           ft_nizar_calcul();
        //Modification here 2  
        if(swiitch == 1)
            render_colomn(i);
}
int ray_Direction()
{
    rayFacingDown = 0;
    rayFacingUp = 0;
    rayFacingRight = 0;
    rayFacingLeft = 0;

    rayFacingDown = (deg(rotation) > 0 && deg(rotation) < 180) ? 1 : 0;
    rayFacingUp = !(rayFacingDown) ? 1 : 0;

    rayFacingRight = ((deg(rotation) > 0 && (deg(rotation) < 90)) || (deg(rotation) > 270 && (deg(rotation) < 360))) ? 1 : 0;
    rayFacingLeft = !(rayFacingRight) ? 1 : 0;
    // printf("%d\n",rayFacingUp);
     //printf("%f\n",deg(rotation));
     return 0;

}
float Distance_between_HorVer(int x1,int y1, int x2, int y2)
{
    return sqrtf(powf((x2 - x1),2) + powf((y2 - y1),2));
}

int ft_cast_ray(int index)
{
    WallHitX = 0;
    WallHitY = 0;
    distance = 0;
    sprite = 0;
    int i = 0;
    int check;
    wallHoriHit = 0;
    ray_Direction();

    yintercept = (int)(Y_player / wall) * wall;
    yintercept += rayFacingDown ? wall : 0;
    xintercept = X_player + (yintercept - Y_player) / tan(rotation);

    ystep = wall;
    ystep *= rayFacingUp ? -1 : 1;

    // ==> 
    xstep = ystep / tan(rotation);
    // ==>
    //xstep *= (rayFacingLeft && xstep > 0) ? -1 : 1;
    //xstep *= (rayFacingRight && xstep < 0) ? -1 : 1;

    nextHoriX = xintercept;
    nextHoriY = yintercept;

    if(rayFacingUp)
        nextHoriY--;
        //increment x & y step until we find  a wall
    while(nextHoriX >= 0 && nextHoriX < 650 && nextHoriY >= 0 && nextHoriY < 300)
    {
        check = wall_checker();
        if (check == 1)
        {
            wallHoriHit = 1;
            HorizwallHitX = nextHoriX;
            HorizwallHitY = nextHoriY;
            //DDA(X_player, Y_player,  HorizwallHitX, HorizwallHitY);
            break;
        }
        else
        {
            nextHoriX += xstep;
            nextHoriY += ystep; 
        }
        
    }
    // VERITICAL RAYCAST

    wallVertHit = 0;
    ray_Direction();
    xintercept = (int)(X_player / wall) * wall;
    xintercept += rayFacingRight ? wall : 0;
    yintercept = Y_player - (X_player - xintercept) * tan(rotation);

    xstep = wall;
    xstep *= rayFacingLeft ? -1 : 1;
    // ==>
    ystep = xstep * tan(rotation);
    // == <
    //ystep *= (rayFacingUp && ystep > 0) ? -1 : 1;
    //ystep *= (rayFacingDown && ystep < 0) ? -1 : 1;

    nextHoriX = xintercept;
    nextHoriY = yintercept;

    if(rayFacingLeft)
        nextHoriX--;

    while(nextHoriX >= 0 && nextHoriX < 650 && nextHoriY >= 0 && nextHoriY < 300)
    {
        check = wall_checker();
        if (check == 1)
        {
            wallVertHit = 1;
            VertwallHitX = nextHoriX;
            VertwallHitY = nextHoriY;
          //  DDA(X_player, Y_player,  HorizwallHitX, HorizwallHitY);
            break;
        }
        else
        {
            nextHoriX += xstep;
            nextHoriY += ystep; 
        }
    }

    // The Distance between vert and horizontal distances and precist the smallest value

    HorzHitDistance = (wallHoriHit) ? Distance_between_HorVer(X_player , Y_player, HorizwallHitX,HorizwallHitY) : MAX_INT;
    VertHitDistance = (wallVertHit) ? Distance_between_HorVer(X_player , Y_player, VertwallHitX,VertwallHitY) : MAX_INT;
// store the smallest of the distances

    WallHitX = (HorzHitDistance) < (VertHitDistance) ? HorizwallHitX : VertwallHitX;
    WallHitY = (HorzHitDistance) < (VertHitDistance) ? HorizwallHitY : VertwallHitY;
    distance = (HorzHitDistance) < (VertHitDistance) ? HorzHitDistance : VertHitDistance;
    g_mhah = distance == HorzHitDistance ? 1 : 0;
    wasHitVertical = (VertHitDistance) < (HorzHitDistance);
    
   // printf("%f\n",distance);
    DarkColor = 0x006400;
    DarkColor = check_opacity(DarkColor);

  
    DDA(X_player,Y_player,WallHitX,WallHitY);
    //printf("%d",sprite);
      if (sprite == 1)
    {
        ft_lstadd_back(&myah, ft_lstnew(WallHitX, WallHitY,distance_center));
       // printf("x ==> |%d\n| y ==> |%d\n| distance ==> |%d\n| ",myah->x,myah->y,myah->distance);
       // printf("x");
       // write(1,"x",1);
        //printf("x = %d| y = %d|", myah->x, myah->y);
    }
   
    // while(myah)
    // {
       
    // }
   // g_rays[index] = (rayFacingRight) ? 1 : 2;
    //g_rays[index] *= (rayFacingDown) ? 1 : -1;
   // g_rays_hit[index] = (wallHoriHit) ? 1 : 0;
   return 0;
}

int mlx_key_press(int key)
{
    if(key == 123)
        left = 1;
    if (key == 124)
        right = 1;
    if (key == 125)
        down = 1;
    if (key == 126)
        up = 1;
    return 0;
}
int key_release(int key)
{
    if(key == 123)
        left = 0;
    if(key == 124)
        right = 0;
    if (key == 125)
        down = 0;
    if (key == 126)
        up = 0;
    return 0;
}
void render_sprite(int i)
{
    correctWallDistance = distance * cos(rotation - rotationAngle);
    
   // alpha = 80 / correctWallDistance;
    distanceProjectionPlan = (1000 / 2) / tan(rad(45) / 2); //here delete cos
    wallStripHeight = (50 / correctWallDistance) * distanceProjectionPlan;
    xOfsset = g_mhah == 1 ? fmod(WallHitX,50) : fmod(WallHitY,50);
    ft_nizar_calcul();
        //Modification here 2
        //printf("d\n");  
        if(swiitch == 1)
        {
            //printf("s\n");+
            render_column1(i);
        }
}
int deal_key(void)
{
    int p = 0;
    x = wall;
    y = wall;
    k = 0;
    int i = 0;
    int j = 0;
    int ray_lenght;
    remaind = wall;
    ft_morba3(line);
    //mlx_clear_window(mlx_ptr,win_ptr);
    rotation = rotationAngle - M_PI / 8;
    rot = rad(45) / 1000;

    if (rotationAngle > 2 * M_PI || rotationAngle < 0)
            rotationAngle = ft_normalize_angle(rotationAngle);
   // printf("rotationAngle :|%f|\n",deg(rotationAngle));
   myih = myah;
    while(i < 1000)
    {
        if (rotation > 2 * M_PI || rotation < 0)
            rotation = ft_normalize_angle(rotation);
        //DDA(X_player, Y_player,  wallHitX, wallHitY);
        ft_cast_ray(i);
        rotation += rot;
        // if(sprite == 0)
        render_map3D(i);
       // printf("%d",sprite);
        // if(sprite == 1)
        // {
        //     //printf("1\n");
        //     render_sprite(i);
        // } 
        i++;
      //  printf("Only Rotation |%f|\n",deg(rotation));
     //   printf("rotationAngle :|%f|\n",deg(rotationAngle));
    }

    //DDA(X_player, Y_player,  X_player  +  150  *  cos(rotationAngle - M_PI / 8) , Y_player +  150 * sin//(rotationAngle - M_PI / 8));
    if(down == 1)
    {
        X_remainder = X_player;
        Y_remainder = Y_player;
        X_remainder -= cos(rotationAngle) * 5;
        Y_remainder -= sin(rotationAngle) * 5;
        p = wall_collision();
        if (p != 1)
        {
            X_player -= cos(rotationAngle) * 5;
            Y_player -= sin(rotationAngle) * 5;
        }
        // printf("%f",deg(rotation));
    }
    if (up == 1)
    {
        X_remainder = X_player;
        Y_remainder = Y_player;
        X_remainder += cos(rotationAngle) * 5;
        Y_remainder += sin(rotationAngle) * 5;
         p = wall_collision();
        if (p != 1)
        {
            X_player += cos(rotationAngle) * 5;
            Y_player += sin(rotationAngle) * 5;
        }
    }
    if (left == 1)
    {
         rotationAngle -= rad(rotationSpeed);
    }
    if (right == 1)
    {
         rotationAngle += rad(rotationSpeed);
    }
    /*printf("x = |%d| \ny = |%d|",X_player,Y_player);
    printf("\n====> X_remainder : ||%d||\n",X_remainder);
    printf("\n====> Y_remainder : ||%d||\n",Y_remainder);
    //printf("%f\n",rotationAngle );*/
   // rotation = ft_normalize_angle(rotation);
    return 0;
}

int loop_key()
{

    /*textu1 = "ayoub.xpm";
    textu2 = "maroc.xpm";
    textu3 = "shanks.xpm"; */

    mlx_hook(win_ptr,2,0,mlx_key_press,0);
    mlx_hook(win_ptr,3,0,key_release,0);
    deal_key();
    // modification 3
    //mlx_clear_window(mlx_ptr,win_ptr);
    if(swiitch == 1)
        mlx_put_image_to_window(mlx_ptr,win_ptr,g_image,0,0);
    
    //ft_texture();
    return 0; 
}

char  **fd_tab(int fd)
{
    line = malloc(sizeof(char *) * 7);
    while(get_next_line(fd,&line[y_len]))
        y_len++;
    line[y_len + 1] = NULL;
    return (line);
}
int main()
{
    int i = 0;
    int j = 0;
    //printf("ayoub")
    x = wall;
    y = wall;
   // memset(g_rays, 0, 1000 * sizeof(int));
    //memset(g_rays_hit, 0, 1000 * sizeof(int));
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 1000, 1000,"mlx 42");
    g_image = mlx_new_image(mlx_ptr,1000,1000);
    g_data = (int *)mlx_get_data_addr(g_image,&g_b,&g_a,&g_c);
    int fd = open("map.txt", O_RDONLY);
    line = fd_tab(fd);
    ft_morba3(line);
    text();
    //return 0;
    rotation = rotationAngle - M_PI / 8;
    rot = rad(45) / 1000;
    while(i < 1000)
    {
        if (rotation > 2 * M_PI || rotation < 0)
            rotation = ft_normalize_angle(rotation);
       ft_cast_ray(i);
        rotation += rot;
        i++;

    } 
    mlx_loop_hook(mlx_ptr,loop_key,0);

   mlx_loop(mlx_ptr);
}