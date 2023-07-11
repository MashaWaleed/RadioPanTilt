#include <VirtualWire.h>
const int RF_RX_PIN = 11;
const int panPin = 9;   // Pin for pan servo
const int tiltPin = 10; // Pin for tilt servo

void setup() {
  Serial.begin(9600);  // Initialize the serial communication for debugging
  pinMode(panPin, OUTPUT);
  pinMode(tiltPin, OUTPUT);
  vw_set_rx_pin(RF_RX_PIN);  // Set the receive pin for VirtualWire
  vw_setup(2000);  // Set the transmission speed (in bits per second)
  vw_rx_start();  // Start the receiver
  
}

void loop() {
  uint8_t buffer[VW_MAX_MESSAGE_LEN];  // Create a buffer to store the received message
  uint8_t bufferSize = VW_MAX_MESSAGE_LEN;  // Set the buffer size
  
  if (vw_get_message(buffer, &bufferSize)) {  // Check if a message is received
    char receivedData[VW_MAX_MESSAGE_LEN];  // Create a buffer to store the received data as a string
    memcpy(receivedData, buffer, bufferSize);  // Copy the received message to the data buffer
    receivedData[bufferSize] = '\0';  // Null-terminate the data buffer to treat it as a string
    int panValue, tiltValue;
    sscanf(receivedData, "%d,%d", &panValue, &tiltValue);
    Serial.print("Pan: ");
    Serial.print(panValue);
    Serial.print(", Tilt: ");
    Serial.println(tiltValue);
    int panAngle = map(panValue, 0, 1023, 0, 180);
    int tiltAngle = map(tiltValue, 0, 1023, 0, 180);
//    analogWrite(panPin, angleToPWM(panAngle));
//    analogWrite(tiltPin, angleToPWM(tiltAngle));
    writeServoAngle(panPin, panAngle);
    writeServoAngle(tiltPin, tiltAngle);
    
  }
}

// Write servo angle to the specified pin
void writeServoAngle(int servoPin, int angle) {
  int pulseWidth = map(angle, 0, 180, 1000, 2000);  // Convert angle to pulse width
  digitalWrite(servoPin, HIGH);  // Set pin high
  delayMicroseconds(pulseWidth);  // Wait for the desired pulse width
  digitalWrite(servoPin, LOW);   // Set pin low
  delay(20);                      // Add a small delay between servo pulses
}
