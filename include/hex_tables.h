#pragma once

#include <stdio.h>
#include <stdint.h>

// This macro will be used simply to speed up the typing
#define PRINT_BUF(var) printf("%s\n",var)

/**
 * This structure is used to save useful parameters
 * for the string formatting part.
 */
typedef struct {
    /// Character used to create spaces around `value`
    char spacer;
    /// Value that we want to print
    uint8_t value;
    /// Character used to separate two entries
    char separator;
} line_entry;

/**
 * This function is used to create the format for a single entry
 *
 * @param[out] line is used to store the string associated with the entry
 * @param entry_ptr is a pointer referencing the entry we want to format
 */
void format_entry( char *const line, const line_entry* const entry_ptr) {
    line[0] = entry_ptr->spacer;
    line[1] = '0';
    line[2] = 'x';
    sprintf(&line[3],"%.2X",entry_ptr->value);
    line[5] = entry_ptr->spacer;
    line[6] = entry_ptr->separator; // could work as a string termination character
}

/**
 * This function is used the create a formatted line with all specified entries
 * 
 * @param[out] line is used to store the string associated with the entry
 * @param values is the array containing the values to be shown
 * @param size specifies the length of `values`
 */
void format_line( char *const line, const uint8_t *const values, const int size) {
    line_entry tmp_var;
    tmp_var.spacer = ' ';
    tmp_var.separator = '|';
    for( int i = 0; i < size; ++i ) {
        tmp_var.value = values[i]; 
        if( i == 0 ) tmp_var.separator = '|';
        else tmp_var.separator = ' ';
        if( i == size - 1 ) tmp_var.separator = '\0'; // here the separator is used to close the line with a string termination character
        format_entry(line + 7*i,&tmp_var);
    }
}

/**
 * This function is used to create a spacing line of the size associated to a series of entries
 *
 * @param[out] line is used to store the string associated with the entry
 * @param val is the character that will be repeated along the whole spacing line
 * @param entry_size is the size of the entries' array that the spacing line has to match
 */
void spacer_line( char *const line, const char val, const int entry_size)  {
    // here we use `entry_size*7 - 1` because in the function above we use `tmp_var.separator` as
    // a string termination character, thus it is not necessary to match after that
    for( int i = 0; i < entry_size*7 - 1; ++i ) { 
        line[i] = val; 
    }
    line[entry_size*7 - 1] = '\0';
}

/**
 * This function is used to create and **SHOW** the multiplicative table in base 16
 *
 * @param[out] line is used to store the string associated with the entry
 * @param size represent the number of lines that will be shown in the table
 */
void hex_table( char *const line, uint8_t size) {
    uint8_t tmp_values[16];
    spacer_line( line, '-' , 17 );
    PRINT_BUF(line);
    for( int i = 1; i <= size; ++i ) {
        tmp_values[0] = i; 
        for( int j = 1; j < 17; ++j) tmp_values[j] = j*tmp_values[0]; // Computes the multiplications from 0x01 (decimal for 1) to 0x0F (decimal for 15)
        format_line( line, tmp_values, 17 );
        PRINT_BUF(line);
    }
    spacer_line( line, '-', 17 );
    PRINT_BUF(line);
}
