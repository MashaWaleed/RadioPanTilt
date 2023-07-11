#include <VirtualWire.h>
const int RF_TX_PIN = 12;

void setup() {
  Serial.begin(9600);  // Initialize the serial communication for debugging
  
  vw_set_tx_pin(RF_TX_PIN);  // Set the transmit pin for VirtualWire
  vw_setup(2000);  // Set the transmission speed (in bits per second)
}
void loop() {
  int joystickX = analogRead(A0);  // Read the X-axis value from the joystick
  int joystickY = analogRead(A1);  // Read the Y-axis value from the joystick
  
  char buffer[16];  // Create a buffer to store the values as a string
  sprintf(buffer, "%d,%d", joystickX, joystickY);  // Format the values as a comma-separated string
  
  vw_send((uint8_t*)buffer, strlen(buffer));  // Send the values via VirtualWire
  vw_wait_tx();  // Wait for the transmission to complete
  
  Serial.println(buffer);  // Print the values to the serial monitor for debugging
  
  delay(100);  // Adjust the delay as needed
}
