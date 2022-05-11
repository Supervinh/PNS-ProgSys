/*
 * my-malloc.c  -- Implementation de malloc, free, calloc, realloc
 *
 * Implémentation first-fit pour malloc
 *
 * Erick Gallesio (2020/04/10)
 * Stéphane Lavirotte (2020/04/16)
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include "mymalloc.h"

// ======================================================================
//
//    Définition des fonctions. NE PAS MODIFIER CETTE PREMIERE PARTIE.
//
// ======================================================================


// Les fonctions internes à implémenter
void *internal_malloc(size_t size);
void  internal_free(void *ptr);
void *internal_calloc(size_t nmemb, size_t size);
void *internal_realloc(void *ptr, size_t size);


// Les fonctions externes: ces fonctions appellent les fonctions internes 
//  que vous avez à écrire en y ajoutant une trace qui est utilisée par 
//  to-html et villoc.py pour générer les .html 
void *mysbrk(intptr_t increment) {
  void *ret, *old, *tmp;
  static int first_call = 1;

  if (first_call) {
    old =sbrk(0);
    fprintf(stderr, "SYS_brk(0)                    =  %p\n", old);
    first_call = 0;
  }

  ret = sbrk(increment);
  tmp = ret +increment;
  fprintf(stderr, "SYS_brk(%p)                    = %p\n", tmp, tmp);
  return ret;
}

void *mymalloc(size_t size) {
  void *ret = internal_malloc(size);
  fprintf(stderr, "mymalloc(%ld)                     = %p\n",  size, ret);
  return ret;
}

void myfree(void *ptr) {
  internal_free(ptr);
  fprintf(stderr, "myfree(%p)                    = <void>\n", ptr);
}

void *myrealloc(void *ptr, size_t size) {
  void *ret = internal_realloc(ptr, size);
  fprintf(stderr, "myrealloc(%p, %ld)                     = %p\n",  ptr, size, ret);
  return ret;
}

void *mycalloc(size_t nmemb, size_t size) {
  void *ret = internal_calloc(nmemb, size);
  fprintf(stderr, "mycalloc(%ld, %ld)                   = %p\n",  nmemb, size, ret);
  return ret;
}


// ======================================================================
//
//    Implementation
//
// ======================================================================


/* On suppose qu'on ajoute au moins 50 Headers au minimum */
#define MIN_ALLOCATION        50

/* Pour s'aligner sur des frontieres multiples
 * de la taille du type le plus contraignant
 */
#define MOST_RESTRICTING_TYPE long double
typedef union header {                          /* Header de bloc */
    struct {
        size_t size;                            /* Taille du bloc */
        union header *ptr;                      /* bloc libre suivant */
    } info;
    MOST_RESTRICTING_TYPE dummy;        /* Ne sert qu'a provoquer un alignement */
} Header;
#define HEADER_SIZE sizeof(Header)

#define NEXT(p)                  ((p)->info.ptr)
#define SIZE(p)                  ((p)->info.size)

/* L'unité de découpage de la mémoire est la taille de Header car ça permet de gérer facilement chaînage
   Le programme appelant malloc reçoit un pointeur et utilise la mémoire comme il veut.
   BLOCKS_TO_ALLOCATE renvoie le nombre de blocks nécessaires pour le malloc demandé, en tenant compte du header */
#define BLOCKS_TO_ALLOCATE(size) (1 + (size + HEADER_SIZE - 1) / HEADER_SIZE)

static Header base   = { {0, &base} }; /* Le pointeur de départ: aucune zone allouée */
static Header *freep = &base;          /* freep pointe sur la 1ère zone libre */

/* ====================================================================== */

/* Utilisé si on n'a pas trouvé assez de place */
static void *allocate_core(size_t size)
{
    Header *new;

    /* Allouer au moins MIN_ALLOCATION cellules */
    if (size < MIN_ALLOCATION)
        size = MIN_ALLOCATION;

    new = mysbrk(size * sizeof(Header));
    if (new  == ((void *) - 1))
        return NULL;     /* Plus de memoire */

#ifdef MALLOC_DBG
    fprintf(stderr, "\t--> sbrk(%ld) [%ld blocks]\n", size * sizeof(Header), size);
#endif
    /* Mettre a jour la taille du Header */
    SIZE(new) = size;

    /* Liberer ce bloc (ceci afin de le remettre dans la liste libre) */
    internal_free(new + 1);

    /* Retourner le pointeur sur le debut de la zone libre */
    return freep;
}

/* ====================================================================== */

void *internal_malloc(size_t size)
{
    
  size_t size_in_block = BLOCKS_TO_ALLOCATE(size);

  Header *free_node = freep;
  Header *next_free_node = NEXT(free_node);

  while (next_free_node != freep)
  {
    size_t next_free_node_size = SIZE(next_free_node);
    if (next_free_node_size == size_in_block)
    {
      NEXT(free_node) = NEXT(next_free_node);
      NEXT(next_free_node) = NULL;

      return next_free_node + 1;
    }

    if (next_free_node_size >= size_in_block)
    {
      Header *next_next_free_node = next_free_node + size_in_block;
      NEXT(next_next_free_node) = NEXT(next_free_node);
      SIZE(next_next_free_node) = next_free_node_size - size_in_block;

      NEXT(free_node) = next_next_free_node;

      // On le met à null, on sait jamais
      SIZE(next_free_node) = size_in_block;
      NEXT(next_free_node) = NULL;

      return next_free_node + 1;
    }

    free_node = next_free_node;
    next_free_node = NEXT(next_free_node);
  }

  size_t blocks_to_request = (size_in_block < MIN_ALLOCATION) ? MIN_ALLOCATION : size_in_block;

  allocate_core(blocks_to_request);

  return internal_malloc(size);
}

/* ====================================================================== */

void internal_free(void *ptr)
{
    Header *bp, *p, *prevp;

    if (!ptr)
        /* On peut appeller free avec NULL. Ne rien faire dans ce cas */
        return;

    /* Ajuster bp sur le debut du bloc */
    bp = ((Header *) ptr) - 1;

    for (prevp = freep, p = NEXT(freep);    ; prevp = p, p = NEXT(p)) {
        if (NEXT(prevp) == freep || p > bp) {
            break;
        }
    }

    /* Essayer de "coller" ce bloc au suivant */
    if (bp + SIZE(bp) == p) {
        SIZE(bp) += SIZE(p);
        NEXT(bp)  = NEXT(p);
    } else {
        NEXT(bp) = p;
    }

    /* Essayer de "coller" ce bloc au precedent */
    if (prevp + SIZE(prevp) == bp) {
        SIZE(prevp) += SIZE(bp);
        NEXT(prevp)  = NEXT(bp);
    } else {
        NEXT(prevp) = bp;
    }
}

/* ====================================================================== */

void *internal_calloc(size_t nmemb, size_t size)
{
    size_t size_in_byte = nmemb * size;
    void* tmp = internal_malloc(size_in_byte);

    memset(tmp, 0, size_in_byte);

    return tmp;
}

void *internal_realloc(void *ptr, size_t size)
{
  Header *ptr_header = ((Header *)ptr) - 1;
  size_t ptr_header_size = SIZE(ptr_header);

  if ((ptr_header_size - 1) * HEADER_SIZE >= size)
  {
    return ptr;
  }

  internal_free(ptr);
  void *tmp = internal_malloc(size);

  void *old_start = ptr_header + 1;
  void *old_end = ptr_header + ptr_header_size;

  void *new_start = tmp;
  void *new_end = tmp + size;

  ptrdiff_t off_1 = old_end - new_start;
  ptrdiff_t off_2 = old_start - new_end;

  if (off_1 * off_2 > 0)
  {
    memcpy(tmp, ptr, ptr_header_size);
  }
  else
  {
    memmove(tmp, ptr, ptr_header_size);
  }

  return tmp;
}

