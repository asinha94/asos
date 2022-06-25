#ifndef ASOS_IDT_H
#define ASOS_IDT_H

#include <stdint.h>
#include <stddef.h>

namespace asos {

   struct IDTEntry {
      uint16_t offset_l;  // offset bits 0..15
      uint16_t selector;  // a code segment selector in GDT or LDT
      uint8_t  zero;      // unused, set to 0
      uint8_t  type_attr; // type and attributes
      uint16_t offset_h;  // offset bits 16..31
   };


   struct ISRData {
      uint32_t gs, fs, es, ds;
      uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
      uint32_t int_no, err_code;
      uint32_t eip, cs, eflags, useresp, ss;
   };

   using IVTPtr = void (*)(ISRData*);

   #pragma pack(push, 1)
   class IDTHandler {
   public:
      IDTHandler(uint16_t length, uint32_t entries) :
         m_length(length),
         m_entries(entries) {}
      static constexpr size_t table_size = 256;
      static void initIDT();
      static void insertIDTEntry(uint8_t index, uint32_t handler, IVTPtr kernel_hander);

   private:
      uint16_t m_length;
      uint32_t m_entries;
   };
   #pragma pack(pop)
}


#endif