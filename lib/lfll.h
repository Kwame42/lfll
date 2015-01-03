/*
**
*/
#include <stdio.h>
#include <stdlib.h>
/*
**
*/
typedef struct					lfll_s
{
  int						index;
  void						*val;
  struct lfll_s					*next;
}						lfll_t;

/*
**
*/
#define LFLL_ELEM_TYPE_AUX			(0)
#define LFLL_ELEM_TYPE_CELL			(!(LFLL_ELEM_TYPE_AUX))
#define LFLL_PRINT_DEBUG			(1<<0)
#define LFLL_PRINT_
/*
**
*/
#define lfll_elem_type(list)			((list)->index == LFLL_ELEM_TYPE_AUX ? LFLL_ELEM_TYPE_AUX : LFLL_ELEM_TYPE_CELL)

/*
**
*/
lfll_t						*lfll_init_size(int, void *(*)());
void						lfll_destroy_list(lfll_t *, void (*)(void *));
lfll_t						*lfll_init_cell(int);
lfll_t						*lfll_init_aux(void);
void						lfll_print_list(lfll_t *, void (*)(void *));
int						lfll_detach_cell(lfll_t *, lfll_t *);
int						lfll_reattach_cell(lfll_t *, lfll_t *);
void						lfll_free_elem(lfll_t *, void (*)());
int						lfll_add_cell(lfll_t *, void *(*)());
lfll_t						*lfll_last_elem(lfll_t *);
lfll_t						*lfll_last_cell(lfll_t *);
int						lfll_list_size(lfll_t *);
lfll_t						*lfll_set_pos_in_list(lfll_t *, int);
lfll_t						*lfll_set_pos_to_cell_nbr(lfll_t *, int);
