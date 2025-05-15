#define TRIG_PIN 9
#define ECHO_PIN 10
#define MOTOR_PIN 7
int rainPin = A0;
int thresholdValue = 800;
float criticalValue = 200.0; // Critical tank value in cm

void setup() {
    Serial.begin(9600);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(rainPin, INPUT);
    pinMode(MOTOR_PIN, OUTPUT);
}

void loop() {
    // Ultrasonic sensor section
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH);
    float distanceToWater = duration * 0.034 / 2;
    float waterLevel = criticalValue - distanceToWater; // Calculate the water level
    Serial.print("Distance to Water: ");
    Serial.print(distanceToWater);
    Serial.println(" cm");
    Serial.print("Water Level: ");
    Serial.print(waterLevel);
    Serial.println(" cm");

    // Check the water level
    if (distanceToWater > 50.0) {
        Serial.println("Water level is low. Turning on the motor.");
        digitalWrite(MOTOR_PIN, HIGH); // Turn on the motor to fill the tank
    } else {
        Serial.println("Water level is sufficient.");
        digitalWrite(MOTOR_PIN, LOW); // Turn off the motor
    }
    
    // Rain sensor section
    int sensorValue = analogRead(rainPin);
    Serial.print("Moisture Sensor Value: ");
    Serial.print(sensorValue);
    if (sensorValue < thresholdValue) {
        Serial.println(" - Doesn't need watering");
    } else {
        Serial.println(" - Time to water your plant");
    }
    
    // Delay to avoid flooding the serial monitor
    delay(500);
}
