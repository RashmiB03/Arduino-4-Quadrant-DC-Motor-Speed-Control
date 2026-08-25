// Motor control pins
const int enA = 9;    // Enable pin (PWM for speed)
const int in1 = 8;    // Input 1
const int in2 = 7;    // Input 2

// Button pins
const int btnForward = 2;
const int btnReverse = 3;
const int btnFwdBlock = 4;
const int btnRevBlock = 5;

// Motor states
enum MotorState {
  STOPPED,
  FORWARD,
  REVERSE,
  FORWARD_BLOCKING,
  REVERSE_BLOCKING
};

MotorState currentState = STOPPED;

void setup() {
  // Set motor control pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // Set button pins as inputs
  pinMode(btnForward, INPUT);
  pinMode(btnReverse, INPUT);
  pinMode(btnFwdBlock, INPUT);
  pinMode(btnRevBlock, INPUT);
  
  // Start with motors stopped
  stopMotor();
  
  Serial.begin(9600);
  Serial.println("Motor Controller with Blocking Ready!");
  Serial.println("Commands: Forward, Reverse, Fwd Block, Rev Block");
}

void loop() {
  // Read button states
  bool forwardBtn = digitalRead(btnForward);
  bool reverseBtn = digitalRead(btnReverse);
  bool fwdBlockBtn = digitalRead(btnFwdBlock);
  bool revBlockBtn = digitalRead(btnRevBlock);
  
  // Handle button presses with priority
  if (fwdBlockBtn) {
    setForwardBlocking();
  }
  else if (revBlockBtn) {
    setReverseBlocking();
  }
  else if (forwardBtn) {
    setForward();
  }
  else if (reverseBtn) {
    setReverse();
  }
  else {
    // No buttons pressed - maintain current blocking state or stop
    if (currentState != FORWARD_BLOCKING && currentState != REVERSE_BLOCKING) {
      stopMotor();
    }
  }
  
  delay(50); // Small delay for stability
}

void setForward() {
  if (currentState != FORWARD) {
    // Motor A forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 200); // Medium speed
    
    currentState = FORWARD;
    Serial.println("MOTOR: Forward Running");
  }
}

void setReverse() {
  if (currentState != REVERSE) {
    // Motor A reverse
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, 200); // Medium speed
    
    currentState = REVERSE;
    Serial.println("MOTOR: Reverse Running");
  }
}

void setForwardBlocking() {
  if (currentState != FORWARD_BLOCKING) {
    // Motor A forward with high torque (blocking)
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 255); // Full speed - maximum torque
    
    currentState = FORWARD_BLOCKING;
    Serial.println("MOTOR: Forward BLOCKING (High Torque)");
  }
}

void setReverseBlocking() {
  if (currentState != REVERSE_BLOCKING) {
    // Motor A reverse with high torque (blocking)
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, 255); // Full speed - maximum torque
    
    currentState = REVERSE_BLOCKING;
    Serial.println("MOTOR: Reverse BLOCKING (High Torque)");
  }
}

void stopMotor() {
  if (currentState != STOPPED) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(enA, 0);
    
    currentState = STOPPED;
    Serial.println("MOTOR: Stopped");
  }
}
