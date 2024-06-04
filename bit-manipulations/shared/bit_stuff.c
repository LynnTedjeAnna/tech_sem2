#include "bit_stuff.h"
#include <limits.h>
#include <stddef.h>

// leave resource_detector.h as last include!
#include "resource_detector.h"

unsigned int count_ones(unsigned int value)
{
    unsigned int count = 0;

    /* Examples:

        value = 0b110011 (4 bits are one)
        return value should be 4 
    */

    return count;
}

void make_bitmask(unsigned int width, unsigned int shift, unsigned int* mask)
{
    /* Examples:

    width = 3, shift = 0 
    --------------------------------- 
    mask = 0b111 (a bit mask with a width of 3 bits)

    width = 4, shift = 2 
    --------------------------------- 
    mask = 0b111100 (a bit mask with a width of 4 bits, that is shift to left for 2 bits)
    */

}

void apply_bitmask(
            unsigned int value, unsigned int mask, unsigned int* masked_value)
{
    /* Example:

        value          =    0b 1100 1010
        mask           =    0b 0000 1111   
        --------------------------------- 
        masked_valued  =    0b 0000 1010
    */

}

void flip_bit(
            unsigned int value, 
            unsigned int bit_index,
            unsigned int* updated_value)
{

    /* Example:

       value          =    0b 1100 1010
       bit_index      =            3
       --------------------------------- 
       updated_value  =    0b 1100 00101

    */
}

void extract_nibbles_from_byte(
            uint8_t value, 
            uint8_t* high_nibble, 
            uint8_t* low_nibble)
{
    /* Examples:

    value          =    0b 1100 1010
    ----------------------------------
    high_nibble    =    0b 1100
    low_nible      =         0b 1010

    value          =    0x F 9 (using hexidecimal notation)
    ----------------------------------
    high_nibble    =    0xF
    low_nible      =        0x9

    */

}

void combine_nibles_to_byte(
            uint8_t high_nibble, uint8_t low_nibble, uint8_t* value)
{
    /* Examples:

    high_nibble    =    0b 1100
    low_nible      =         0b 1010
    ----------------------------------
    value          =    0b 1100 1010

    high_nibble    =    0xF
    low_nible      =        0x9
    ----------------------------------
    value          =    0x F 9 (using hexidecimal notation)

    */
}
