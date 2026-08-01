// lib/led.c
#include "led.h"
#include "button.h"   // need this include to read is_holding, event_single_click...

#define BLINK_INTERVAL_MS   150
#define BLINK_BURST_TOGGLES 6

static uint8_t  burst_remaining = 0;
static uint32_t time_last_burst = 0;
static uint32_t time_last_blink = 0;
static uint8_t  was_holding     = 0;

void LED_Handle(void)
{
  // One Click
  if(event_single_click)
  {
    event_single_click = 0;
    HAL_GPIO_TogglePin(LEDY_GPIO_Port, LEDY_Pin);
  }

  // Double click
  if(event_double_click)
  {
    event_double_click = 0;
    burst_remaining = BLINK_BURST_TOGGLES;
    time_last_burst = HAL_GetTick();
  }
  if(burst_remaining > 0 &&  (HAL_GetTick()-time_last_burst) >= BLINK_INTERVAL_MS)
  {
    HAL_GPIO_TogglePin(LEDY_GPIO_Port, LEDY_Pin);
    time_last_burst = HAL_GetTick();
    burst_remaining--;
  }

  // Hold
  if(is_holding)
  {
    if((HAL_GetTick()-time_last_blink) >= BLINK_INTERVAL_MS)
    {
      HAL_GPIO_TogglePin(LEDY_GPIO_Port, LEDY_Pin);
      time_last_blink = HAL_GetTick();
    }
  }
  else if(was_holding)
  {
    HAL_GPIO_WritePin(LEDY_GPIO_Port, LEDY_Pin, GPIO_PIN_RESET);
  }
  was_holding = is_holding;
}
