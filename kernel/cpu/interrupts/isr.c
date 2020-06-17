#include <cpu/interrupts/isr.h>
#include <cpu/interrupts/idt.h>
#include <cpu/interrupts/pic.h>


ivect ivt[IDT_LEN];

void isr_handler_33(isr_data * data)
{
    //irq_eoi();
}