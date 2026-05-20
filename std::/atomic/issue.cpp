#include <iostream>
#include <iterator>

/* This is an without protection code
 */

bool dataReady = false;

void ISR() {
    dataReady = true;
}

int main() {
    
    if ( dataReady ) {
        /* process the data
         */
    }

}

/* ISSUES FACED HERE
 * - compiler optimization issue
 * - Race condition issue 
 *   if variable is bigger than CPU word ISR only writes halfaway only
 *   example: 32 bit on 8 bit MCU
 *   thus we get an corrupted value
 */
