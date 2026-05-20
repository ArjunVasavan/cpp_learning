#include <atomic>

std::atomic<bool> dataReady{false};

/* NOTE: ATOMIC
 * - No cache issue
 *   every read and write goes to acutual memory
 * - No partial read and write
 *   operations  are atiomic
 * - No Race conditions
 */

void ISR() {
    dataReady.store(true);
}

int main() {

    if ( dataReady.load()) {
        //process data
        dataReady.store(false);
    }

    /* We are telling compiler donot optimise it this can change anytime
     * we can use for modern embedded systems only 
     * we cannot use it on small Like PIC and AVR
     */
}
