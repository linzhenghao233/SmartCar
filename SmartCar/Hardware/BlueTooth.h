#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

void BlueTooth_Init(void);
void BlueTooth_SendByte(uint8_t Byte);
void BlueTooth_SendNumber(uint32_t Number, uint8_t Length);

#endif
