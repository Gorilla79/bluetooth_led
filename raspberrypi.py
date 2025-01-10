import bluetooth
import sys

# ESP32 Bluetooth device name
ESP32_NAME = "ESP32_LED_Control"

def find_esp32():
    """Search for the ESP32 device via Bluetooth."""
    print("Searching for ESP32 device...")
    nearby_devices = bluetooth.discover_devices(duration=8, lookup_names=True)
    for addr, name in nearby_devices:
        if ESP32_NAME in name:
            print(f"Found ESP32 at {addr}")
            return addr
    print("ESP32 not found.")
    sys.exit(1)

def main():
    esp32_address = find_esp32()

    # Create a Bluetooth socket and connect to ESP32
    sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    sock.connect((esp32_address, 1))
    print("Connected to ESP32. Press 'q', 'w', or 'e' to control the LED board. Press Ctrl+C to exit.")

    try:
        while True:
            # Get user input
            key = input("Enter command (q/w/e): ").strip()
            if key in ['q', 'w', 'e']:
                sock.send(key)  # Send command to ESP32
                print(f"Sent: {key}")
            else:
                print("Invalid command. Use 'q', 'w', or 'e'.")
    except KeyboardInterrupt:
        print("\nExiting program.")
    finally:
        sock.close()

if __name__ == "__main__":
    main()
