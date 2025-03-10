#define MotionSensorPin 13
#define BuzzerPin 12
#define RedPin 27
#define BluePin 26
#define LedOnPin 25
#define LedOffPin 33
#define OnButtonPin 35
#define OffButtonPin 34

bool AlarmState = LOW;
bool AlarmOn, AlarmOff;
int Motion;

void PinSetup(){
  pinMode(MotionSensorPin, INPUT);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(RedPin, OUTPUT);
  pinMode(LedOnPin, OUTPUT);
  pinMode(LedOffPin, OUTPUT);
  pinMode(OnButtonPin, INPUT);
  pinMode(OffButtonPin, INPUT);
}

void offState(){
  digitalWrite(RedPin, LOW);
  digitalWrite(BluePin, LOW);
  digitalWrite(BuzzerPin, LOW);
  digitalWrite(LedOnPin, LOW);
  digitalWrite(LedOffPin, HIGH);
}

void LedAlarm(){
  digitalWrite(BluePin, LOW);
  digitalWrite(RedPin, HIGH);
  delay(75);
  digitalWrite(RedPin, LOW);
  digitalWrite(BluePin, HIGH);
  delay(75);
}

void LedOn(){
  digitalWrite(LedOnPin, HIGH);
  digitalWrite(LedOffPin, LOW);
}

void LedOff(){
  digitalWrite(LedOnPin, LOW);
  digitalWrite(LedOffPin, HIGH);
}

void setup() {
  Serial.begin(115200);
  PinSetup();
  offState();
}

void loop() {
  AlarmOn = digitalRead(OnButtonPin);
  AlarmOff = digitalRead(OffButtonPin);

  if(AlarmOn == HIGH){
    AlarmState = HIGH;
    LedOn();
  }

  else if(AlarmOff == HIGH){
    AlarmState = LOW;
    LedOff();
  }

  if(AlarmState == HIGH){
    Motion = digitalRead(MotionSensorPin);
    if(Motion == HIGH){
      digitalWrite(BuzzerPin, HIGH);
      while(true){
        AlarmOff = digitalRead(OffButtonPin);
        LedAlarm();
        if(AlarmOff == HIGH){
          offState();
          AlarmState = LOW;
          break;
        }
      }
    }
  }
}
