#include <stddef.h>
#include <cpu/interrupts/idt.h>
#include <cpu/interrupts/pic.h>
#include <libk/kprintf.h>


extern "C" void asm_init_idt(uint32_t idt_address);
extern "C" void asm_handler_isr0();
extern "C" void asm_handler_isr1();
extern "C" void asm_handler_isr2();
extern "C" void asm_handler_isr3();
extern "C" void asm_handler_isr4();
extern "C" void asm_handler_isr5();
extern "C" void asm_handler_isr6();
extern "C" void asm_handler_isr7();
extern "C" void asm_handler_isr8();
extern "C" void asm_handler_isr9();
extern "C" void asm_handler_isr10();
extern "C" void asm_handler_isr11();
extern "C" void asm_handler_isr12();
extern "C" void asm_handler_isr13();
extern "C" void asm_handler_isr14();
extern "C" void asm_handler_isr15();
extern "C" void asm_handler_isr16();
extern "C" void asm_handler_isr17();
extern "C" void asm_handler_isr18();
extern "C" void asm_handler_isr19();
extern "C" void asm_handler_isr20();
extern "C" void asm_handler_isr21();
extern "C" void asm_handler_isr22();
extern "C" void asm_handler_isr23();
extern "C" void asm_handler_isr24();
extern "C" void asm_handler_isr25();
extern "C" void asm_handler_isr26();
extern "C" void asm_handler_isr27();
extern "C" void asm_handler_isr28();
extern "C" void asm_handler_isr29();
extern "C" void asm_handler_isr30();
extern "C" void asm_handler_isr31();




namespace asos {

    static IDTEntry * idt_entries    = nullptr;
    static IVTPtr * ivt              = nullptr;
    static size_t handled_interuppts = 0;

    static void default_isr_handler(ISRData * data)
    {
        kprintf("Unhandled Exception: %d\n", data->int_no);
        for(;;);
    }

    extern "C" void isr_dispatcher(ISRData * regs)
    {
        if (regs->int_no >= handled_interuppts) {
            kprintf("No handler found for: int %u\n", regs->int_no);
            return;
        }

        IVTPtr handler = ivt[regs->int_no];
        if (handler == NULL) {
            kprintf("No handler found for: int %u\n", regs->int_no);
            return;
        }
        handler(regs);
    }

    void IDTHandler::insertIDTEntry(uint8_t index, uint32_t handler, IVTPtr kernel_hander)
    {
        IDTEntry entry;
        entry.offset_l = (handler >>  0) & 0xFFFF;
        entry.offset_h = (handler >> 16) & 0xFFFF;
        // Selector tells the CPU what GDT segment, CPL etc... we want to be in
        // when we run this handler. The Answer is always the same...Kernel code segment
        // Look here for details https://wiki.osdev.org/Selector
        entry.selector = 0x8; //0b 0000 0000 0000 1000
        entry.zero = 0; // always zero
        // Type attribute tells us who/what is calling this routine
        // https://wiki.osdev.org/Interrupts_Descriptor_Table for more details
        entry.type_attr =  0x8E;
        // 0xEF for trap which doesn't disable interrupts

        // Insert the handlers
        idt_entries[index] = entry;
        ivt[index] = kernel_hander;
        handled_interuppts++;
        
    }

    void IDTHandler::initIDT()
    {
        kprintf("Creating CPU Exception IDT entries\n");
        idt_entries = new IDTEntry[IDTHandler::table_size];
        ivt         = new IVTPtr[IDTHandler::table_size];
        // Install first 32 handlers for CPU Exceptions
        IDTHandler::insertIDTEntry(0, (uint32_t) asm_handler_isr0, default_isr_handler);
        IDTHandler::insertIDTEntry(1, (uint32_t) asm_handler_isr1, default_isr_handler);
        IDTHandler::insertIDTEntry(2, (uint32_t) asm_handler_isr2, default_isr_handler);
        IDTHandler::insertIDTEntry(3, (uint32_t) asm_handler_isr3, default_isr_handler);
        IDTHandler::insertIDTEntry(4, (uint32_t) asm_handler_isr4, default_isr_handler);
        IDTHandler::insertIDTEntry(5, (uint32_t) asm_handler_isr5, default_isr_handler);
        IDTHandler::insertIDTEntry(6, (uint32_t) asm_handler_isr6, default_isr_handler);
        IDTHandler::insertIDTEntry(7, (uint32_t) asm_handler_isr7, default_isr_handler);
        IDTHandler::insertIDTEntry(8, (uint32_t) asm_handler_isr8, default_isr_handler);
        IDTHandler::insertIDTEntry(9, (uint32_t) asm_handler_isr9, default_isr_handler);
        IDTHandler::insertIDTEntry(10, (uint32_t) asm_handler_isr10, default_isr_handler);
        IDTHandler::insertIDTEntry(11, (uint32_t) asm_handler_isr11, default_isr_handler);
        IDTHandler::insertIDTEntry(12, (uint32_t) asm_handler_isr12, default_isr_handler);
        IDTHandler::insertIDTEntry(13, (uint32_t) asm_handler_isr13, default_isr_handler);
        IDTHandler::insertIDTEntry(14, (uint32_t) asm_handler_isr14, default_isr_handler);
        IDTHandler::insertIDTEntry(15, (uint32_t) asm_handler_isr15, default_isr_handler);
        IDTHandler::insertIDTEntry(16, (uint32_t) asm_handler_isr16, default_isr_handler);
        IDTHandler::insertIDTEntry(17, (uint32_t) asm_handler_isr17, default_isr_handler);
        IDTHandler::insertIDTEntry(18, (uint32_t) asm_handler_isr18, default_isr_handler);
        IDTHandler::insertIDTEntry(19, (uint32_t) asm_handler_isr19, default_isr_handler);
        IDTHandler::insertIDTEntry(20, (uint32_t) asm_handler_isr20, default_isr_handler);
        IDTHandler::insertIDTEntry(21, (uint32_t) asm_handler_isr21, default_isr_handler);
        IDTHandler::insertIDTEntry(22, (uint32_t) asm_handler_isr22, default_isr_handler);
        IDTHandler::insertIDTEntry(23, (uint32_t) asm_handler_isr23, default_isr_handler);
        IDTHandler::insertIDTEntry(24, (uint32_t) asm_handler_isr24, default_isr_handler);
        IDTHandler::insertIDTEntry(25, (uint32_t) asm_handler_isr25, default_isr_handler);
        IDTHandler::insertIDTEntry(26, (uint32_t) asm_handler_isr26, default_isr_handler);
        IDTHandler::insertIDTEntry(27, (uint32_t) asm_handler_isr27, default_isr_handler);
        IDTHandler::insertIDTEntry(28, (uint32_t) asm_handler_isr28, default_isr_handler);
        IDTHandler::insertIDTEntry(29, (uint32_t) asm_handler_isr29, default_isr_handler);
        IDTHandler::insertIDTEntry(30, (uint32_t) asm_handler_isr30, default_isr_handler);
        IDTHandler::insertIDTEntry(31, (uint32_t) asm_handler_isr31, default_isr_handler);

        init_irq();

        // Install the ISRs
        uint16_t tbl_size = IDTHandler::table_size * sizeof(IDTEntry) - 1;
        IDTHandler * idt = new IDTHandler(tbl_size, (uint32_t) idt_entries);
        asm_init_idt((uint32_t) idt);
        kprintf("IDT loaded\n");
    }


}