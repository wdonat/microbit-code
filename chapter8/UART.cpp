#include "MicroBit.h"
#include "MicroBitSamples.h"
#include "MicroBitUARTService.h"
 
#ifdef MICROBIT_UART
 
MicroBit uBit;
MicroBitUARTService *uart;
int connected = 0;
 
void onConnected(MicroBitEvent e)
{
    uBit.display.scroll("C");
    connected = 1;
    ManagedString eom(":");
 
    while (1)
    {
        ManagedString msg = uart->readUntil(eom);
        uBit.display.scroll(msg);
    }
}
 
void onDisconnected(MicroBitEvent e)
{
    uBit.display.scroll("D");
    connected = 0;
}
 
void onButtonA(MicroBitEvent e)
{
    if (connected == 0)
    {
        uBit.display.scroll("NC");
        return;
    }
    uart->send("YES");
    uBit.display.scroll("YES");
}
 
void onButtonB(MicroBitEvent e)
{
    if (connected == 0)
    {
        uBit.display.scroll("NC");
        return;
    }
    uart->send("NO");
    uBit.display.scroll("NO");
}
 
void onButtonAB(MicroBitEvent e)
{
    if (connected == 0)
    {
        uBit.display.scroll("NC");
        return;
    }
    uart->send("GOT IT!");
    uBit.display.scroll("GOT IT!");
}
 
int main()
{
    uBit.init();
    uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_CONNECTED, onConnected);
    uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_DISCONNECTED, onDisconnected);
 
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonB);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_BUTTON_EVT_CLICK, onButtonAB);
 
    uart = new MicroBitUARTService(*uBit.ble, 32, 32);
    uBit.display.scroll("AVM");
 
    release_fiber();
}
 
#endif
