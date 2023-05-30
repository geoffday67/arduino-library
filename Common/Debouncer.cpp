#include <Arduino.h>
#include "Debouncer.h"

Debouncer::Debouncer (int (*pGetValue) (void), void (*pOnComplete) (int), int period) {
  this->pGetValue = pGetValue;
  this->pOnComplete = pOnComplete;
  this->period = period;
  current = pGetValue();
  changing = false;
}

void Debouncer::loop() {
  // Get the value now.
  int value = pGetValue();

  // Has a change begun?
  if (!changing) {
    // No, is the value different from the current value?
    if (value != current) {
      // Yes, record the time of change and flag that we're changing.
      changeTime = millis();
      changing = true;
      previous = value;
    }
    return;
  }

  // We're changing, has the value returned to the current value?
  if (value == current) {
    // Yes, we're no longer changing.
    changing = false;
    return;
  }

  // We're changing from current, is the value the same as previously?
  if (value == previous) {
    // Yes, is it long enough since the value changed?
    if (millis() - changeTime > period) {
      // Yes, update the current value and fire the event.
      changing = false;
      current = value;
      pOnComplete(current);
    }
    return;
  }

  // The value is different from previously but not the same as the current value, reset the change start time.
  changeTime = millis();
  previous = value;
}
