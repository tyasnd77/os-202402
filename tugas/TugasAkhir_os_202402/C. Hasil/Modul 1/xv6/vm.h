#ifndef VM_H
#define VM_H

#include "types.h"
#include "mmu.h"
#include "proc.h"

pde_t* cowuvm(pde_t *pgdir, uint sz);
pte_t* walkpgdir(pde_t *pgdir, const void *va, int alloc);
int mappages(pde_t *pgdir, void *va, uint size, uint pa, int perm);
void decref(char *pa);
void incref(char *pa); // kalau ada incref juga

#endif
