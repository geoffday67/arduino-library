#pragma once

class Debouncer {
private:
  int (*pGetValue) (void);
  void (*pOnComplete) (int);
  unsigned long period;
  int current, previous;
  unsigned long changeTime;
  bool changing;

public:
  Debouncer (int (*pGetValue) (void), void (*pOnComplete) (int), int period);
  void loop();
};
