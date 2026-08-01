# STM32F446RE — Teaching Projects

A collection of small, progressively-harder STM32 embedded projects built on the **Nucleo-F446RE** board, developed as teaching material for RPTU to introduce students to bare-metal / HAL-based STM32 programming with STM32CubeIDE.

Each project is self-contained: its own STM32CubeIDE project (`.project`/`.cproject`/`.ioc`), its own wiring diagram, and its own `README.md` explaining what it teaches and why it's built the way it is. Start at project 1 and work forward — each one reuses a concept from the previous one.

## Hardware

- **Board:** ST Nucleo-F446RE (STM32F446RETx, Cortex-M4)
- **IDE:** STM32CubeIDE (GCC / make toolchain — not Keil/IAR)

## Projects

| # | Project | Teaches |
|---|---|---|
| 1 | [1_Blink_LED](1_Blink_LED) | Non-blocking timing with `HAL_GetTick()` — two LEDs blinking at independent rates without `HAL_Delay()` blocking either one |
| 2 | [2_Button](2_Button) | Polling a button: mechanical debounce, single click, double click, long-press — all as a non-blocking state machine |
| 3.1 | [3_1_Button_Interupt](3_1_Button_Interupt) | Same button logic, but edge-detected via **EXTI interrupt**, restructured into a modular `lib/` with a reusable interrupt dispatcher (for when more than one interrupt source is needed) |
| 3.2 | [3_2_Button_Interrupt](3_2_Button_Interrupt) | Same interrupt-driven button logic, built **step by step in a single file** — the recommended path for walking a student through the reasoning, stage by stage, before showing them the modular version in 3.1 |
| 5.1 | [5_1_ADC_LED](5_1_ADC_LED) | True single-channel ADC (not the sequential-polling trick some sample code uses) read from a potentiometer, driving an LED's brightness through timer PWM |

## Folder structure (general)

```
STM32_F446RE/
├── README.md                    - this file
├── 1_Blink_LED/                 - project 1 (see table above)
├── 2_Button/                    - project 2
├── 3_1_Button_Interupt/         - project 3.1
└── 3_2_Button_Interrupt/        - project 3.2

# each numbered project folder follows the same internal layout:
<project>/
├── Core/Src, Core/Inc           - CubeMX-generated HAL init code + application code
├── Drivers/                     - STM32 HAL + CMSIS (generated, not hand-edited)
├── lib/                         - hand-written application modules, where present
├── <name>.ioc                   - CubeMX pin/clock configuration (open with STM32CubeIDE)
├── README.md                    - what this project teaches, pin mapping, wiring diagram
└── wiring_diagram.svg           - how to physically wire the breadboard for this project
```
