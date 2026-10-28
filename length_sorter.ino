#include <Servo.h>

const byte TRIG_PIN = 8;
const byte ECHO_PIN = 9;

const byte SERVO_PIN = 10;

const byte MOTOR_ENABLE = 5;
const byte MOTOR_IN1 = 4;
const byte MOTOR_IN2 = 3;

const float BASELINE_CM = 30 
CT_DETECT_CM = 29.0;

const float SMALL_MAX_CM = 8.0;
const float MEDIUM_MAX_CM = 16.0;

const int SERVO_REST = 10;
const int SERVO_SMALL = 45;
const int SERVO_MEDIUM = 90;
const int SERVO_LARGE = 135;

Servo diverter;

unsigned int smallCount = 0;
unsigned int mediumCount = 0;
unsigned int largeCount = 0;

bool waitingForObjectToClear = false;

float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(3);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);

  if (duration == 0) {
    return BASELINE_CM + 1.0;
  }

  return duration * 0.0343 / 2.0;
}

void conveyorOn() {
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENABLE, 160);
}

void conveyorOff() {
  analogWrite(MOTOR_ENABLE, 0);
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(MOTOR_ENABLE, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);

  diverter.attach(SERVO_PIN);
  diverter.write(SERVO_REST);

  Serial.begin(9600);
  Serial.println("Length-based object sorter ready.");
  Serial.println("Place an object against the fixed guide.");

  conveyorOn();
}

void loop() {
  float gapCm = readDistanceCm();

  if (!waitingForObjectToClear && gapCm < OBJECT_DETECT_CM) {
    conveyorOff();
    delay(200); 
    gapCm = readDistanceCm();
    float lengthCm = BASELINE_CM - gapCm;

    if (lengthCm < 0) {
      lengthCm = 0;
    }

    Serial.print("Measured length: ");
    Serial.print(lengthCm, 1);
    Serial.println(" cm");

    if (lengthCm < SMALL_MAX_CM) {
      smallCount++;
      diverter.write(SERVO_SMALL);
      Serial.println("Sorted: SMALL");
    } else if (lengthCm < MEDIUM_MAX_CM) {
      mediumCount++;
      diverter.write(SERVO_MEDIUM);
      Serial.println("Sorted: MEDIUM");
    } else {
      largeCount++;
      diverter.write(SERVO_LARGE);
      Serial.println("Sorted: LARGE");
    }

    Serial.print("Counts - Small: ");
    Serial.print(smallCount);
    Serial.print(" | Medium: ");
    Serial.print(mediumCount);
    Serial.print(" | Large: ");
    Serial.println(largeCount);

    waitingForObjectToClear = true;
  }

  if (waitingForObjectToClear && gapCm >= OBJECT_DETECT_CM) {
    diverter.write(SERVO_REST);
    waitingForObjectToClear = false;
    conveyorOn();
  }

  delay(100);
}
