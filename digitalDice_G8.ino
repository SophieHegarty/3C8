#define Pin_A 4
#define Pin_B 5
#define Pin_C 6
#define Pin_D 7
#define Pin_Q1 8
#define Pin_Q2 9
#define Pin_Q3 10
#define Pin_Q4 11

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

}


int pulse_Q(digitalRead(Pin_Q1), digitalRead(Pin_Q2), digitalRead(Pin_Q3), digitalRead(Pin_Q4)){
    if((Pin_Q1== LOW) && (Pin_Q2 == HIGH) && (Pin_Q3 == LOW) && (Pin_Q4 == LOW)){
    testNumber = 1;
  }else if(Pin_Q1== LOW) && (Pin_Q2 == HIGH) && (Pin_Q3 == LOW) && (Pin_Q4 == HIGH)){
    testNumber = 2;
  }else if(((Pin_Q1)== LOW) && ((Pin_Q2) == HIGH) && ((Pin_Q3) == HIGH) && ((Pin_Q4) == LOW)){
    testNumber = 3;
  }else if(((Pin_Q1)== LOW) && ((Pin_Q2) == HIGH) && ((Pin_Q3) == HIGH) && ((Pin_Q4) == HIGH)){
    testNumber = 4;
  }else if(((Pin_Q1)== HIGH) && ((Pin_Q2) == LOW) && ((Pin_Q3) == LOW) && ((Pin_Q4) == LOW)){
    testNumber = 5;
  }else if(((Pin_Q1)== LOW) && ((Pin_Q2) == HIGH) && ((Pin_Q3) == LOW) && ((Pin_Q4) == HIGH)){
    testNumber = 6;
  }else{
    testNumber = 0;
  }
  return testNumber;
}

int pulse_Char(digitalRead(Pin_A), digitalRead(Pin_B), digitalRead(Pin_C), digitalRead(Pin_D)){
  if(((Pin_A)== LOW) && ((Pin_B) == LOW) && ((Pin_C) == HIGH) && ((Pin_D) == LOW)){
    testCharacter = 1;
  }else if(((Pin_Q1)== LOW) && ((Pin_Q2) == HIGH) && ((Pin_Q3) == LOW) && ((Pin_Q4) == LOW)){
    testCharacter = 2;
  }else if(((Pin_Q1)== LOW) && ((Pin_Q2) == HIGH) && ((Pin_Q3) == HIGH) && ((Pin_Q4) == LOW)){
    testCharacter = 3;
  }else if(((Pin_Q1)== HIGH) && ((Pin_Q2) == HIGH) && ((Pin_Q3) == LOW) && ((Pin_Q4) == LOW)){
    testCharacter = 4;
  }else if(((Pin_Q1)== HIGH) && ((Pin_Q2) == HIGH) && ((Pin_Q3) == HIGH) && ((Pin_Q4) == LOW)){
    testCharacter = 5;
  }else if(((Pin_Q1)== HIGH) && ((Pin_Q2) == HIGH) && ((Pin_Q3) == LOW) && ((Pin_Q4) == HIGH)){
    testCharacter = 6;
  }else{
    testCharacter = 0;
  }
  return testCharacter;
}

void testing(int testPQ, int testPC){
  if(testPQ == testPC){

    Serial.write("TestNumber =  " + testPQ " TestChar = " + testPC);
    Serial.write("Test Successful.");
    
  }else{
    Serial.write("TestNumber =  " + testPQ " TestChar = " + testPC);
    Serial.write("Test Failed.");
  }
}

void loop(){
//TESTING -- TEST NUMBERS
  //1
  testPQ = pulse_Q(Pin_Q1, Pin_Q2, Pin_Q3, Pin_Q4);
  testPC = pulse_Char(Pin_A, Pin_B, Pin_C, Pin_D);
  testing(testPQ, testPC);
    //2
  testPQ = pulse_Q(Pin_Q1, Pin_Q2, Pin_Q3, Pin_Q4);
  testPC = pulse_Char(Pin_A, Pin_B, Pin_C, Pin_D);
  testing(testPQ, testPC);
    //3
  testPQ = pulse_Q(Pin_Q1, Pin_Q2, Pin_Q3, Pin_Q4);
  testPC = pulse_Char(Pin_A, Pin_B, Pin_C, Pin_D);
  testing(testPQ, testPC);
    //4
  testPQ = pulse_Q(Pin_Q1, Pin_Q2, Pin_Q3, Pin_Q4);
  testPC = pulse_Char(Pin_A, Pin_B, Pin_C, Pin_D);
  testing(testPQ, testPC);
    //5
  testPQ = pulse_Q(Pin_Q1, Pin_Q2, Pin_Q3, Pin_Q4);
  testPC = pulse_Char(Pin_A, Pin_B, Pin_C, Pin_D);
  testing(testPQ, testPC);
    //6
  testPQ = pulse_Q(Pin_Q1, Pin_Q2, Pin_Q3, Pin_Q4);
  testPC = pulse_Char(Pin_A, Pin_B, Pin_C, Pin_D);
  testing(testPQ, testPC);
}

