// lib/exti_dispatcher.h
#ifndef EXTI_DISPATCHER_H
#define EXTI_DISPATCHER_H

#include "main.h"

// Function pointer type: any module that wants to receive EXTI interrupts
// must write a function with this exact signature (void, takes uint16_t GPIO_Pin).
typedef void (*EXTI_CallbackTypeDef)(uint16_t GPIO_Pin);

// Call once in main() (after MX_GPIO_Init) to register a callback for a pin.
void EXTI_Dispatcher_Register(uint16_t GPIO_Pin, EXTI_CallbackTypeDef callback);

// Called from HAL_GPIO_EXTI_Callback() in main.c - looks up the table and
// calls the callback registered for the pin that just fired, if any.
void EXTI_Dispatcher_Handle(uint16_t GPIO_Pin);

#endif
