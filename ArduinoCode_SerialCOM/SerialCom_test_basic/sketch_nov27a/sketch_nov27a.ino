    
const int inflate1 = 32;    
const int inflate2 = 33;   
const int deflate1 = 25;    
const int deflate2 = 26;    

unsigned long previousMillis = 0; 
unsigned long modeMillis = 0;     
unsigned long cycleMillis = 0;    

int currentMode = -1;      
bool isRunning = false;    

void setup() {
  Serial.begin(9600);

  pinMode(inflate1, OUTPUT);
  digitalWrite(inflate1, LOW);
  pinMode(inflate2, OUTPUT);
  digitalWrite(inflate2, LOW);

  pinMode(deflate1, OUTPUT);
  digitalWrite(deflate1, LOW);
  pinMode(deflate2, OUTPUT);
  digitalWrite(deflate2, LOW);

  Serial.println("System ready. Initial detection starts...");
  initialDetection();
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input == "start") {
      currentMode = 0;
      isRunning = true;
      Serial.println("Command received: start. Inflate 10s and hold.");
    } else if (input == "1") {
      currentMode = 1;
      isRunning = true;
      Serial.println("Command received: Mode 1. Inflate 5s, then alternate 2s inflate/2s deflate.");
    } else if (input == "2") {
      currentMode = 2;
      isRunning = true;
      Serial.println("Command received: Mode 2. Inflate 5s, deflate 5s.");
    } else if (input == "3") {
      currentMode = 3;
      isRunning = true;
      Serial.println("Command received: Mode 3. Inflate and hold 10s.");
    } else if (input == "stop") {
      currentMode = 4;
      isRunning = true;
      Serial.println("Command received: stop. Deflate 10s.");
    } else {
      Serial.println("Unknown command. Please use 'start', '1', '2', '3', or 'stop'.");
    }
  }

  if (isRunning) {
    switch (currentMode) {
      case 0:
        modeStartHold();
        break;
      case 1:
        modeAlternateCycle();
        break;
      case 2:
        modeCycle();
        break;
      case 3:
        modeHold();
        break;
      case 4:
        modeStopDeflate();
        break;
    }
  }
}

void initialDetection() {

  inflate(5000);
  deflate(5000);
  Serial.println("Initial detection complete. Waiting for command...");
}

void modeStartHold() {

  unsigned long currentMillis = millis();
  if (currentMillis - modeMillis >= 10000) {
    inflate(10000);
    isRunning = false;
    Serial.println("Mode 0 complete. Holding inflate.");
  }
}

void modeAlternateCycle() {

  unsigned long currentMillis = millis();
  if (currentMillis - modeMillis < 5000) {
    inflate(0); 
  } else {
    unsigned long cycleTime = (currentMillis - modeMillis - 5000) % 4000;
    if (cycleTime < 2000) {
      deflate(0); 
    } else {
      inflate(0); 
    }
  }
}

void modeCycle() {
 
  unsigned long currentMillis = millis();
  unsigned long cycleTime = (currentMillis - modeMillis) % 10000;
  if (cycleTime < 5000) {
    inflate(0); 
  } else {
    deflate(0); 
  }
}

void modeHold() {

  unsigned long currentMillis = millis();
  if (currentMillis - modeMillis < 10000) {
    inflate(0);
  } else {
    Serial.println("Mode 3 complete. Holding inflate.");
    isRunning = false;
  }
}

void modeStopDeflate() {

  unsigned long currentMillis = millis();
  if (currentMillis - modeMillis < 10000) {
    deflate(0);
  } else {
    Serial.println("Mode 4 complete. Stopping system.");
    isRunning = false;
  }
}

void inflate(unsigned long duration) {
  digitalWrite(inflate1, HIGH);
  digitalWrite(inflate2, HIGH);
  digitalWrite(deflate1, LOW);
  digitalWrite(deflate2, LOW);
  if (duration > 0) delay(duration);
}

void deflate(unsigned long duration) {
  digitalWrite(inflate1, LOW);
  digitalWrite(inflate2, LOW);  // 确保充气引脚关闭
  digitalWrite(deflate1, HIGH);
  digitalWrite(deflate2, HIGH);  // 新增的放气引脚
  if (duration > 0) delay(duration);
}

void stopAll() {
  digitalWrite(inflate1, LOW);
  digitalWrite(inflate2, LOW);
  digitalWrite(deflate1, LOW);
  digitalWrite(deflate2, LOW);
}