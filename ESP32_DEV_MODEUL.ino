#include "BluetoothSerial.h"
#include <Adafruit_GFX.h>   
#include <P3RGB64x32MatrixPanel.h>

// Initialize the LED Matrix
P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 0, 15, 32, 33, 12, 5, 23, 4);

// Check for Bluetooth Config
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it
#endif

BluetoothSerial SerialBT;

void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32_LED_Control"); // Bluetooth Device Name
    Serial.println("ESP32 is ready. Pair via Bluetooth.");

    // Initialize the LED Matrix
    matrix.begin();
    matrix.fillScreen(0);
    matrix.setCursor(3, 8);
    matrix.setTextColor(matrix.colorHSV(7, 7, 7)); // White color
    matrix.print("Ready!");
}

void loop() {
    if (SerialBT.available()) {
        char receivedChar = SerialBT.read(); // Read incoming Bluetooth command
        Serial.printf("Received: %c\n", receivedChar);

        matrix.fillScreen(0); // Clear the LED matrix

        if (receivedChar == 'q') {
            matrix.setCursor(3, 8);
            matrix.print("1"); // Display 1
        } else if (receivedChar == 'w') {
            matrix.setCursor(3, 8);
            matrix.print("2"); // Display 2
        } else if (receivedChar == 'e') {
            matrix.setCursor(3, 8);
            matrix.print("3"); // Display 3
        } else {
            matrix.setCursor(3, 8);
            matrix.print("Invalid"); // Display invalid command
        }
    }

    delay(100); // Add delay to stabilize the loop
}
