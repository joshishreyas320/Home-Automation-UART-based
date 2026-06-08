// ============================================
// Bluetooth Home Automation - Arduino UNO
// HC-05 via Serial (Pin 0=RX, 1=TX)
// Relay 1 (Lamp)  -> Pin 13
// Relay 2 (Motor) -> Pin 12
// Relay 3 (LED)   -> Pin 7
// Active HIGH relay (2N2222 NPN driver)
// ============================================

// --- Pin Definitions ---
#define RELAY_LAMP   13   // RL1 -> Lamp (L1)
#define RELAY_MOTOR  12   // RL2 -> Motor
#define RELAY_LED     7   // RL3 -> LED Yellow (D5)

// --- State Tracking ---
bool lampState  = false;
bool motorState = false;
bool ledState   = false;

void setup() {
  // Relay control pins as OUTPUT
  pinMode(RELAY_LAMP,  OUTPUT);
  pinMode(RELAY_MOTOR, OUTPUT);
  pinMode(RELAY_LED,   OUTPUT);

  // All relays OFF initially
  digitalWrite(RELAY_LAMP,  LOW);
  digitalWrite(RELAY_MOTOR, LOW);
  digitalWrite(RELAY_LED,   LOW);

  // HC-05 communicates at 9600 baud via hardware Serial
  Serial.begin(9600);

  Serial.println("Bluetooth Home Automation Ready");
  Serial.println("Commands:");
  Serial.println("  1=Lamp ON   | 0=Lamp OFF  | T=Lamp Toggle");
  Serial.println("  2=Motor ON  | 3=Motor OFF | U=Motor Toggle");
  Serial.println("  4=LED ON    | 5=LED OFF   | V=LED Toggle");
  Serial.println("  A=ALL ON    | X=ALL OFF   | S=Status");
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    handleCommand(cmd);
  }
}

// -----------------------------------------------
void handleCommand(char cmd) {
  switch (cmd) {

    // --- LAMP (RL1) ---
    case '1':
      setRelay(RELAY_LAMP, true);
      lampState = true;
      Serial.println("Lamp -> ON");
      break;

    case '0':
      setRelay(RELAY_LAMP, false);
      lampState = false;
      Serial.println("Lamp -> OFF");
      break;

    case 'T': case 't':
      lampState = !lampState;
      setRelay(RELAY_LAMP, lampState);
      Serial.print("Lamp -> ");
      Serial.println(lampState ? "ON" : "OFF");
      break;

    // --- MOTOR (RL2) ---
    case '2':
      setRelay(RELAY_MOTOR, true);
      motorState = true;
      Serial.println("Motor -> ON");
      break;

    case '3':
      setRelay(RELAY_MOTOR, false);
      motorState = false;
      Serial.println("Motor -> OFF");
      break;

    case 'U': case 'u':
      motorState = !motorState;
      setRelay(RELAY_MOTOR, motorState);
      Serial.print("Motor -> ");
      Serial.println(motorState ? "ON" : "OFF");
      break;

    // --- LED (RL3) ---
    case '4':
      setRelay(RELAY_LED, true);
      ledState = true;
      Serial.println("LED -> ON");
      break;

    case '5':
      setRelay(RELAY_LED, false);
      ledState = false;
      Serial.println("LED -> OFF");
      break;

    case 'V': case 'v':
      ledState = !ledState;
      setRelay(RELAY_LED, ledState);
      Serial.print("LED -> ");
      Serial.println(ledState ? "ON" : "OFF");
      break;

    // --- ALL ON / ALL OFF ---
    case 'A': case 'a':
      setRelay(RELAY_LAMP,  true);
      setRelay(RELAY_MOTOR, true);
      setRelay(RELAY_LED,   true);
      lampState = motorState = ledState = true;
      Serial.println("ALL Devices -> ON");
      break;

    case 'X': case 'x':
      setRelay(RELAY_LAMP,  false);
      setRelay(RELAY_MOTOR, false);
      setRelay(RELAY_LED,   false);
      lampState = motorState = ledState = false;
      Serial.println("ALL Devices -> OFF");
      break;

    // --- STATUS ---
    case 'S': case 's':
      Serial.println("--- Device Status ---");
      Serial.print("Lamp  (Pin 13): "); Serial.println(lampState  ? "ON" : "OFF");
      Serial.print("Motor (Pin 12): "); Serial.println(motorState ? "ON" : "OFF");
      Serial.print("LED   (Pin  7): "); Serial.println(ledState   ? "ON" : "OFF");
      Serial.println("---------------------");
      break;

    // --- Ignore newline/carriage return ---
    case '\n': case '\r':
      break;

    default:
      Serial.print("Unknown command: ");
      Serial.println(cmd);
      break;
  }
}

// -----------------------------------------------
// setRelay: HIGH = transistor ON = relay energized
// -----------------------------------------------
void setRelay(int pin, bool state) {
  digitalWrite(pin, state ? HIGH : LOW);
}