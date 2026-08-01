// Core/Src/button.c
#include "button.h"

#define DEBOUNCE_MS            15
#define LONG_PRESS_MS          500
#define DOUBLE_CLICK_WINDOW_MS 400

static uint8_t  button_current   = 1;
static uint8_t  button_last      = 1;
static uint8_t  button_filter    = 1;
static uint8_t  is_debouncing    = 0;
static uint32_t time_debounce    = 0;
static uint32_t time_press_start = 0;
static uint8_t  click_count      = 0;
static uint32_t time_first_click = 0;

uint8_t is_holding       = 0;
uint8_t event_single_click = 0;
uint8_t event_double_click = 0;

void Button_Handle(void)
{
  // --- Debounce ---
  uint8_t button_state = HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin);
  if(button_state != button_filter)
  {
    button_filter = button_state;
    is_debouncing = 1;
    time_debounce = HAL_GetTick();
  }

  if(is_debouncing && (HAL_GetTick()-time_debounce) >= DEBOUNCE_MS)
  {
    button_current = button_filter;
    is_debouncing = 0;
  }

  // --- Click and Unclick ---
  if(button_current != button_last)
  {
    if(button_current == 0)
    {
      time_press_start = HAL_GetTick();
    }
    else if(is_holding) // Check if holding
    {
      is_holding = 0;
    }
    else // check if double click
    {
      if(click_count == 0)
      {
        click_count = 1;
        time_first_click = HAL_GetTick();
      }
      else
      {
        click_count = 0;
        event_double_click = 1;
      }
    }
    button_last = button_current;
  }

  // --- Holding ---
  if(button_current == 0 && !is_holding && (HAL_GetTick() - time_press_start >= LONG_PRESS_MS))
  {
    is_holding = 1;
    click_count = 0;
  }

  if(click_count == 1 && (HAL_GetTick() - time_first_click > DOUBLE_CLICK_WINDOW_MS))
  {
    click_count = 0;
    event_single_click = 1;
  }
}