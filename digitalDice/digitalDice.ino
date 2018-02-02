//pin
#define Pin_test_clock 3
#define Pin_A 4
#define Pin_B 5
#define Pin_C 6
#define Pin_D 7
#define Pin_Q1 8
#define Pin_Q2 9
#define Pin_Q3 10
#define Pin_Q4 11
#define Pin_clock 12
#define Pin_test 14

#define clock_delay 10


void setup() {
 // put your setup code here, to run once:
 //set up pins and serial
  pinMode(Pin_A, INPUT);
  pinMode(Pin_B, INPUT);
  pinMode(Pin_C, INPUT);
  pinMode(Pin_D, INPUT);
  pinMode(Pin_Q1, INPUT);
  pinMode(Pin_Q2, INPUT);
  pinMode(Pin_Q3, INPUT);
  pinMode(Pin_Q4, INPUT);
  pinMode(Pin_clock, OUTPUT);
  pinMode(Pin_test_clock, OUTPUT);
  pinMode(Pin_test, INPUT_PULLUP);
  
  Serial.begin(9600);
}

int test_Q() { // creates test number for the Q pins, ie pins from CD4029BMS counter
  byte q1 = digitalRead(Pin_Q1);
  byte q2 = digitalRead(Pin_Q2);
  byte q3 = digitalRead(Pin_Q3);
  byte q4 = digitalRead(Pin_Q4);
  byte testNumber = q4 << 3 | q3 << 2 | q2 << 1 | q1;

  return testNumber;
}

int test_Char() { // creates a test number for the 'char' pins ie pins from leds
  byte testCharacter = 0;
  bool a = digitalRead(Pin_A) ? false : true;
  bool b = digitalRead(Pin_B) ? false : true;
  bool c = digitalRead(Pin_C) ? false : true;
  bool d = digitalRead(Pin_D) ? false : true;

  if (!a && !b && c && !d) {
      testCharacter = 1;
  }
  if (a && !b && !c && !d) {
      testCharacter = 2;
  }
  if (a && !b && c && !d) {
      testCharacter = 3;
  }
  if (a && b && !c && !d) {
      testCharacter = 4;
  }
  if (a && b && c && !d) {
      testCharacter = 5;
  }
  if (a && b && !c && d) {
      testCharacter = 6;
  }

  return testCharacter;
}

void testing(byte testPQ, byte testPC) { //compares the two test numbers, if equal test is sucessful 
  Serial.print("TestNumber =  ");
  Serial.println(testPQ);
  Serial.print(" TestChar = ");
  Serial.println(testPC);
  
  if(testPQ == testPC){
    Serial.println("Test Successful.");
  } else {
    Serial.println("Test Failed.");
  }
}

void clock_pulse(int pin) { // function to pulse clock pin
  digitalWrite(pin, HIGH);
  delay(10);
  digitalWrite(pin, LOW);
  delay(10);
}

void loop() {
  if(digitalRead(Pin_test) == LOW){
    //TESTING -- TEST NUMBERS repeat 6 times to test all possible numbers
    for (byte i = 0; i < 6; i++) {
      byte testPQ = test_Q();
      byte testPC = test_Char();
      testing(testPQ, testPC);
      clock_pulse(Pin_test_clock);
    }

    while(digitalRead(Pin_test) == LOW);
  }

  clock_pulse(Pin_clock);
}
