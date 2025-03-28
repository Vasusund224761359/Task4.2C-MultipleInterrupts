
#define BUTTON_PIN 2            // Push button connected to digital pin 2
#define TRIG_PIN 3              // Trig pin of ultrasonic sensor connected to digital pin 3
#define ECHO_PIN 4              // Echo pin of ultrasonic sensor connected to digital pin 4
#define LED1_PIN 5              // LED1 connected to digital pin 5
#define LED2_PIN 6              // LED2 connected to digital pin 6


volatile bool buttonPressed = false;  // Flag to indicate button press
long duration, distance;  // For storing distance measurement


void buttonISR() {//This is used for setting up a flag likw when button press, it stets the value to true
  buttonPressed = true;   
}

void setup() {
  
  Serial.begin(9600);

  
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Button pin 
  pinMode(TRIG_PIN, OUTPUT);  // Trig pin as output
  pinMode(ECHO_PIN, INPUT);  // Echo pin as input
  pinMode(LED1_PIN, OUTPUT);  // LED1 pin as output
  pinMode(LED2_PIN, OUTPUT);  // LED2 pin as output

  
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);  //used to tell arduino to watch for changes on certain pins.

  
  digitalWrite(LED1_PIN, LOW);  // LED1 off initially
  digitalWrite(LED2_PIN, LOW);  // LED2 off initially
}

void loop() {
  
  if (buttonPressed) {
    buttonPressed = false;  
    digitalWrite(LED1_PIN, !digitalRead(LED1_PIN));  // Toggle LED1
    Serial.println("Button pressed! LED1 toggled.");//Print on the serial monitor as soon asd the button 1 is pressed
  }

  // Measure distance using ultrasonic sensor
  
  digitalWrite(TRIG_PIN, LOW);  // Ensure trig is LOW
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);  // Trigger the ultrasonic sensor
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);  // Stop trigger

 
  duration = pulseIn(ECHO_PIN, HIGH);  // Read the duration of the pulse

  
  distance = duration * 0.0344 / 2;  

  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");//Prints out thevalue of the distnce onthe serial monitor

  // Toggle LED2 based on distance (for example, turn on if distance < 20 cm)
  if (distance < 20) {
    digitalWrite(LED2_PIN, HIGH);  // Turn on LED2 if distance is less than 20 cm
    Serial.println("LED2 ON (Distance less than 20 cm)");
  } else {
    digitalWrite(LED2_PIN, LOW);  // Turn off LED2 if distance is more than 20 cm
    Serial.println("LED2 OFF (Distance more than 20 cm)");
  }

  
  delay(500);  //Delay in measuering the values
}
