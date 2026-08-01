// lib/button.h
#ifndef BUTTON_H
#define BUTTON_H

#include "main.h"

extern uint8_t is_holding;
extern uint8_t event_single_click;
extern uint8_t event_double_click;

void Button_Handle(void);
void Button_EXTI_Callback(uint16_t GPIO_Pin);

#endif
