#ifndef ASOS_ISR_H
#define ASOS_ISR_H

#include <stdint.h>

struct isr_data_struct {
    uint32_t eax;
};
typedef struct isr_data_struct isr_data;

// ivect is a pointer to void function which takes a pointer to isr_input
typedef void (*ivect)(isr_data * );

#endif