# IoT_Task1_ColourSorter_26CE10055
Daksh Kashyap 26CE10055 ProDex task 1
Task 1: Length-Based Automatic Sorting System

**Student:** Daksh Kashyap  
**Roll number:** 26CE10055  
**Course:** Internet of Thing						                                                                                                        Project overview

This Arduino-based system sorts objects into small, medium, and large categories. An HC-SR04 ultrasonic sensor measures the gap beyond an object positioned against a fixed guide. The Arduino estimates the object’s length, stops the conveyor motor, moves a servo diverter, and reports the category and running counts in the Serial Monitor.
Components

- Arduino Uno R3
- HC-SR04 ultrasonic distance sensor
- L293D motor driver
- DC motor
- Micro servo

Main connections

- HC-SR04 TRIG → Arduino D8; ECHO → D9
- Servo signal → D10
- L293D enable 1-2 → D5; inputs 1A and 2A → D4 and D3
- L293D outputs 1Y and 2Y → DC motor
- L293D VCC1 and VCC2 → 5V in the Tinkercad simulation
- L293D 3-4EN → GND; all circuit grounds are connected

Further real-world applications

A length-based sorter can route parcels in a warehouse, grade produce by size, or separate manufactured parts that fall outside a target range. A real conveyor would need a calibrated measuring station that holds each item against a reference guide while it is measured. It should also use a separate motor power supply, a stable sensor mount, and an emergency stop.
