#include "MicroBit.h"
#include "MicroBitSamples.h"
#include "MicroBitUARTService.h"
 
#ifdef MICROBIT_BUGGY
 
MicroBit uBit;
MicroBitUARTService *uart;
 
 
int pin0, pin8, pin12, pin16 = 0;
int connected = 0;
int drive = 0;
 
void moveBot(ManagedString message)
{
          ManagedString w("w");
          ManagedString space(" ");
          ManagedString a("a");
          ManagedString d("d");
          ManagedString s("s");
 
  if (message == w) // start moving
  {
    pin12 = 1;
    pin16 = 1;
    drive = 1;
  }
  else
  {
    if (message == space) // all stop
    {
      pin12 = 0;
      pin16 = 0;
      drive = 0;
    }
  }
 
  if (drive == 1)
  {
    if (message == a) // left
    {
      pin12 = 1;
      pin16 = 0;
    }
    else
    {
      if (message == d) // right
      {
        pin12 = 0;
        pin16 = 1;
      }
      else
      {
        if (message == s) // stop moving left or right
        {
          pin12 = 1;
          pin16 = 1;
        }
        else
        {
        }
      }
    }
  }
  uBit.io.P0.setDigitalValue(pin0);
  uBit.io.P8.setDigitalValue(pin8);
  uBit.io.P12.setDigitalValue(pin12);
  uBit.io.P16.setDigitalValue(pin16);
  return;
}
 
void onConnected(MicroBitEvent e)
{
    uBit.display.scroll("C");
    connected = 1;
 
    while(1)
    {
        ManagedString msg = uart->read(1);
        moveBot(msg);
    }
}
 
void onDisconnected(MicroBitEvent e)
{
    uBit.display.scroll("D");
    connected = 0;
}
 
int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();
 
    uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_CONNECTED, onConnected);
    uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_DISCONNECTED, onDisconnected);
    uart = new MicroBitUARTService(*uBit.ble, 32, 32);
    uBit.display.scroll("BUGGY!");
    // If main exits, there may still be other fibers running or registered event handlers etc.
    // Simply release this fiber, which will mean we enter the scheduler. Worse case, we then
    // sit in the idle task forever, in a power efficient sleep.
    release_fiber();
}
 
#endif
