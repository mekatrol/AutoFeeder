#include <Arduino.h>

#include "debounce.h"

void debounce_init(DebounceState *debounce_state, uint8_t pin_number, uint8_t inital_value)
{
    debounce_state->debounce_count = 0;
    debounce_state->pin_number = pin_number;
    debounce_state->previous_sample_value = inital_value;
    debounce_state->stable_value = inital_value;
}

uint8_t debounce(DebounceState *debounce_state)
{
    // Get the current value of the pin
    uint8_t pin_current_value = digitalRead(debounce_state->pin_number);

    // If the pin value is the same as the stable value then
    // just return 0 to indicate no change
    if (pin_current_value == debounce_state->stable_value)
    {
        // Reset count when state has not changed.
        debounce_state->debounce_count = 0;
        debounce_state->previous_sample_value = debounce_state->stable_value;

        // Return false to indicate that there has not been a pin stable value change
        return false;
    }

    // Create flag to indicate if the pin value has changed since last sample
    uint8_t value_has_changed_from_last_sample = pin_current_value != debounce_state->previous_sample_value;

    // Update the previous sample value to this sample value (for next debounce call)
    debounce_state->previous_sample_value = pin_current_value;

    // Did the value change since last sample?
    if (value_has_changed_from_last_sample)
    {
        // Reset the debounce counter as the value has changed from last sample
        debounce_state->debounce_count = 0;

        // Return false to indicate that there has not been a pin stable value change
        return false;
    }

    // Have we already reached the debounce count? If so nothing further to do
    if (debounce_state->debounce_count == DEBOUNCE_MIN_COUNT)
    {
        // Return false to indicate that there has not been a pin stable value change
        return false;
    }

    // Increment the debounce count
    debounce_state->debounce_count++;

    // Have we reached the debounce count?
    if (debounce_state->debounce_count < DEBOUNCE_MIN_COUNT)
    {
        // Return false to indicate that there has not been a pin stable value change
        return false;
    }

    // Update the stable value
    debounce_state->stable_value = pin_current_value;

    // Return true to indicate that there has been a pin stable value change
    return true;
}