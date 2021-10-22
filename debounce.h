#ifndef __DEBOUNCE_H__
#define __DEBOUNCE_H__

#ifndef DEBOUNCE_MIN_COUNT
#define DEBOUNCE_MIN_COUNT 10
#endif // DEBOUNCE_MIN_COUNT

struct DebounceState
{
    uint8_t stable_value;
    uint8_t previous_sample_value;
    uint8_t debounce_count;
    uint8_t pin_number;
};

/**
 * Initialise the debounce state to a known starting state.
 */
void debounce_init(DebounceState *debounce_state, uint8_t pin_number, uint8_t inital_value);

/**
 * Debounces a digit input to reduce 'bounce' that occurs when a switch changes state.
 *
 * debounceCount  - The current debounce counter value for the number of samples
 *                  that the pin has been at the current stable value. Incremented each
 *                  call to this function if the value remains stable. Reset to zero
 *                  if the current pin value
 *
 * pinStableValue - The current stable value for the pin. Will be changed to a new value
 *                  if the debounceCount value reaches the DEBOUNCE_MIN_COUNT with
 *                  a consistent read value.
 *
 * pinNumber      - The pin number to sample.
 */
uint8_t debounce(DebounceState *debounce_state);

#endif // __DEBOUNCE_H__