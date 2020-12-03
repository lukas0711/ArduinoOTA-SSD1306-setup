#include "OTAsetupSSD1306.h"

void OTAsetupSSD1306()
{
    // source: https://github.com/ThingPulse/esp8266-oled-ssd1306/blob/master/examples/SSD1306OTADemo/SSD1306OTADemo.ino
    // source: https://lastminuteengineers.com/esp8266-ota-updates-arduino-ide/
    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
            type = "sketch";
        else // U_SPIFFS
            type = "filesystem";
        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        Serial.println("Start updating " + type);

        display.clear();
        display.setFont(ArialMT_Plain_10);
        display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
        display.drawString(display.getWidth() / 2, display.getHeight() / 2 - 10, "OTA Update");
        display.display();
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
        display.drawProgressBar(4, 32, 120, 8, progress / (total / 100));
        display.display();
    });

    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
        display.clear();
        display.setFont(ArialMT_Plain_10);
        display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
        display.drawString(display.getWidth() / 2, display.getHeight() / 2, "Restart");
        display.display();
    });

    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        display.clear();
        display.setFont(ArialMT_Plain_10);
        display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
        String message;
        if (error == OTA_AUTH_ERROR)
            message = "Auth Failed";
        else if (error == OTA_BEGIN_ERROR)
            message = "Begin Failed";
        else if (error == OTA_CONNECT_ERROR)
            message = "Connect Failed";
        else if (error == OTA_RECEIVE_ERROR)
            message = "Receive Failed";
        else if (error == OTA_END_ERROR)
            message = "End Failed";
        Serial.println(message);
        display.drawString(display.getWidth() / 2, display.getHeight() / 2, message);
        display.display();
        delay(5000);
    });

    // Align text vertical/horizontal center
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    display.setFont(ArialMT_Plain_10);
    display.drawString(display.getWidth() / 2, display.getHeight() / 2, "Ready for OTA:\n" + WiFi.localIP().toString() + "\n" + ArduinoOTA.getHostname());
    display.display();
    delay(5000);
}
