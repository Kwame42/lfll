/*
**    objectivemoon.io locked free linked list
**    Copyright (C) 2014 Kwame
**
**    This program is free software: you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation, either version 3 of the License, or
**    (at your option) any later version.
**
**    This program is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <string.h>

/*
**
*/
#include "lfll.h"

/*
**
*/
int			gl_count;

typedef struct		s_data {
  char			*name;
  int			nbr;
}			t_data;

void			data_print(void *data)
{
  printf("(data (%p):(%d))", (t_data *)data, ((t_data *)data)->nbr);
}

void			*data_init(void)
{
  t_data		*data;

  data=malloc(sizeof(*data));
  memset(data, 0, sizeof(*data));
  data->nbr=gl_count++;
  
  return data;
}
  
void			data_destroy(void *val)
{
  t_data		*data;

  data=val;
  data_print(data);
  printf("\n");
  gl_count--;
  free(data);
}

/*
**
*/
int			main(int ac, char **av)
{
  lfll_t		*list;
  int			list_size;

  list_size=1000;
  gl_count=0;
  //Initialising a lfll of list_size cell and 10 aux 
  list=lfll_init_size(list_size, data_init);
  // Printing the list (with debug info)
  lfll_print_list(list, data_print);
  // moving somewhere int he list
  
  
  //Destroying list
  lfll_destroy_list(list, data_destroy);
  exit (0);
}
