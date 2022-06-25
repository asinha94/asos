#ifndef ASOS_GDT_H
#define ASOS_GDT_H

#include <stdint.h>
#include <stddef.h>

namespace asos {

    class GDTSegment {
    public:
        GDTSegment() {};
        GDTSegment& operator=(GDTSegment && other)
        {
            this->m_limit_lower = other.m_limit_lower;
            this->m_base_lower = other.m_base_lower;
            this->m_base_middle = other.m_base_middle;
            this->m_type = other.m_type;
            this->m_granularity = other.m_granularity;
            this->m_base_upper = other.m_base_upper;
            return *this;
        }
        GDTSegment(uint32_t base, uint32_t limit, uint8_t type, uint8_t granularity);

    private:
        uint16_t m_limit_lower = 0;
        uint16_t m_base_lower  = 0;
        uint8_t  m_base_middle = 0;
        uint8_t  m_type        = 0;
        uint8_t  m_granularity = 0;
        uint8_t  m_base_upper  = 0;
    };

    #pragma pack(push, 1)
    class GDTTable {
    public:
        static constexpr size_t table_size = 5;
        static void initGDT();
    private:
        uint16_t m_length;
        uint32_t m_segments;
    };
    #pragma pack(pop)
}


#endif
