#include "debounce.h"
#include "pins.h"

DebounceState sensor1_debounce_state;
DebounceState sensor2_debounce_state;

void setup()
{
    // Set up inputs (sensors & switches)
    pinMode(SENSOR1, INPUT);
    pinMode(SENSOR2, INPUT);
    pinMode(SENSOR3, INPUT);
    pinMode(SENSOR4, INPUT);

    // Set up outputs (LED & )
    pinMode(LED_PIN, OUTPUT);

    pinMode(X_STEP_PIN, OUTPUT);
    pinMode(X_DIR_PIN, OUTPUT);
    pinMode(X_ENABLE_PIN, OUTPUT);

    pinMode(Y_STEP_PIN, OUTPUT);
    pinMode(Y_DIR_PIN, OUTPUT);
    pinMode(Y_ENABLE_PIN, OUTPUT);

    pinMode(Z_STEP_PIN, OUTPUT);
    pinMode(Z_DIR_PIN, OUTPUT);
    pinMode(Z_ENABLE_PIN, OUTPUT);

    digitalWrite(X_ENABLE_PIN, LOW);
    digitalWrite(Y_ENABLE_PIN, LOW);
    digitalWrite(Z_ENABLE_PIN, LOW);

    debounce_init(&sensor1_debounce_state, SENSOR1, 0);
    debounce_init(&sensor2_debounce_state, SENSOR2, 0);
}

unsigned long previous_sensor_sample_millis = 0;

void loop()
{
    unsigned long now_millis = millis();

    // Sample sensors about every 10 milliseconds
    if (now_millis - previous_sensor_sample_millis >= 10)
    {
        previous_sensor_sample_millis = now_millis;

        debounce(&sensor1_debounce_state);
        debounce(&sensor2_debounce_state);
    }

    if (sensor1_debounce_state.stable_value)
    {
        if (now_millis % 10000 < 500)
            digitalWrite(LED_PIN, HIGH);
        else
            digitalWrite(LED_PIN, LOW);

        if (now_millis % 10000 < 500)
        {
            digitalWrite(X_DIR_PIN, HIGH);
            digitalWrite(Y_DIR_PIN, HIGH);
            digitalWrite(Z_DIR_PIN, HIGH);
        }
        else
        {
            digitalWrite(X_DIR_PIN, LOW);
            digitalWrite(Y_DIR_PIN, LOW);
            digitalWrite(Z_DIR_PIN, LOW);
        }

        digitalWrite(X_STEP_PIN, HIGH);
        digitalWrite(Y_STEP_PIN, HIGH);
        digitalWrite(Z_STEP_PIN, HIGH);
        delay(1);
        digitalWrite(X_STEP_PIN, LOW);
        digitalWrite(Y_STEP_PIN, LOW);
        digitalWrite(Z_STEP_PIN, LOW);
    }
}
