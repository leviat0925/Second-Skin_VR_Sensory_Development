    
const int inflate1 = 12;    
const int inflate2 = 14;    
const int deflate1 = 27;    
const int deflate2 = 26;    

int pumpDelay = 2000;       
bool isRunning = false;     

void setup() {
  Serial.begin(9600);


  pinMode(valve, OUTPUT);
  digitalWrite(valve, LOW);

  pinMode(inflate1, OUTPUT);
  digitalWrite(inflate1, LOW);
  pinMode(inflate2, OUTPUT);
  digitalWrite(inflate2, LOW);

  pinMode(deflate1, OUTPUT);
  digitalWrite(deflate1, LOW);
  pinMode(deflate2, OUTPUT);
  digitalWrite(deflate2, LOW);

  Serial.println("Setup complete. Waiting for START command...");
}

void loop() {

  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  
    input.trim();  


    if (input == "START") {
      isRunning = true; 
      Serial.println("Command received: START. Pump started.");
    } else if (input == "STOP") {
      isRunning = false; 
      Serial.println("Command received: STOP. Pump stopped.");
    } else {
      int newDelay = input.toInt();
      if (newDelay > 0) {
        pumpDelay = newDelay; 
        Serial.print("Pump delay updated to: ");
        Serial.println(pumpDelay);
      } else {
        Serial.println("Unknown command received.");
      }
    }
  }


  if (isRunning) {
 
    Serial.println("Inflating...");
    digitalWrite(valve, HIGH);
    digitalWrite(inflate1, HIGH);
    digitalWrite(inflate2, LOW);
    digitalWrite(deflate1, LOW);
    digitalWrite(deflate2, LOW);
    delay(pumpDelay);  


    Serial.println("Deflating...");
    digitalWrite(valve, LOW);
    digitalWrite(inflate1, LOW);
    digitalWrite(inflate2, LOW);
    digitalWrite(deflate1, HIGH);
    digitalWrite(deflate2, LOW);
    delay(pumpDelay); 
  }
}