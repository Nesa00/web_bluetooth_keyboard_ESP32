# web_bluetooth_keyboard_ESP32
## This is Bluetooth keyboard that was controlled using local webpage. Code was created and tested for ESP32.
### Instructions for run
 In **privatedata.h** you need to replace **value** string with actual data\
 example: const char WIFI_SSID[] PROGMEM = R"=====(My_home_wifi_name)=====";

 Most important thing was:/
 BleKeyboard library was so big that requre more space, using default settings you cannot upload your code to the ESP, so
 during uploading of this code to your ESP you need to select partition scheme -> No OTA(2MB APP/2MB SPIFFS)

### Look on the webpage:
![Picture](https://github.com/Nesa00/web_bluetooth_keyboard_ESP32/blob/main/web_keyboard.PNG)
