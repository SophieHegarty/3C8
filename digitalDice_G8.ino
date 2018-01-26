#define Pin_A 4
#define Pin_B 5
#define Pin_C 6
#define Pin_D 7
#define Pin_Q1 8
#define Pin_Q2 9
#define Pin_Q3 10
#define Pin_Q4 11
#define Pin_Clock 12 

//#define Pin_Button

int testNumber;
int testCharacter;
int testPQ;
int testPC;


void setup() {
 // put your setup code here, to run once:
 // pinMode(Pin_Button, INPUT);
 // digitalWrite(Pin_Button, LOW):
  pinMode(Pin_A, INPUT);
  pinMode(Pin_B, INPUT);
  pinMode(Pin_C, INPUT);
  pinMode(Pin_D, INPUT);
  pinMode(Pin_Q1, INPUT);
  pinMode(Pin_Q2, INPUT);
  pinMode(Pin_Q3, INPUT);
  pinMode(Pin_Q4, INPUT);
  Serial.begin(9600);

  //TESTING -- TEST NUMBERS
  //1
  testPQ = pulse_Q();
  testPC = pulse_Char();
  testing(testPQ, testPC);
  //2
  test_clock();
  testPQ = pulse_Q();
  testPC = pulse_Char();
  testing(testPQ, testPC);
  //3
  test_clock();
  testPQ = pulse_Q();
  testPC = pulse_Char();
  testing(testPQ, testPC);
  //4
  test_clock();
  testPQ = pulse_Q();
  testPC = pulse_Char();
  testing(testPQ, testPC);
  //5
  test_clock();
  testPQ = pulse_Q();
  testPC = pulse_Char();
  testing(testPQ, testPC);
  //6
  test_clock();
  testPQ = pulse_Q();
  testPC = pulse_Char();
  testing(testPQ, testPC);
}

int pulse_Q(){
    if((digitalRead(Pin_Q1== HIGH) )&& digitalRead((Pin_Q2 == LOW)) && digitalRead((Pin_Q3 == LOW)) && (digitalRead(Pin_Q4 == LOW))){
    testNumber = 1;
  }else if((digitalRead(Pin_Q1== LOW)) && digitalRead((Pin_Q2 == HIGH)) && digitalRead((Pin_Q3 == LOW)) && digitalRead((Pin_Q4 == LOW))){
    testNumber = 2;
  }else if(digitalRead((Pin_Q1)== HIGH) && digitalRead((Pin_Q2) == HIGH) && (digitalRead(Pin_Q3) == LOW) && (digitalRead(Pin_Q4) == LOW)){
    testNumber = 3;
  }else if((digitalRead(Pin_Q1)== LOW) && digitalRead(Pin_Q2) == LOW && digitalRead(Pin_Q3) == HIGH && digitalRead(Pin_Q4) == LOW){
    testNumber = 4;
  }else if((digitalRead(Pin_Q1)== HIGH) && (digitalRead(Pin_Q2) == LOW) && (digitalRead(Pin_Q3) == HIGH) && digitalRead((Pin_Q4) == LOW)){
    testNumber = 5;
  }else if(digitalRead((Pin_Q1)== LOW) && digitalRead((Pin_Q2) == HIGH) && digitalRead((Pin_Q3) == HIGH) && digitalRead((Pin_Q4) == LOW)){
    testNumber = 6;
  }else{
    testNumber = 0;
  }
  return testNumber;
}

int pulse_Char(){
  int a = (digitalRead(Pin_A) ? 0 : 1);
  int b = (digitalRead(Pin_B) ? 0 : 1);
  int c = (digitalRead(Pin_C) ? 0 : 1);
  int d = (digitalRead(Pin_D) ? 0 : 1);
  testNumber = a << 3 | b << 2 | c << 1 | d;

  return testNumber;
}

void testing(int testPQ, int testPC){
  if(testPQ == testPC){
    Serial.write("TestNumber =  " + testPQ);
    Serial.write(" TestChar = " + testPC);
    Serial.write("Test Successful.");
  }else{
    Serial.write("TestNumber =  " + testPQ);
    Serial.write(" TestChar = " + testPC);
    Serial.write("Test Failed.");
  }
}

void test_clock(){
  digitalWrite(Pin_Clock, HIGH);
  delay(100);
  digitalWrite(Pin_Clock, LOW);
}

void loop(){
}

