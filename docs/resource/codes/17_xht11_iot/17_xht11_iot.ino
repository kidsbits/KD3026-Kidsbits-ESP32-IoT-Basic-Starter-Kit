/*  
  Project name: 17_xht11_iot
  Function: Remote monitoring of temperature and humidity data
  Author: keyestudio    
  Hardware connection:  
    - Connect to port 4
  Library:  
    - SimpleTimer.h 
  Develop software version:  
    - It is recommended to use the same software version as the one used at the time of development to avoid incompatibility
    - Arduino IDE 2.3.3
    - ESP32 2.0.12
  Cautions:  
    - Make sure you are connected to the correct interface   
    - Before uploading test code, please correctly connect to the development board and port
    - Set ESP32 Tools -> Partition Scheme:"RainMaker"
*/
#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"
#include <DHT.h>
#include <SimpleTimer.h>

SimpleTimer Timer;

//Define the XHT11 read data at pin IO27
#define xht11_Pin 27
DHT dht(xht11_Pin, DHT11);

static uint8_t gpio_reset = 0;  // Press BOOT to reset WiFi Details

// define the Node Name
char nodeName[] = "Keyes_ESP32_SmartHome";

//Here you can modify the name and key of the Bluetooth you want
const char *service_name = "keyestudio";
const char *pop = "keyes123";

// define the Chip Id
uint32_t espChipId = 5;

float temperature1 = 0;
float humidity1 = 0;

static TemperatureSensor temperature("Temperature");
static TemperatureSensor humidity("Humidity");

void sysProvEvent(arduino_event_t *sys_event) {
  switch (sys_event->event_id) {
    case ARDUINO_EVENT_PROV_START:
#if CONFIG_IDF_TARGET_ESP32
      Serial.printf("\nProvisioning Started with name \"%s\" and PoP \"%s\" on BLE\n", service_name, pop);
      printQR(service_name, pop, "ble");
#else
      Serial.printf("\nProvisioning Started with name \"%s\" and PoP \"%s\" on SoftAP\n", service_name, pop);
      printQR(service_name, pop, "softap");
#endif
      break;
    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
      Serial.printf("\nConnected to Wi-Fi!\n");
      break;
  }
}

void readSensor() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();  // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  } else {
    humidity1 = h;
    temperature1 = t;
  }
}

void sendSensor() {
  readSensor();
  temperature.updateAndReportParam("Temperature", temperature1);
  humidity.updateAndReportParam("Temperature", humidity1);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(gpio_reset, INPUT);

  dht.begin();  // Enabling DHT sensor

  Node my_node;
  my_node = RMaker.initNode(nodeName);

  my_node.addDevice(temperature);
  my_node.addDevice(humidity);

  Timer.setInterval(30000);  //send Data after every 30 seconds
  delay(1000);

  //This is optional
  RMaker.enableOTA(OTA_USING_PARAMS);
  //If you want to enable scheduling, set time zone for your region using setTimeZone().
  //The list of available values are provided here https://rainmaker.espressif.com/docs/time-service.html
  //RMaker.setTimeZone("Asia/Shanghai");
  // Alternatively, enable the Timezone service and let the phone apps set the appropriate timezone
  RMaker.enableTZService();
  RMaker.enableSchedule();

  Serial.printf("\nStarting ESP-RainMaker\n");
  RMaker.start();



  WiFi.onEvent(sysProvEvent);
#if CONFIG_IDF_TARGET_ESP32
  WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name);
#else
  WiFiProv.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, pop, service_name);
#endif
}

void loop() {
  // put your main code here, to run repeatedly:
  // Read GPIO0 (external button to reset device
  if (digitalRead(gpio_reset) == LOW) {  //Push button pressed
    Serial.printf("Reset Button Pressed!\n");
    // Key debounce handling
    delay(100);
    int startTime = millis();
    while (digitalRead(gpio_reset) == LOW) delay(50);
    int endTime = millis();

    if ((endTime - startTime) > 10000) {
      // If key pressed for more than 10secs, reset all
      Serial.printf("Reset to factory.\n");
      RMakerFactoryReset(2);
    } else if ((endTime - startTime) > 3000) {
      Serial.printf("Reset Wi-Fi.\n");
      // If key pressed for more than 3secs, but less than 10, reset Wi-Fi
      RMakerWiFiReset(2);
    }
  }
  delay(100);

  if (WiFi.status() == WL_CONNECTED) {
    //Serial.println("WiFi Connected");
    if (Timer.isReady()) {
      Serial.println("Sending Sensor Data");
      sendSensor();
      Timer.reset();  // Reset a second timer
    }
  }
}
