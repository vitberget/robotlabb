#define ON 1
#define OFF 0

#define LEFT_SPEED 4
#define LEFT_FORWARD 7
#define LEFT_REVERSE 8

#define RIGHT_SPEED 3
#define RIGHT_FORWARD 5
#define RIGHT_REVERSE 6

#define RIGHT_LINE_SENSOR A2
#define LEFT_LINE_SENSOR A3

#define BUTTON_PIN 9

int LEN = 5;
int leftBuf = 0;
int rightBuf = 0;
int rightLineSensorBack = 700; 
int rightLineSensorCounter = 0;
int rightLineSensorCounterStart = 3500;   //1000 = 45 grader rotation (rotationstid: rightLineSensorCounterStart-rightLineSensorBack)
int whiteColor = 600;

bool shouldRun = false;
bool running = false;

bool serial = true;

void motors(int leftSpeed, int rightSpeed) {
  int l = min(255, abs(leftSpeed));
  int r = min(255, abs(rightSpeed));

  if(l>200)
    digitalWrite(LEFT_SPEED, HIGH);
  else
    analogWrite(LEFT_SPEED, l);

  if(r>200)
    digitalWrite(RIGHT_SPEED, HIGH);
  else
    analogWrite(RIGHT_SPEED, r);

  if(leftSpeed==0) {
    digitalWrite(LEFT_FORWARD, OFF);
    digitalWrite(LEFT_REVERSE, OFF);
  } else if(leftSpeed<0) {
    digitalWrite(LEFT_FORWARD, OFF);
    digitalWrite(LEFT_REVERSE, ON);
  } else {
    digitalWrite(LEFT_FORWARD, ON);
    digitalWrite(LEFT_REVERSE, OFF);
  }

  if(rightSpeed==0) {
    digitalWrite(RIGHT_FORWARD, OFF);
    digitalWrite(RIGHT_REVERSE, OFF);
  } else if(rightSpeed<0) {
    digitalWrite(RIGHT_FORWARD, OFF);
    digitalWrite(RIGHT_REVERSE, ON);
  } else {
    digitalWrite(RIGHT_FORWARD, ON);
    digitalWrite(RIGHT_REVERSE, OFF);
  }
}

bool onOff = false;


void buttonPressed() {
  cli(); // Disable interrupts
  //Serial.println("Button interupt FALLING (pressed)");
  detachInterrupt(BUTTON_PIN);
  if(shouldRun) {
    motors(0,0);
    delay(100);
    running = false;
  }
  shouldRun = !shouldRun;
  sei(); // Enable interrupts
}

int readLeft() {
  //return analogRead(A0);
  leftBuf = (leftBuf * LEN + analogRead(A1)) / (LEN+1);
  return leftBuf;
}

int readRight() {
  //return analogRead(A1);
  rightBuf = (rightBuf * LEN + analogRead(A0)) / (LEN+1);
  return rightBuf;
}

int readLineSensor(int sensor) {
  return analogRead(sensor);
}


void rotateLeft() {
  motors(-255,255);
}

void back() {
  motors(-255,-255);
}


void turn180DegreesToEscapeWhiteLine() {
  if (rightLineSensorCounter <= (rightLineSensorCounterStart-rightLineSensorBack)) {
      rotateLeft();
  } else {
      back();
  }
  //if (serial) Serial.printf("COUNTER: [%4d]", rightLineSensorCounter);
  //if (serial) Serial.println("");
  rightLineSensorCounter--;
}

void setup() {
  if(serial) Serial.begin(115200);

  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(RIGHT_LINE_SENSOR,INPUT);
  pinMode(LEFT_LINE_SENSOR,INPUT);

  pinMode(RIGHT_SPEED, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_REVERSE, OUTPUT);

  pinMode(LEFT_SPEED, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);

  pinMode(13, OUTPUT);

   motors(0,0);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(BUTTON_PIN, buttonPressed, FALLING);

  //delay(100);

  //pixels.begin();
  //pixels.setPixelColor(0, pixels.Color(0,150,0));
  //pixels.show();

  //delay(100);
}
void loop() {
  onOff = !onOff;
  digitalWrite(13, onOff ? HIGH : LOW);

  if(!running) {
    if(shouldRun) {
      //Serial.println("Waiting to start");
      running = true;
      delay(3000);
    } else {
      //Serial.println("Waiting for button");
      delay(100);
      return;
    }
  }

  int left = readLeft();
  int right = readRight();
  int rightLineSensor = readLineSensor(RIGHT_LINE_SENSOR);
  int leftLineSensor = readLineSensor(LEFT_LINE_SENSOR);
  int diff = left - right;
  int avg = (left + right) / 2;

 
  //delay(500);
  //if (serial) Serial.printf("[%4d %4d %5d] ",left,right,diff);
  if (serial) Serial.printf("[%4d]", leftLineSensor);
  if (serial) Serial.printf("[%4d]", rightLineSensor);
  //if (serial) Serial.printf("[%4d %4d %5d] ",left,right,diff);

  
  if (rightLineSensorCounter == 0 && (rightLineSensor < whiteColor)) {
    // Found white line
    rightLineSensorCounter = rightLineSensorCounterStart;
  }

  if (rightLineSensorCounter > 0) {
    turn180DegreesToEscapeWhiteLine();
  } else {
    int ll = left/32;
    int rr = right/32;
  
    if (serial) Serial.print("[");
    for(int i=0; serial && i< 32; i++) {
        Serial.print(i<=ll ? "=":"-");
    }
    if (serial) Serial.print("|");
    for(int i=31; serial && i>-1; i--) {
        Serial.print(i<=rr ? "=":"-");
    }
  
    if(serial) Serial.print("] ");
  
    if(ll>rr+3) {
      if (serial) Serial.print("Left");
      motors(-255,255);
    } else if(rr>ll+3) {
      if (serial) Serial.print("Right");
      motors(255,-255);
    } else if (ll >4 && rr>4) {
      if (serial) Serial.print("Fwd");
      motors(255, 255);
    } else {
      if (serial) Serial.print("Search");
      if((millis()%8000)>4000) {
        motors(255,-255);
      } else {
        motors(-255,255);
      }
    }
  
    if (serial) Serial.println();
    delay(7);
  }
}
