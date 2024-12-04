/*  
  Project name: 18_led_iot
  Function: Remote control led on and off
  Author: keyestudio    
  Hardware connection:  
    - Connect to port 9
  Library:  
    - none (no need to import additional library)  
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

// define the Node Name
char nodeName[] = "Keyes_ESP32_SmartHome";
//Set the Bluetooth name and key
const char *service_name = "keyestudio1";
const char *pop = "keyes123";

// define the Chip Id
uint32_t espChipId = 5;

// define the Device Names
char deviceName_1[] = "redLED";
char deviceName_2[] = "yellowLED";
char deviceName_3[] = "greenLED";
//define pins
static uint8_t redLEDPin = 17;     //IO17
static uint8_t yellowLEDPin = 18;  //IO18
static uint8_t greenLEDPin = 19;   //IO19
static uint8_t gpio_reset = 0;     // Press BOOT to reset WiFi Details

int red_LED_Light = 255;
int yellow_LED_Light = 255;
int green_LED_Light = 255;

// RLED State, Used to switch the LED status
bool redState = true;
bool yellowState = true;
bool greenState = true;

//The framework provides some standard device types like switch, lightbulb, temperature sensor.
static LightBulb my_switch1(deviceName_1, &redLEDPin);
static LightBulb my_switch2(deviceName_2, &yellowLEDPin);
static LightBulb my_switch3(deviceName_3, &greenLEDPin);

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
    //Callback brightness value - Test
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
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // PWM pin initialization
  pinMode(redLEDPin,OUTPUT);
  pinMode(yellowLEDPin,OUTPUT);
  pinMode(greenLEDPin,OUTPUT);
  //The initial state of the led is on
  analogWrite(redLEDPin, red_LED_Light);
  analogWrite(yellowLEDPin, yellow_LED_Light);
  analogWrite(greenLEDPin, green_LED_Light);

  Node my_node;
  my_node = RMaker.initNode(nodeName);


  //Standard switch device
  my_switch1.addCb(write_callback);
  my_switch2.addCb(write_callback);
  my_switch3.addCb(write_callback);

  //Add led slider block
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

  delay(1000);

  //This is optional
  RMaker.enableOTA(OTA_USING_PARAMS);
  //If you want to enable scheduling, set time zone for your region using setTimeZone().
  //The list of available values are provided here https://rainmaker.espressif.com/docs/time-service.html
  // RMaker.setTimeZone("Asia/Shanghai");
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
}
