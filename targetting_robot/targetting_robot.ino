#define ON 1
#define OFF 0

#define LS 4
#define LF 7
#define LR 8

#define RS 3
#define RF 5
#define RR 6

void setup() {                
  Serial.begin(38400);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);

  pinMode(LS, OUTPUT);
  pinMode(RS, OUTPUT);
  pinMode(LF, OUTPUT);
  pinMode(LR, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RR, OUTPUT);

  analogWrite(LS, 200);
  analogWrite(RS, 200);
}

void loop() {
  int left = analogRead(A0);
  int right = analogRead(A1);
  int diff = left - right;
  Serial.printf("[%4d %4d %4d] ",left,right,diff);

  if(diff < -100) {
    Serial.println("Turning LEFT");
    digitalWrite(LF, OFF);
    digitalWrite(LR, ON);
    digitalWrite(RF, ON);
    digitalWrite(RR, OFF);
  } else if (diff > 100) {
    Serial.println("Turning RIGHT");
    digitalWrite(LF, ON);
    digitalWrite(LR, OFF);
    digitalWrite(RF, OFF);
    digitalWrite(RR, ON);
  } else {
    Serial.println("Turning STOP");
    digitalWrite(LF, OFF);
    digitalWrite(LR, OFF);
    digitalWrite(RF, OFF);
    digitalWrite(RR, OFF);
  }
  
  delay(133);
} 

