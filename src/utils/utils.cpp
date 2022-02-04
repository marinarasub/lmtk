#include "utils.h"

namespace utils {

    uint32_t uint_max_val(uint8_t bit_depth)
    {
        if (bit_depth > 32) bit_depth = 32;
        return std::numeric_limits<std::uint32_t>::max() >> (32 - bit_depth);
    }


    // why is this so slow???
    uint64_t uint64_next_pwr2(uint64_t val)
    {
        uint64_t test = 1;
        while (val > test)
        {
            test *= 2;

        }
        return test;
    }

    std::string get_size_string(size_t byte_size)
    {
        std::string size;
        if (byte_size < 1024) size = std::to_string(byte_size) + " B";
        else if (byte_size >= 1024 && byte_size < 1024 * 1024) size = std::to_string((double)byte_size / 1024) + " KB"; // KB
        else if (byte_size >= 1024 * 1024) size = std::to_string((double) byte_size / (1024 * 1024)) + " MB"; // MB
        return size; // TODO use utils to truncate to sigfig or fixed precison
    }

}

