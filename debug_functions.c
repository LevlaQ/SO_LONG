
#include "so_long.h"

/*
	Debug fonksiyonu
*/
void	print_the_map(t_map **st)
{
	int x = 0;
	int y = 0;

	while((*st)->map_copy[y] != NULL)
	{
		x = 0;
		while((*st)->map_copy[y][x] != '\0')
		{
			printf("%c", (*st)->map_copy[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}


/*
	Debug fonksiyonu
*/
void	print_the_ori_map(t_map **st)
{
	int x = 0;
	int y = 0;

	while((*st)->map[y] != NULL)
	{
		x = 0;
		while((*st)->map[y][x] != '\0')
		{
			printf("%c", (*st)->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}