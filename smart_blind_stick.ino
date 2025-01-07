// // Smart Stick for visually impaired //

// const int trigPin = 3;
// const int echoPin = 2;
// const int buzzer = 4;
// const int motorPin = 5;

// long duration;
// int distance;
// int safetyDistance;


// void setup() {
// Serial.begin (9600); 
// pinMode(trigPin, OUTPUT); 
// pinMode(echoPin, INPUT); 
// pinMode(buzzer, OUTPUT);
// pinMode(motorPin, OUTPUT); 
// }


// void loop() {
// digitalWrite(trigPin, LOW);
// delayMicroseconds(2);
// digitalWrite(trigPin, HIGH);
// delayMicroseconds(10);
// digitalWrite(trigPin, LOW);
// duration = pulseIn(echoPin, HIGH);
// distance= (duration*0.034)/2;

// safetyDistance = distance;
// if (safetyDistance <= 30){
//   Serial.println (" Object is near ");
//   Serial.print (" Distance= ");              
//   Serial.println (safetyDistance);
//   digitalWrite(motorPin, HIGH);
//   digitalWrite(buzzer, HIGH);
//   delay (500);
//   digitalWrite (buzzer, LOW);
//   delay (500);
// }
// if (safetyDistance <= 20){
//   Serial.println (" Object is near ");
//   Serial.print (" Distance= ");              
//   Serial.println (safetyDistance);
//   digitalWrite(motorPin, HIGH);
//   digitalWrite(buzzer, HIGH);
//   delay (200);
//   digitalWrite (buzzer, LOW);
//   delay (200);
// }
// if (safetyDistance <= 10){
//   Serial.println (" Object is near ");
//   Serial.print (" Distance= ");              
//   Serial.println (safetyDistance);
//   digitalWrite(motorPin, HIGH);
//   digitalWrite(buzzer, HIGH);
//   delay (50);
//   digitalWrite (buzzer, LOW);
//   delay (50);
// }
// else{
//   Serial.println (" object is far ");
//   Serial.print (" Distance= ");              
//   Serial.println (distance);        
//   digitalWrite (buzzer, LOW);
//   digitalWrite(motorPin, LOW);
//   delay (250);
// }
// }


// Smart Stick for Visually Impaired //

const int trigPin1 = 3; // Bottom sensor trigger pin
const int echoPin1 = 2; // Bottom sensor echo pin
const int trigPin2 = 7; // Top sensor trigger pin
const int echoPin2 = 6; // Top sensor echo pin
const int buzzer = 4;   // Buzzer pin
const int motorPin = 5; // Vibration motor pin

long duration1, duration2;
int distance1, distance2;
const int safetyDistance = 30; // Safety distance threshold in cm
const int minDelay = 250;       // Minimum delay in ms
const int maxDelay = 1000;     // Maximum delay in ms

void setup() {
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // Measure distance from the bottom sensor
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1 * 0.034) / 2;

  // Measure distance from the top sensor
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 * 0.034) / 2;

  // Calculate delay based on proximity (closer distance -> shorter delay)
  int delayBottom = map(distance1, 0, safetyDistance, minDelay, maxDelay);
  int delayTop = map(distance2, 0, safetyDistance, minDelay, maxDelay);

  // Object detected by the bottom sensor
  if (distance1 <= safetyDistance) {
    Serial.println("Object detected at bottom.");
    Serial.print("Bottom distance: ");
    Serial.println(distance1);
    digitalWrite(motorPin, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(delayBottom); // Dynamic delay based on bottom distance
    digitalWrite(motorPin, LOW);
    digitalWrite(buzzer, LOW);
    delay(delayBottom);
  }

  // Object detected by the top sensor
  else if (distance2 <= safetyDistance) {
    Serial.println("Object detected at height.");
    Serial.print("Top distance: ");
    Serial.println(distance2);
    digitalWrite(motorPin, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(delayTop); // Dynamic delay based on top distance
    digitalWrite(motorPin, LOW);
    digitalWrite(buzzer, LOW);
    delay(delayTop);
  }

  // No object detected
  else {
    Serial.println("No object detected.");
    digitalWrite(buzzer, LOW);
    digitalWrite(motorPin, LOW);
    delay(250);
  }
}
