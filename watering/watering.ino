#include <RCSwitch.h>

#define MOISTURE_PIN_1 A1
#define MOISTURE_PIN_2 A2

#define POMP_POWER_PIN 9
#define RF_PIN 2

double analogValue_1 = 0.0;
double analogValue_2 = 0.0;
double analogVolts = 0.0;

#define ON   0
#define OFF  1

#define MIN_MOISTURE  500

bool pompStarted = false;
RCSwitch rfsense = RCSwitch();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode ( POMP_POWER_PIN , OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(POMP_POWER_PIN, OFF);
  pinMode(RF_PIN, OUTPUT);  
  rfsense.enableTransmit(RF_PIN);
  rfsense.disableReceive();
  rfsense.setProtocol(1);
}

void loop() {
  
  analogValue_1 = analogRead(MOISTURE_PIN_1);
  analogValue_2 = analogRead(MOISTURE_PIN_2);
  Serial.println(analogValue_1);
  Serial.println(analogValue_2);
  Serial.print("pomp started =");
  Serial.println(pompStarted == true ? "true" : "false");
  if(analogValue_1 > MIN_MOISTURE || analogValue_2 > MIN_MOISTURE)
  {
    if(pompStarted == false){
      digitalWrite(POMP_POWER_PIN, ON);
      pompStarted = true;
      Serial.println("started");
      digitalWrite(LED_BUILTIN, HIGH);
    }

    
    delay(1000);
  }
  else
  {
    if(pompStarted){
      digitalWrite(POMP_POWER_PIN, OFF);
      pompStarted = !pompStarted;
      Serial.println("stoped");
      digitalWrite(LED_BUILTIN, LOW);
    }
    delay(10000);
  }
  rfsense.send(analogValue_1, 24);
  
  
  
  
}
