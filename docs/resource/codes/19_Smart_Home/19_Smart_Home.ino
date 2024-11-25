/*  
  Project name: 19_Smart_Home
  Function: Remote control led and buzzer, remote read environment brightness, humidity, temperature.
  Author: keyestudio    
  Hardware connection:  
    - Connect traffic light module to port 9
    - Connect temperature and humidity module to port 4
    - Connect buzzer to port 3
    - Connect photoresistor to port 7
  Library:  
    - SimpleTimer.h
  Develop software version:  
      It is recommended to use the same software version as the one used at the time of development to avoid incompatibility
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

// define the Node Name
char nodeName[] = "Keyes_ESP32_SmartHome";

// define the Device Names
char deviceName_1[] = "redLED";
char deviceName_2[] = "yellowLED";
char deviceName_3[] = "greenLED";
char deviceName_4[] = "buzzer";

// Preferences pref;
SimpleTimer Timer;

const char *service_name = "keyes";
const char *pop = "keyes123";

// define the Chip Id
uint32_t espChipId = 5;

//define pins
static uint8_t redLEDPin = 17;     //IO17
static uint8_t yellowLEDPin = 18;  //IO18
static uint8_t greenLEDPin = 19;   //IO19
static uint8_t buzzerPin = 26;     //IO26
static uint8_t lightPin = 35;      //IO35
static uint8_t gpio_reset = 0;     // Press BOOT to reset WiFi Details
static uint8_t DHTPIN = 27;        //RX2  pin connected with DHT

//led brightness
int red_LED_Light = 255;
int yellow_LED_Light = 255;
int green_LED_Light = 255;

// LED State, Used to switch the LED status
bool redState = true;
bool yellowState = true;
bool greenState = true;

float temperature1 = 0;
float humidity1 = 0;
float lightValue = 0;
int wifiFlag = 0;
bool first_run = true;

DHT dht(DHTPIN, DHT11);

//The framework provides some standard device types like switch, lightbulb, temperature sensor.
static LightBulb my_switch1(deviceName_1, &redLEDPin);
static LightBulb my_switch2(deviceName_2, &yellowLEDPin);
static LightBulb my_switch3(deviceName_3, &greenLEDPin);
static Switch my_switch4(deviceName_4, &buzzerPin);
static TemperatureSensor temperature("Temperature");
static TemperatureSensor humidity("Humidity");
static TemperatureSensor light("Light");

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
      Serial.println("Connected to Wi-Fi!");
      break;
  }
}

//Read data from the server
void write_callback(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx) {
  const char *device_name = device->getDeviceName();
  const char *param_name = param->getParamName();

  if (strcmp(device_name, deviceName_1) == 0) {
    if (strcmp(param_name, "Power") == 0) {
      redState = val.val.b;
      (redState == false) ? analogWrite(redLEDPin, 0) : analogWrite(redLEDPin, red_LED_Light);
      param->updateAndReport(val);
    }
    //Callback brightness value
    if (strcmp(param_name, "redLED_light") == 0) {
      red_LED_Light = val.val.i;
      if (redState == 1) {
        analogWrite(redLEDPin, red_LED_Light);
      }
      param->updateAndReport(val);
    }
  } else if (strcmp(device_name, deviceName_2) == 0) {
    if (strcmp(param_name, "Power") == 0) {
      yellowState = val.val.b;
      (yellowState == false) ? analogWrite(yellowLEDPin, 0) : analogWrite(yellowLEDPin, yellow_LED_Light);
      param->updateAndReport(val);
    }
    //Callback brightness value
    if (strcmp(param_name, "yellowLED_light") == 0) {
      yellow_LED_Light = val.val.i;
      if (yellowState == 1) {
        analogWrite(yellowLEDPin, yellow_LED_Light);
      }
      param->updateAndReport(val);
    }

  } else if (strcmp(device_name, deviceName_3) == 0) {
    if (strcmp(param_name, "Power") == 0) {
      greenState = val.val.b;
      (greenState == false) ? analogWrite(greenLEDPin, 0) : analogWrite(greenLEDPin, green_LED_Light);
      param->updateAndReport(val);
    }
    //Callback brightness value
    if (strcmp(param_name, "greenLED_light") == 0) {
      green_LED_Light = val.val.i;
      if (greenState == 1) {
        analogWrite(greenLEDPin, green_LED_Light);
      }
      param->updateAndReport(val);
    }

  } else if (strcmp(device_name, deviceName_4) == 0) {
    if (strcmp(param_name, "Power") == 0) {
      tone(buzzerPin, 384, 500);
      noTone(buzzerPin);
      param->updateAndReport(val);
    }
  }
}
void readSensor() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();  // or dht.readTemperature(true) for Fahrenheit
  //scale down the range of photoresistor to 0-100
  lightValue = map(analogRead(lightPin), 0, 4095, 0, 100);

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
  light.updateAndReportParam("Temperature", lightValue);
}


void setup() {
  Serial.begin(115200);

  pinMode(buzzerPin, OUTPUT);
  pinMode(gpio_reset, INPUT);
  pinMode(lightPin, INPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);

  analogWrite(redLEDPin, 255);
  analogWrite(yellowLEDPin, 255);
  analogWrite(greenLEDPin, 255);

  dht.begin();  // Enabling DHT sensor

  Node my_node;
  my_node = RMaker.initNode(nodeName);

  //Standard switch device
  my_switch1.addCb(write_callback);
  my_switch2.addCb(write_callback);
  my_switch3.addCb(write_callback);
  my_switch4.addCb(write_callback);

  //led light slider block
  Param red_LED("redLED_light", ESP_RMAKER_PARAM_RANGE, value(0), PROP_FLAG_READ | PROP_FLAG_WRITE);
  red_LED.addBounds(value(0), value(255), value(100));
  red_LED.addUIType(ESP_RMAKER_UI_SLIDER);
  my_switch1.addParam(red_LED);

  Param yellow_LED("yellowLED_light", ESP_RMAKER_PARAM_RANGE, value(0), PROP_FLAG_READ | PROP_FLAG_WRITE);
  yellow_LED.addBounds(value(0), value(255), value(100));
  yellow_LED.addUIType(ESP_RMAKER_UI_SLIDER);
  my_switch2.addParam(yellow_LED);

  Param green_LED("greenLED_light", ESP_RMAKER_PARAM_RANGE, value(0), PROP_FLAG_READ | PROP_FLAG_WRITE);
  green_LED.addBounds(value(0), value(255), value(100));
  green_LED.addUIType(ESP_RMAKER_UI_SLIDER);
  my_switch3.addParam(green_LED);

  //Add switch device to the node
  my_node.addDevice(my_switch1);
  my_node.addDevice(my_switch2);
  my_node.addDevice(my_switch3);
  my_node.addDevice(my_switch4);
  my_node.addDevice(temperature);
  my_node.addDevice(humidity);
  my_node.addDevice(light);
  //send Data after every 30 seconds
  Timer.setInterval(30000);
  delay(1000);

  RMaker.enableOTA(OTA_USING_PARAMS);
  RMaker.enableTZService();
  RMaker.enableSchedule();

  Serial.println("Starting ESP-RainMaker");
  RMaker.start();

  WiFi.onEvent(sysProvEvent);
#if CONFIG_IDF_TARGET_ESP32
  WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name);
#else
  WiFiProv.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, pop, service_name);
#endif

  delay(200);
  tone(buzzerPin, 384, 1000);
  noTone(buzzerPin);
}

void loop() {
  // Read GPIO0 (external button to reset device
  if (digitalRead(gpio_reset) == LOW) {  //Push button pressed
    Serial.println("Reset Button Pressed!");
    // Key debounce handling
    delay(100);
    int startTime = millis();
    while (digitalRead(gpio_reset) == LOW) delay(50);
    int endTime = millis();

    if ((endTime - startTime) > 10000) {
      // If key pressed for more than 10secs, reset all
      Serial.println("Reset to factory.");
      RMakerFactoryReset(2);
    } else if ((endTime - startTime) > 3000) {
      Serial.println("Reset Wi-Fi.");
      // If key pressed for more than 3secs, but less than 10, reset Wi-Fi
      RMakerWiFiReset(2);
    }
  }
  delay(100);
  if (WiFi.status() == WL_CONNECTED) {
    if (Timer.isReady()) {
      Serial.println("Sending Sensor Data");
      sendSensor();
      Timer.reset();  // Reset a second timer
    }
  }
}