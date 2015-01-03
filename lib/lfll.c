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
#include "lfll.h"

/*
**
*/

lfll_t				*lfll_init_size(int size, void *(*init_func)(void))
{
  lfll_t			*first;
  lfll_t			*prev;
  lfll_t			*tmp;
  int				i;

  if (size == 0)
    return (NULL);
  first=NULL;
  i=1;
  tmp=NULL;
  do {
    prev=tmp;
    tmp=lfll_init_cell(i);
    tmp->val=init_func();
    if (!first)
      first=tmp;
    else
      prev->next->next=tmp;
    i++;
  } while (i <= size);
    
  return (first);
}

void				lfll_destroy_list(lfll_t *list, void (*destroy_func)(void *val))
{
  lfll_t			*tmp;

  do
    {
      tmp=list;
      if (tmp->val)
	destroy_func(list->val);
      free(tmp);
      list=list->next;
    } while (list);
}

lfll_t				*lfll_init_cell(int index)
{
  lfll_t			*cell;
  lfll_t			*aux;

  if ((cell=malloc(sizeof(lfll_t))) == NULL)
    return NULL;
  memset(cell, 0, sizeof(lfll_t));
  aux=lfll_init_aux();
  cell->index=index;
  cell->next=aux;
  
  return (cell);
}

lfll_t				*lfll_init_aux(void)
{
  lfll_t			*aux;

  if ((aux=malloc(sizeof(lfll_t))) == NULL)
    return NULL;
  memset(aux, 0, sizeof(lfll_t));
  
  return (aux);
}


void				lfll_print_list(lfll_t *list, void (*print_func)(void *val))
{
  lfll_t			*tmp;

  for (tmp=list ; tmp->next ; tmp=tmp->next)
    if (lfll_elem_type(tmp) == LFLL_ELEM_TYPE_CELL)
      {
	printf("|-[%p][%d]->",tmp, tmp->index);
	print_func(tmp->val);
      }
    else
      printf("|-[%p------->", tmp);
  printf("\n");
}

int				 lfll_detach_cell(lfll_t *cell, lfll_t *prev)
// on my mac (intel core i7 2.5ghz) tell around 333 333 333 detach / second
{
  if (prev->next->next != cell)
    return (0);
  (prev)->next->next=(cell)->next;

  return (1);
}

int				lfll_reattach_cell(lfll_t *list, lfll_t *cell)
// Test on my mac (intel core i7 2.5ghz) tell around 22 727 272 reattach / second
{
  lfll_t			*tmp;

  tmp=lfll_init_aux();
  if (!tmp)
    return (0);
  cell->next=tmp;
  cell->next->next=list->next->next;
  if (!list->next->next)
    return (0);
  list->next->next=cell;

  return (1);
}

void				lfll_free_elem(lfll_t *list, void (*destroy_func)(void *val))
{
  if (list->val)
    destroy_func(list->val);
  free(list);
}

int				lfll_add_cell(lfll_t *list, void *(*init_func)(void))
// Test on my mac (intel core i7 2.5ghz) tell around 12 500 000 add / second (without mall for val)
{
  lfll_t			*new_elem;

  new_elem=lfll_init_cell(list->index+1);
  new_elem->next->next=list->next->next;
  if (list->next->next != new_elem->next->next)
    {
      free(new_elem->next);
      free(new_elem);
      
      return (0);
    }
    list->next->next=new_elem;
    return (1);
}

lfll_t				*lfll_last_elem(lfll_t *list)
{
  for ( ; list->next ; list=list->next)
    ;

  return (list);
}

lfll_t				*lfll_last_cell(lfll_t *list)
{
  lfll_t			*last_cell;
  
  for ( ; list->next ; list=list->next)
    if (lfll_elem_type(list) == LFLL_ELEM_TYPE_CELL)
      last_cell=list;

  return (last_cell);
}

int				lfll_list_size(lfll_t *list)
{
  int				size;
  
  for (size=0 ; list->next ; list=list->next)
    size++;

  return (size);
}

lfll_t				*lfll_set_pos_in_list(lfll_t *list, int pos)
{
  for ( ; (list->next) && (pos > 0) ; pos--)
    list=list->next;

  return (list);
}

lfll_t				*lfll_set_pos_to_cell_nbr(lfll_t *list, int pos)
{
  while ((list->next) && (pos > 1))
    {
      list=list->next;
      if (lfll_elem_type(list) == LFLL_ELEM_TYPE_CELL)
	pos--;
    }

  return (list);
}
