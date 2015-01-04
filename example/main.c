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
#include <pthread.h>
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
  data->nbr=gl_count;
  
  return data;
}
  
void			data_destroy(void *val)
{
  t_data		*data;

  data=val;
  free(data);
}

/*
**
*/
void			*list_read(void *recv_list)
{
  lfll_t		*list, *tmp;
  int			count;
#define NBR_READ	100000000
  
  list=(lfll_t *)recv_list;
  for (count=0 ; count < NBR_READ ; count++)
    for (tmp=list ; tmp->next ; tmp=tmp->next)
      ;
  printf("I just finish to READ %d that list\n", NBR_READ);
  
  return (NULL);
}

void			*list_add(void *recv_list)
{
  lfll_t		*list, *tmp;
  int			count;
#define NBR_ADD		10
  
  list=(lfll_t *)recv_list;
  for (count=0 ; count < NBR_ADD ; count++)
    {
      tmp=lfll_set_pos_to_cell_nbr(list, 20);
      printf("%p(%d)\n", tmp, tmp->index);
      lfll_add_cell(tmp, data_init);
      gl_count++;
    }
  printf("I just finish to ADD  %d cells from the list\n", NBR_ADD);

  return (NULL);
}

void			*list_rm(void *recv_list)
{
  lfll_t		*list, *tmp, *prev;
  int			count;
#define NBR_RM		1

  printf("--! \n");
  list=(lfll_t *)recv_list;
  for (count=0 ; count < NBR_RM ; )
    {
      //      if (gl_count > 100)
      //{
	  prev=lfll_set_pos_to_cell_nbr(list, 20);
	  tmp=lfll_set_pos_to_cell_nbr(list, 21);
	  lfll_detach_cell(tmp, prev);
	  printf("-->%15p-->%15p-->%15p\n", prev, prev->next, prev->next->next);
	  printf("%18p(%d)%18p(%d)%18p(%d)\n", prev->val, prev->index, prev->next->val, prev->next->index, prev->next->next->val, prev->next->next->index);
	  lfll_free_elem(tmp, data_destroy);
	  count++;
	  //}
	  gl_count--;
    }
  printf("I just finish to RM   %d cells from the list\n", NBR_RM);
  
  return (NULL);
}

/*
**
*/
int			main(int ac, char **av)
{
  lfll_t		*list, *tmp;
  int			list_size;
  pthread_t		read, add, rm;
  
  list_size=50;
  gl_count=0;
  //Initialising a lfll of list_size cell and 10 aux 
  list=lfll_init_size(list_size, data_init);

  // Printing the list (with debug info)
  lfll_print_list(list, data_print);

  // moving at 42 cell (which doesn't mean aux in the list ) somewhere int the list


  //  data_print((t_data *)tmp->val);

  // I create a process that move around the list
  pthread_create(&read, NULL, list_read, list);
  
  // I create a process that will add a cell a position 42
  pthread_create(&add, NULL, list_add, list);

  // I create a process, which wait for the previous one, then destroy the 42 cell
  pthread_create(&rm, NULL, list_rm, list);
  
  //Destroying list
  pthread_join(read, NULL);
  pthread_join(add, NULL);
  pthread_join(rm, NULL);
  lfll_print_list(list, data_print);
  lfll_destroy_list(list, data_destroy);
  exit (0);
}
