#include <cpu/interrupts/exception.h>
#include <cpu/interrupts/idt.h>

// CPU Exception handlers
extern void asm_handler_isr0();
extern void asm_handler_isr1();
extern void asm_handler_isr2();
extern void asm_handler_isr3();
extern void asm_handler_isr4();
extern void asm_handler_isr5();
extern void asm_handler_isr6();
extern void asm_handler_isr7();
extern void asm_handler_isr8();
extern void asm_handler_isr9();
extern void asm_handler_isr10();
extern void asm_handler_isr11();
extern void asm_handler_isr12();
extern void asm_handler_isr13();
extern void asm_handler_isr14();
extern void asm_handler_isr15();
extern void asm_handler_isr16();
extern void asm_handler_isr17();
extern void asm_handler_isr18();
extern void asm_handler_isr19();
extern void asm_handler_isr20();
extern void asm_handler_isr21();
extern void asm_handler_isr22();
extern void asm_handler_isr23();
extern void asm_handler_isr24();
extern void asm_handler_isr25();
extern void asm_handler_isr26();
extern void asm_handler_isr27();
extern void asm_handler_isr28();
extern void asm_handler_isr29();
extern void asm_handler_isr30();
extern void asm_handler_isr31();

static void handler_isr0(isr_data * data)
{

}

static void handler_isr1(isr_data * data)
{

}

static void handler_isr2(isr_data * data)
{

}

static void handler_isr3(isr_data * data)
{

}

static void handler_isr4(isr_data * data)
{

}

static void handler_isr5(isr_data * data)
{

}

static void handler_isr6(isr_data * data)
{

}

static void handler_isr7(isr_data * data)
{

}

static void handler_isr8(isr_data * data)
{

}

static void handler_isr9(isr_data * data)
{

}

static void handler_isr10(isr_data * data)
{

}

static void handler_isr11(isr_data * data)
{

}

static void handler_isr12(isr_data * data)
{

}

static void handler_isr13(isr_data * data)
{

}

static void handler_isr14(isr_data * data)
{

}

static void handler_isr15(isr_data * data)
{

}

static void handler_isr16(isr_data * data)
{

}

static void handler_isr17(isr_data * data)
{

}

static void handler_isr18(isr_data * data)
{

}

static void handler_isr19(isr_data * data)
{

}

static void handler_isr20(isr_data * data)
{

}

static void handler_isr21(isr_data * data)
{

}

static void handler_isr22(isr_data * data)
{

}

static void handler_isr23(isr_data * data)
{

}

static void handler_isr24(isr_data * data)
{

}

static void handler_isr25(isr_data * data)
{

}

static void handler_isr26(isr_data * data)
{

}

static void handler_isr27(isr_data * data)
{

}

static void handler_isr28(isr_data * data)
{

}

static void handler_isr29(isr_data * data)
{

}

static void handler_isr30(isr_data * data)
{

}

static void handler_isr31(isr_data * data)
{

}

void init_cpu_exceptions()
{
    kprintf("Creating CPU Exception IDT entries\n");
    // Install first 32 handlers for CPU Exceptions
    insert_idt_entry(0, (uint32_t) asm_handler_isr0, handler_isr0);
    insert_idt_entry(1, (uint32_t) asm_handler_isr1, handler_isr1);
    insert_idt_entry(2, (uint32_t) asm_handler_isr2, handler_isr2);
    insert_idt_entry(3, (uint32_t) asm_handler_isr3, handler_isr3);
    insert_idt_entry(4, (uint32_t) asm_handler_isr4, handler_isr4);
    insert_idt_entry(5, (uint32_t) asm_handler_isr5, handler_isr5);
    insert_idt_entry(6, (uint32_t) asm_handler_isr6, handler_isr6);
    insert_idt_entry(7, (uint32_t) asm_handler_isr7, handler_isr7);
    insert_idt_entry(8, (uint32_t) asm_handler_isr8, handler_isr8);
    insert_idt_entry(9, (uint32_t) asm_handler_isr9, handler_isr9);
    insert_idt_entry(10, (uint32_t) asm_handler_isr10, handler_isr10);
    insert_idt_entry(11, (uint32_t) asm_handler_isr11, handler_isr11);
    insert_idt_entry(12, (uint32_t) asm_handler_isr12, handler_isr12);
    insert_idt_entry(13, (uint32_t) asm_handler_isr13, handler_isr13);
    insert_idt_entry(14, (uint32_t) asm_handler_isr14, handler_isr14);
    insert_idt_entry(15, (uint32_t) asm_handler_isr15, handler_isr15);
    insert_idt_entry(16, (uint32_t) asm_handler_isr16, handler_isr16);
    insert_idt_entry(17, (uint32_t) asm_handler_isr17, handler_isr17);
    insert_idt_entry(18, (uint32_t) asm_handler_isr18, handler_isr18);
    insert_idt_entry(19, (uint32_t) asm_handler_isr19, handler_isr19);
    insert_idt_entry(20, (uint32_t) asm_handler_isr20, handler_isr20);
    insert_idt_entry(21, (uint32_t) asm_handler_isr21, handler_isr21);
    insert_idt_entry(22, (uint32_t) asm_handler_isr22, handler_isr22);
    insert_idt_entry(23, (uint32_t) asm_handler_isr23, handler_isr23);
    insert_idt_entry(24, (uint32_t) asm_handler_isr24, handler_isr24);
    insert_idt_entry(25, (uint32_t) asm_handler_isr25, handler_isr25);
    insert_idt_entry(26, (uint32_t) asm_handler_isr26, handler_isr26);
    insert_idt_entry(27, (uint32_t) asm_handler_isr27, handler_isr27);
    insert_idt_entry(28, (uint32_t) asm_handler_isr28, handler_isr28);
    insert_idt_entry(29, (uint32_t) asm_handler_isr29, handler_isr29);
    insert_idt_entry(30, (uint32_t) asm_handler_isr30, handler_isr30);
    insert_idt_entry(31, (uint32_t) asm_handler_isr31, handler_isr31);
}