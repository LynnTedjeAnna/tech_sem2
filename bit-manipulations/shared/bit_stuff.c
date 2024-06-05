#include "bit_stuff.h"
#include <limits.h>
#include <stddef.h>

// leave resource_detector.h as last include!
#include "resource_detector.h"

uint8_t count_ones(uint8_t value){
    uint8_t count = 0;

    /* Examples:
        value = 0b110011 (4 bits are one)
        return value should be 4 
    */
    while (value != 0) {
        if (value & 1) { // Check if the last bit is 1
            count++;
        }
        value = value >> 1; // Shift bits to the right
    }
    return count;
}

void make_bitmask(uint8_t width, uint8_t shift, uint8_t* mask){
    /* Examples:
    width = 3, shift = 0 
    --------------------------------- 
    mask = 0b111 (a bit mask with a width of 3 bits)

    width = 4, shift = 2 
    --------------------------------- 
    mask = 0b111100 (a bit mask with a width of 4 bits, that is shift to left for 2 bits)
    */
    // Create the mask with width bits set to 1
    *mask = (1 << width) - 1;

    // Shift the mask left by shift bits
    *mask <<= shift;
}

void apply_bitmask(uint8_t value, uint8_t mask, uint8_t* masked_value){
    /* Example:
        value          =    0b 1100 1010
        mask           =    0b 0000 1111   
        --------------------------------- 
        masked_valued  =    0b 0000 1010
    */
    *masked_value = value & mask;
}

void flip_bit(uint8_t value, uint8_t bit_index, uint8_t* updated_value){
    /* Example:
       value          =    0b 1100 1010
       bit_index      =            3
       --------------------------------- 
       updated_value  =    0b 1100 1110
    */
    *updated_value = value ^ (0b1 << bit_index);
}

void extract_nibbles_from_byte(uint8_t value, uint8_t* high_nibble, uint8_t* low_nibble){
    /* Examples:
    value          =    0b 1100 1010
    ----------------------------------
    high_nibble    =    0b 1100
    low_nibble      =         0b 1010

    value          =    0x C A (using hexadecimal notation)
    ----------------------------------
    high_nibble    =    0xC
    low_nibble      =        0xA
    */
    *low_nibble = value & 0b1111;
    *high_nibble = value >> 4;
}

void combine_nibbles_to_byte(uint8_t high_nibble, uint8_t low_nibble, uint8_t* value){
    /* Examples:
    high_nibble    =    0b 1100
    low_nibble      =         0b 1010
    ----------------------------------
    value          =    0b 1100 1010

    high_nibble    =    0xC
    low_nibble      =        0xA
    ----------------------------------
    value          =    0x C A (using hexadecimal notation)
    */
    // Shift the high nibble to the left by 4 positions to align it properly in the byte
    *value = high_nibble << 4;

    // Combine the low nibble with the byte value using bitwise OR
    // Ensure that only the lower 4 bits of the low nibble are considered by masking with 0b1111
    *value |= (low_nibble & 0b1111);

}
