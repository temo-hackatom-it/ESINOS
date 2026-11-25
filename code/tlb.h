#ifndef TLB_H
#define TLB_H

#include "memory.h"

#define TLB_SIZE 2

typedef struct {
    int page;
    int frame;
} TLBEntry;

void init_tlb(TLBEntry tlb[]);

int search_tlb(TLBEntry tlb[], int page);

void update_tlb(TLBEntry tlb[], int page,
                int frame, int *next);

double calculate_eat(double hit_rate,
                     double tlb_time,
                     double memory_time);

void menu_tlb(void);

#endif