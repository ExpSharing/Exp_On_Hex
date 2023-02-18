#include <stdio.h>
#include <stdlib.h>
#include <hex_tables.h>

const int buffer_size = 120;

int main( int argc, char *argv[]) {
    
    // The default value for the number of lines to be shown is 16 (the complete table)
    uint8_t size = 16;

    // If we pass a value to the executable that will be interpreted as the number of lines we want to show
    if( argc > 1 ) {
        size = (uint8_t)atoi(argv[1]);

        // If the provided argument is greater than 16 we print an error since we will be facing an overflow issue (**NOT AN ERROR**)
        if( size > 16 ) {
            fprintf(stderr,"Values greater than 16 should not be provided\n");
            return 1;
        }
    }

    char line[buffer_size]; // This is the buffer that will be used to perform output operations.
    hex_table(line,size);

    if(size == 16) {
        printf("\nNote that on the last value (0x10 * 0x10) the result is shown to be 0x00.\n");
        printf("This is due to the fact that we've been using 'uint8_t' integers, which can hold numbers up to 255.\n");
        printf("Here, 0x10 * 0x10 would result in 0x0100 which is 256, so one more that we can store with the current format.\n");
    }
    return 0;
}
