#include <xc.h>

void InitGPIO() {
    TRISC=0xFF;
    TRISAbits.TRISA2=1;
}
