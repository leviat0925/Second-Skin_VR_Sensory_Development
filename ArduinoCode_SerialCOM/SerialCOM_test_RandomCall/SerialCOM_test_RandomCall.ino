bool isRunning = false;  
String currentMode = ""; 
unsigned long previousMillis = 0; 
const int interval = 1000; 


String colors[] = {"Red", "Blue", "Green", "Yellow", "Purple"};
String shapes[] = {"Circle", "Square", "Triangle", "Rectangle", "Star"};

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); 
  Serial.println("System ready. Send 'number', 'color', 'shape', or 'stop' to control output.");
}

void loop() {

  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); 
    input.trim(); 


    if (input == "number" || input == "color" || input == "shape") {
      currentMode = input;  
      isRunning = true; 
      Serial.print("Mode set to: ");
      Serial.println(currentMode);
    } else if (input == "stop") {
      isRunning = false;
      Serial.println("Command received: stop. Halting all output.");
    } else {
      Serial.println("Unknown command. Please use 'number', 'color', 'shape', or 'stop'.");
    }
  }


  if (isRunning) {
    unsigned long currentMillis = millis();


    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      if (currentMode == "number") {
        int randomNumber = random(1, 101); 
        Serial.print("Random number: ");
        Serial.println(randomNumber);
      } else if (currentMode == "color") {
        int randomIndex = random(0, 5);
        Serial.print("Random color: ");
        Serial.println(colors[randomIndex]);
      } else if (currentMode == "shape") {
        int randomIndex = random(0, 5);
        Serial.print("Random shape: ");
        Serial.println(shapes[randomIndex]);
      }
    }
  }
}
