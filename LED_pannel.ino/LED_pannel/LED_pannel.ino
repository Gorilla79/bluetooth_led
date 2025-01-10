#include <Adafruit_GFX.h>
#include <P3RGB64x32MatrixPanel.h>
#include "esp_task_wdt.h"

// LED matrix configuration
P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 0, 15, 32, 33, 12, 5, 23, 4);

// Constants
#define MAX_INPUT_LENGTH 64 // Maximum input string length
#define WATCHDOG_TIMEOUT 10 // Watchdog timeout in seconds

// Variables
char InputString[MAX_INPUT_LENGTH] = ""; // Input buffer
int inputIndex = 0;                      // Current position in the input buffer
bool newInputReceived = false;           // Flag for new input

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize LED matrix
  matrix.begin();
  matrix.fillScreen(0); // Clear the screen

  // Initialize watchdog timer
  esp_task_wdt_init(WATCHDOG_TIMEOUT, false); // Set timeout and disable panic
  esp_task_wdt_add(NULL);                     // Add the main task to WDT monitoring
}

void loop() {
  esp_task_wdt_reset(); // Reset the watchdog timer

  // Check for serial data
  if (Serial.available()) {
    char c = Serial.read(); // Read one character from the serial input
    esp_task_wdt_reset();   // Reset watchdog during input processing

    if (c == '\n') {        // If newline character is received
      InputString[inputIndex] = '\0'; // Null-terminate the string

      // Clear the screen and display the received string
      matrix.fillScreen(0);
      matrix.setCursor(15, 10);
      matrix.print(InputString);

      // Reset input buffer and flag
      inputIndex = 0;
      newInputReceived = true;
    } else if (inputIndex < MAX_INPUT_LENGTH - 1) {
      InputString[inputIndex++] = c; // Add character to buffer
    } else {
      // Handle buffer overflow
      Serial.println("Error: Input too long!");
      inputIndex = 0; // Reset the buffer
    }
  }

  // Add a small delay to avoid continuous CPU usage
  delay(1);
}