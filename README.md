
# web_bluetooth_keyboard_ESP32

A Bluetooth keyboard controlled through a local web interface. 
Code was created and tested for **ESP32**.

---

## Setup Instructions

### 1. Configure Wi‑Fi Credentials
Open **privatedata.h** and replace the placeholder `value` string with your actual Wi‑Fi information.

Example:
```cpp
const char WIFI_SSID[] PROGMEM = R"=====(My_home_wifi_name)=====";
```

---

## Important Note About Partition Scheme
The **BleKeyboard** library is large and requires more flash memory than the default ESP32 settings provide.

When uploading the program, select:
**Partition Scheme → No OTA (2MB APP / 2MB SPIFFS)**

This ensures enough space for BleKeyboard and your application.

---

## Security Warning
This project exposes a **local webpage that can control a Bluetooth keyboard**, which means:
- Anyone with access to the webpage could send keystrokes to the paired device.
- If your Wi‑Fi network is not secured, unauthorized users may gain access.
- This can pose a potential **security risk**, including unwanted input or system control.

### Recommended Safety Measures
- Use a **secure Wi‑Fi network** with a strong password.
- Do **not** expose the webpage to public networks.
- Consider adding **basic authentication** to the web interface.
- Disconnect power when the device should not be active.

Use this device responsibly.

---

## Summary
- Edit `privatedata.h` with your real Wi‑Fi details.
- Change the ESP32 partition scheme before uploading.
- Be aware of security implications—anyone who accesses the webpage may control the keyboard.

