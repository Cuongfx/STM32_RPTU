# 5.1 — ADC Single Channel + PWM LED (potentiometer → brightness)

**Board:** Nucleo-F446RE (STM32F446RETx)
**IDE:** STM32CubeIDE (GCC / make)

## What this project is about

A 10kΩ potentiometer is read on a single ADC channel, and its value directly controls the brightness of an LED through PWM — turn the knob, the LED dims or brightens in real time. This is the first project in the repository combining two peripherals: **ADC** (reading an analog voltage) and **timer PWM** (generating an analog-like output).

## CubeMX setup & code generation

1. `File → New → STM32 Project` → Board Selector → **NUCLEO-F446RE** → Next → finish the wizard.
2. Click pin **PA0** → set it to `ADC1_IN0`.
3. **Analog → ADC1** tab: tick only `IN0` (single channel, no Scan Mode). Parameter Settings: **Resolution** = `12-bit`, **Data Alignment** = `Right Alignment`, **Continuous Conversion Mode** = `Disabled`, **Sampling Time** (channel 0) = `56 Cycles`.
4. Click pin **PA1** → set it to `TIM2_CH2`.
5. **Timers → TIM2** tab → **Channel2** = `PWM Generation CH2`. Parameter Settings: **Prescaler** = `89`, **Counter Period (ARR)** = `999`, **Pulse** = `0`.
6. **Project Manager → Project** → Toolchain / IDE = `STM32CubeIDE` (generating with the wrong toolchain, e.g. EWARM/IAR, produces a project STM32CubeIDE's Import wizard can't see — no `.project`/`.cproject`).
7. **Project Manager → Code Generator** → **`Copy only the necessary library files`** (not "Copy all used libraries files" — that pulls in unrelated CMSIS submodules like RTOS2/NN/DSP that fail to compile since their supporting middleware isn't generated).
8. **GENERATE CODE**.

## How the ADC read works

The ADC is configured for **single conversion mode** (`ContinuousConvMode = DISABLE`), so every reading needs an explicit start/poll/stop cycle — the pattern repeats every loop iteration:

```c
HAL_ADC_Start(&hadc1);
HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);   // blocks until EOC flag is set
adc_raw = HAL_ADC_GetValue(&hadc1);                  // read the DR register, 0-4095 (12-bit)
HAL_ADC_Stop(&hadc1);
```

`HAL_ADC_PollForConversion` blocks the CPU while the ADC hardware samples and converts — this is fine here since a single conversion takes only a few microseconds and the loop has nothing else time-critical to do.

## How the PWM output works

TIM2 channel 2 is configured once at startup (not re-started every loop):

```c
HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);   // called once, before while(1)
```

With `Prescaler = 89` and `Period (ARR) = 999`, the timer clock (90MHz APB1 timer clock ÷ 90) produces a 1kHz PWM signal. Every loop iteration just rewrites the compare register — the timer keeps outputting the PWM signal in hardware, no CPU polling needed for the output side:

```c
duty = adc_raw * 999 / 4095;                          // map 0-4095 -> 0-999
__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, duty);    // writes TIM2->CCR2 directly
```

## Pin mapping

| Signal | Pin | Notes |
|---|---|---|
| Potentiometer wiper | PA0 (Arduino header **A0**), `ADC1_IN0` | Analog input, 12-bit, single channel, software-triggered |
| LEDY (PWM) | PA1 (Arduino header **A1**), `TIM2_CH2` | Alternate function output, 1kHz PWM |

## Wiring diagram

![Wiring diagram](wiring_diagram.svg)

- Potentiometer (10kΩ linear, marked **B103**): outer pins to `3V3` and `GND` (either way round works — reversing them just flips which direction feels like "increase"), wiper (middle pin) to `PA0`.
- LEDY: `PA1` → resistor (~330Ω) → LED anode, LED cathode → `GND`.

## Debugging with Live Expressions

`adc_raw` (and `duty`) are inspected live during a debug session using CubeIDE's **Live Expressions** view, which polls a global/static variable's value over SWD while the target keeps running (no breakpoint needed):

1. Start a debug session, open `Window → Show View → Live Expressions`.
2. Add `adc_raw` (and `duty`) as an expression.
3. Toggle **Enable Live Watch** on the view's toolbar, then **Resume** the target.

## Folder structure

```
5_1_ADC_LED/
├── Core/Src/main.c   - MX_ADC1_Init, MX_TIM2_Init, while(1) loop reading ADC and writing PWM compare
├── 5_1_ADC_LED.ioc    - CubeMX project (ADC1 IN0 single channel, TIM2 CH2 PWM, Toolchain: STM32CubeIDE)
└── wiring_diagram.svg
```
