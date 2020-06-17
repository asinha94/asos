#ifndef ASOS_ISR_H
#define ASOS_ISR_H

#include <stdint.h>



// ivect is a pointer to void function which takes a pointer to isr_input
typedef void (*ivect)(isr_data * );

#endif