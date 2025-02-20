#include <can.h>
#include <mcp2515.h> // import this library from https://github.com/autowp/arduino-mcp2515

struct can_frame canMsg; 
MCP2515 mcp2515(10); // SPI CS Pin 10 

void irqHandler() {
  readCanBusMessage();
}

void setupCanBus() {
  SPI.begin();  
  
  mcp2515.reset();                          
  mcp2515.setBitrate(CAN_50KBPS,MCP_8MHZ); 
  
  // Filter out all messages except for the steering wheel controlls
  mcp2515.setFilterMask(MCP2515::MASK0, false, 0xfff);
  mcp2515.setFilter(MCP2515::RXF0, false, STEERING_ID);
  mcp2515.setFilterMask(MCP2515::MASK1, false, 0xfff);
  mcp2515.setFilter(MCP2515::RXF2, false, STEERING_ID);
  
  mcp2515.setNormalMode();

  attachInterrupt(0, irqHandler, FALLING);
}

void readCanBusMessage() {
  uint8_t irq = mcp2515.getInterrupts();

  if (irq & MCP2515::CANINTF_RX0IF) {
    if (mcp2515.readMessage(MCP2515::RXB0, &canMsg) == MCP2515::ERROR_OK) {
      handleMessageData(canMsg.data[0], canMsg.data[1]);
    }
  }

  if (irq & MCP2515::CANINTF_RX1IF) {
    if (mcp2515.readMessage(MCP2515::RXB1, &canMsg) == MCP2515::ERROR_OK) {
      handleMessageData(canMsg.data[0], canMsg.data[1]);
    }
  }
}

void handleMessageData(int data0, int data1) {
  if (data0 & DATA0_SRC)   { messages.push(55); }
  if (data0 & DATA0_NEXT)  { messages.push(45); }
  if (data0 & DATA0_PREV)  { messages.push(30); }
  if (data0 & DATA0_VOL_U) { messages.push(25); }
  if (data0 & DATA0_VOL_D) { messages.push(20); }

  if (data1 & DATA1_PHONE) { messages.push(18); }
  if (data1 & DATA1_ESC)   { messages.push(16); }
  if (data1 & DATA1_WIN)   { messages.push(14); }
  if (data1 & DATA1_UP)    { messages.push(12); }
  if (data1 & DATA1_DOWN)  { messages.push(10); }
  if (data1 & DATA1_OK)    { messages.push(7); }
}
