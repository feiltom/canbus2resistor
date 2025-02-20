#include <Arduino.h>
#define CIRCULAR_BUFFER_INT_SAFE

#define STEERING_ID  0x3C4

#define DATA0_SRC    0b00000100 // 0x04
#define DATA0_NEXT   0b00010000 // 0x10
#define DATA0_PREV   0b00001000 // 0x08
#define DATA0_VOL_U  0b10000000 // 0x80
#define DATA0_VOL_D  0b01000000 // 0x40

#define DATA1_PHONE  0b10000000 // 0x80
#define DATA1_ESC    0b00001000 // 0x08
#define DATA1_WIN    0b01000000 // 0x40
#define DATA1_UP     0b00000010 // 0x02
#define DATA1_DOWN   0b00000001 // 0x01
#define DATA1_OK     0b00000100 // 0x04

#include <CircularBuffer.h>
CircularBuffer<int, 100> messages; // we will store a maximum of 100 messages

void setup() {                       
  setupCanBus();
  setupDigitalPot();
}

void loop() {
  writeToDigitalPot();
}
