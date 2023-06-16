#define BLYNK_PRINT Serial
/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"
#define BLYNK_TEMPLATE_ID "TMPL637fTYdTx"
#define BLYNK_TEMPLATE_NAME "FarmSmart"
#define BLYNK_AUTH_TOKEN "cLs8YlvYV7NWK384DbG1K--Yay6HWpUH"
#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "cLs8YlvYV7NWK384DbG1K--Yay6HWpUH";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Gia Ky ";
char pass[] = "12345679";
#define led1 14 //D5
#define led2 12 //D6
#define led3 13 //D7
#define button1 5 //D1
#define button2 4 //D2
#define button3 0 //D3

unsigned long times = millis();
unsigned long timesDelay = millis();
WidgetLED led_connect(V0);
boolean updateState1 = 0;
boolean updateState2 = 0;
boolean updateState3 = 0;
BlynkTimer timer;


void setup() {
    Serial.begin(9600);
    
    delay(100);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    pinMode(A0, INPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);
    pinMode(button3, INPUT_PULLUP);
    attachInterrupt(button1, handleInterrup1, FALLING);
    attachInterrupt(button2, handleInterrup2, FALLING);
    attachInterrupt(button3, handleInterrup3, FALLING);
    Serial.println("---------------------Int--------------------");
}
void loop() {
    if (millis() - times > 1000) {
        Blynk.virtualWrite(V0, millis() / 1000);
        if (led_connect.getValue()) {
            led_connect.off();
        } else {
            led_connect.on();
        }
        times = millis();
    }
    if (updateState1 == 1) {
        Blynk.virtualWrite(V1, digitalRead(led1));
        updateState1 = 0;
    }
    if (updateState2 == 1) {
        Blynk.virtualWrite(V2, digitalRead(led2));
        updateState2 = 0;
    }
    if (updateState3 == 1) {
        Blynk.virtualWrite(V3, digitalRead(led3));
        updateState3 = 0;
    }
  timer.run();

}
BLYNK_CONNECTED() {
    // Request Blynk server to re-send latest values for all pins
    Blynk.syncAll();
}
BLYNK_WRITE(V1) {
    int p = param.asInt();
    digitalWrite(led1, p);
}
BLYNK_WRITE(V2) {
    int p = param.asInt();
    digitalWrite(led2, p);
}
BLYNK_WRITE(V3) {
    int p = param.asInt();
    digitalWrite(led3, p);
}
ICACHE_RAM_ATTR void handleInterrup1() {
    if (millis() - timesDelay > 200) {
        digitalWrite(led1, !digitalRead(led1));
        updateState1 = 1;
        timesDelay = millis();
    }
}
ICACHE_RAM_ATTR void handleInterrup2() {
    if (millis() - timesDelay > 200) {
        digitalWrite(led2, !digitalRead(led2));
        updateState2 = 1;
        timesDelay = millis();
    }
}
ICACHE_RAM_ATTR void handleInterrup3() {
    if (millis() - timesDelay > 200) {
        digitalWrite(led3, !digitalRead(led3));
        updateState3 = 1;
        timesDelay = millis();
    }
}
