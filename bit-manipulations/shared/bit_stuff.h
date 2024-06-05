#pragma once

#include <stdint.h>

/* pre : -
 * post: the number of bits with value 1 is counted and returned
 */
uint8_t count_ones(uint8_t value);

/* pre : -
 * post: a bitmask with a given width and a given shift is generated (so w=5 and
 *       s=1 gives 00111110)
 */
void make_bitmask(uint8_t width, uint8_t shift, uint8_t* mask);

/* pre : -
 * post: 'masked_value' is assigned the value of 'value' with the 'mask' applied
 */
void apply_bitmask(
            uint8_t value, uint8_t mask, uint8_t* masked_value);

/* pre : -
 * post: the bit of index 'bit_index' of 'value' is flipped: 0 --> 1, 1 --> 0.
 */
void flip_bit(
            uint8_t value, uint8_t bit_index,
            uint8_t* updated_value);

/* pre : -
 * post: the high and low nibbles of 'value' of stored in 'high_nibble' and
 *       'low_nibble'.
 */
void extract_nibbles_from_byte(
            uint8_t value, uint8_t* high_nibble, uint8_t* low_nibbe);

/* pre : -
 * post: the nibble values of the 'high_nibble' and 'low_nibble' are combined
 *       and stored in 'value'
 */
void combine_nibbles_to_byte(
            uint8_t high_nibble, uint8_t low_nibble, uint8_t* value);
