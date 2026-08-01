// lib/exti_dispatcher.c
#include "exti_dispatcher.h"

#define EXTI_LINES_COUNT 16

// Table of 16 slots, one per EXTI line (pin number 0 to 15 of any port).
// All start as NULL (no module registered yet).
static EXTI_CallbackTypeDef callback_table[EXTI_LINES_COUNT] = {0};

// GPIO_Pin is a bitmask (GPIO_PIN_0 = 0x0001, GPIO_PIN_1 = 0x0002, ...
// GPIO_PIN_5 = 0x0020...). This function converts the bitmask into a 0..15 index for the table lookup.
static uint8_t Pin_To_Index(uint16_t GPIO_Pin)
{
  uint8_t index = 0;
  while (GPIO_Pin > 1)
  {
    GPIO_Pin >>= 1;
    index++;
  }
  return index;
}

void EXTI_Dispatcher_Register(uint16_t GPIO_Pin, EXTI_CallbackTypeDef callback)
{
  uint8_t index = Pin_To_Index(GPIO_Pin);
  callback_table[index] = callback;
}

void EXTI_Dispatcher_Handle(uint16_t GPIO_Pin)
{
  uint8_t index = Pin_To_Index(GPIO_Pin);
  if (callback_table[index] != 0)
  {
    callback_table[index](GPIO_Pin);
  }
}
