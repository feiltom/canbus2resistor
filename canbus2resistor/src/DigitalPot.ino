#include <X9C.h> // import library from https://github.com/philbowles/Arduino-X9C
#define CS  9
#define UD  8                          
#define INC 7

X9C pot;

void setupDigitalPot() {
  pot.begin(CS, INC, UD);
  pot.setPotMin(true);
}

void writeToDigitalPot() {
  if (messages.isEmpty()) return;
  quickSetPotValue(messages.pop());
}

void quickSetPotValue(int value) {
  // timing is really important
  pot.setPot(99-value, false);
  delay(240);
  pot.setPotMin(false);
  delay(240);
}
