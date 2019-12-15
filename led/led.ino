#define LED_PIN 9
#define PIR_PIN 7

#define LIGHTS_ON 255
#define LIGHTS_OFF 0
#define TIMEOUT 15000

bool lightOn = true;
unsigned long startTime = 0;

void setup() {
  // put your_
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT_PULLUP);
  analogWrite(LED_PIN, 0);
  digitalWrite(PIR_PIN, LOW);
  Serial.begin(9600);
  PirStartUp();
  SwitchLights(LIGHTS_ON);
  startTime = millis();
}

void SwitchLights(int status)
{
  digitalWrite(LED_PIN, status);
  lightOn = status == 0 ? false : true;
}

void PirStartUp()
{
  for(int i= 0;i<60;i++)
  {
    FadeIn(5);
    FadeOut(5);
  }  
}

void FadeIn(int withDelay)
{
  for(int i=0;i<255;i+=5)
  {
    analogWrite(LED_PIN,i);
    delay(withDelay);
  }
}

void FadeOut(int withDelay)
{
  for(int i=255;i>=0;i-=5)
  {
    analogWrite(LED_PIN,i);
    delay(withDelay);
  }

}

int pirStatus = 0;
unsigned long now = 0;
unsigned long left = 0;

void loop() {

  pirStatus = digitalRead(PIR_PIN);

  now = millis();
  left = now - startTime;

  
  if(pirStatus == HIGH)
  {
      startTime = millis(); //reset timer      
      if(lightOn == false)
      {
        FadeIn(10);
        SwitchLights(LIGHTS_ON);
      }
  }
  
  if(left > TIMEOUT)
  {
        if(lightOn == true)
        {
         FadeOut(10);
         SwitchLights(LIGHTS_OFF);
        }
      
  }
  Serial.print("left=");Serial.println(left);
    
    
}
