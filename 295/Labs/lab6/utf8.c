// By Randy Panopio
// ID: 301294517
// rpanopio@sfu.ca 

#include <stdint.h>
#include <stdio.h>
#include "utf8.h"

void decode_utf8(const char* s) {
    unsigned i = 0;
    uint32_t n;
    uint8_t n_bytes;

    int bmask_first1 = 0b10000000;
    int bmask_first2 = 0b11000000;
    int bmask_first3 = 0b11100000;
    int bmask_first4 = 0b11110000;
    int bmask_first5 = 0b11111000;
    int bmask_last3 = 0b00000111;
    int bmask_last4 = 0b00001111;
    int bmask_last5 = 0b00011111;
    int bmask_last6 = 0b00111111;
    

    while (s[i] != '\0') {
        // bitwise and first leading bits to the current utf8 size is, eg if 2 bytes, it must start with 110, apply AND 111 then check if its stil 110, its 2 bytes
        // then find the unicode number by extracting it from byte representation by isolating relevant bits, shift bits to position, and combine to the final byte using bitwise OR
        if ((s[i] & bmask_first1) == 0) { // Single-byte case
            n = s[i]; // already in correct unicode number, first 7 bits is all we need, 8th bit is already 0
            n_bytes = 1;
            report_character(n, n_bytes);
            i += n_bytes;
        } else if ((s[i] & bmask_first3) == bmask_first2) { // Two-byte case
            // relevant bits: 110xxxxx	10xxxxxx
            // shift byte 1 left by 6, get byte 2's first 6 bits, get final 32 bit with bitewise OR 
            n = ((s[i] & bmask_last5) << 6) | (s[i + 1] & bmask_last6);
            n_bytes = 2;
            report_character(n, n_bytes);
            i += n_bytes; // shift 2 bytes over to next char
        } else if ((s[i] & bmask_first4) == bmask_first3) { // Three-byte case
            // relevant bits: 1110xxxx	10xxxxxx	10xxxxxx
            // get byte 1's 6 bits by shift left 12, get byte 2's 6 bits by shift left 6, get byte 3's first 6 bits, get final 32 bit with bitewise OR 
            n = ((s[i] & bmask_last4) << 12) | ((s[i + 1] & bmask_last6) << 6) | (s[i + 2] & bmask_last6);
            n_bytes = 3;
            report_character(n, n_bytes);
            i += n_bytes; // shift 3 bytes over to next char
        } else if ((s[i] & bmask_first5) == bmask_first4) { // Four-byte case
            // relevant bits 11110xxx	10xxxxxx	10xxxxxx	10xxxxxx
            // get byte 1's 6 bits by shift left 18, get byte 2's 6 bits by shift left 12, get byte 3's 6 bits by shift left 6, get byte 4's first 6 bits, get final 32 bit with bitewise OR 
            n = ((s[i] & bmask_last3) << 18) | ((s[i + 1] & bmask_last6) << 12) | ((s[i + 2] & bmask_last6) << 6) | (s[i + 3] & bmask_last6);
            n_bytes = 4;
            report_character(n, n_bytes);
            i += n_bytes; // shift 4 bytes over to next char
        } else {
            printf("<li>Unknown byte, 0x%02hhx</li>\n", s[i]);
            i++;
        }
    }
}
