
http://stackoverflow.com/questions/1001307/detecting-endianness-programmatically-in-a-c-program

#include <stdio.h>
#include <stdint.h>

int is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } e = { 0x01000000 };

    return e.c[0];
}

int main(void)
{
    printf("System is %s-endian.\n",
        is_big_endian() ? "big" : "little");

    return 0;
}

//
byte    swaptest[2] = {1,0};
if ( *(short *)swaptest == 1) {
    bigendien = false;
//

#include <inttypes.h>
int main(int argc, char ** argv){
    volatile uint32_t i=0x01234567;
    // return 0 for big endian, 1 for little endian.
    return (*((uint8_t*)(&i))) == 0x67;
}

if ( htonl(47) == 47 ) {
  // Big endian
} else {
  // Little endian.
}
