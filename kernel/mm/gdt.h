#ifndef ASOS_GDT_H
#define ASOS_GDT_H

#include <stdint.h>
#include <stddef.h>

namespace asos {

    class GDTSegment {
    public:
        GDTSegment() {};
        GDTSegment(const GDTSegment & other) = default;
        GDTSegment(GDTSegment && other) = default;
        GDTSegment& operator=(const GDTSegment & other) = default;
        GDTSegment& operator=(GDTSegment && other) = default;
        GDTSegment(uint32_t base, uint32_t limit, uint8_t type, uint8_t granularity);
        uint8_t getType() {return m_type;}
    private:
        uint16_t m_limit_lower;
        uint16_t m_base_lower;
        uint8_t  m_base_middle;
        uint8_t  m_type;
        uint8_t  m_granularity;
        uint8_t  m_base_upper;
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
    #pragma pop
}


#endif
