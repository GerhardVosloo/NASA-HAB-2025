#define pin 33

volatile unsigned int count = 0;

const int interval = 1000;
long lastTime = 0;

void IRAM_ATTR incrementCount() { // IRAM_ATTR stores function in IRAM for super fast access
  count++;
}

void setup() {
  Serial.begin(115200);
  pinMode(pin, INPUT);
  attachInterrupt( // (pin, function, mode)
    //digitalPinToInterrupt(pin), // which pin to watch
    pin,
    incrementCount, // function called automatically upon interrupt trigger
    RISING // from LOW to HIGH
  );
}

void loop() {
  unsigned long time = millis();

  if (time - lastTime >= interval) {
    noInterrupts(); // stops interrupts
    int counts = count;
    count = 0;
    interrupts(); // reenables interrupts

    Serial.printf("CPS: %lu\n", counts);

    lastTime = time;
  }
}