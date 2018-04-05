#ifndef TESTCHECKER_H_AGIZLRKF
#define TESTCHECKER_H_AGIZLRKF

#include "Scenario.h"

#include "InputWriter.h"
#include "ValidatorReader.h"

#include <Arduino.h>
#include "stl.h"

/**
 * Scenario relating to the "Checker section" board
 */
namespace scenarios {
    void testCheckerSection() {
        Scenario s("CheckerSection");


        InputWriter input(5, 6, 7, 8, 4,3);
        ValidatorReader reader(18,17,16,19);
        char buffer[100];



        byte position, correct;
        s.sectionHeader("CheckCorrectAnswer");
        Serial.print("CODE: 9386\n");

        Serial.print("STATE AFTER RESET\n");
        Serial.print("position: ");
        Serial.println(reader.readPosition()) ;
        Serial.print("Corect state: ");
        Serial.println(reader.stillCorrect()) ;

        input.writeNumber(9);
        input.pulseValid();

        Serial.print("NUMBER IN: 9\n");
        Serial.print("position: ");
        Serial.println(reader.readPosition()) ;
        Serial.print("Corect state: ");
        Serial.println(reader.stillCorrect()) ;

      //  if (!CHECK_CONDITION(s, reader.readPosition() == 1)
        // && !CHECK_CONDITION(s, reader.stillCorrect())){
         //	Serial.print("Incorrect position: ");
         	//Serial.println(reader.readPosition()) ;
         //}
        
    	input.writeNumber(3);
        input.pulseValid();

        Serial.print("NUMBER IN: 3\n");
        Serial.print("position: ");
        Serial.println(reader.readPosition()) ;
        Serial.print("Corect state: ");
        Serial.println(reader.stillCorrect()) ;

    	//if (!CHECK_CONDITION(s, reader.readPosition() == 2)
         //&& !CHECK_CONDITION(s, reader.stillCorrect())) {
         	//Serial.print("Incorrect position: ");
         	//Serial.println(reader.readPosition()) ;
         //}

    	input.writeNumber(8);
        input.pulseValid();

        Serial.print("NUMBER IN: 8\n");
        Serial.print("position: ");
        Serial.println(reader.readPosition()) ;
        Serial.print("Corect state: ");
        Serial.println(reader.stillCorrect()) ;

//    	if (!CHECK_CONDITION(s, reader.readPosition() == 3)
  //       && !CHECK_CONDITION(s, reader.stillCorrect())) {
    //     	Serial.print("Incorrect position: ");
      //   	Serial.println(reader.readPosition()) ;
        // }

    	input.writeNumber(6);
        input.pulseValid();

        Serial.print("NUMBER IN: 6\n");
        Serial.print("position: ");
        Serial.println(reader.readPosition()) ;
        Serial.print("Corect state: ");
        Serial.println(reader.stillCorrect()) ;

//    	if (!CHECK_CONDITION(s, reader.readPosition() == 4)
  //       && !CHECK_CONDITION(s, reader.stillCorrect())) {
    //     	Serial.print("Incorrect position: ");
      //   	Serial.println(reader.readPosition()) ;
        // }

        s.sectionHeader("CheckMistake");

        input.pulseClear();
        input.writeNumber(9);
        input.pulseValid();

        Serial.print("NUMBER IN: 9\n");
        Serial.print("position: ");
        Serial.println(reader.readPosition()) ;
        Serial.print("Corect state: ");
        Serial.println(reader.stillCorrect()) ;

        input.writeNumber(2);
        input.pulseValid();

        Serial.print("NUMBER IN: 2\n");
        Serial.print("position: ");
        Serial.println(reader.readPosition()) ;
        Serial.print("Corect state: ");
        Serial.println(reader.stillCorrect()) ;

        input.writeNumber(2);
        input.pulseValid();

        Serial.print("NUMBER IN: 2\n");
        Serial.print("position: ");
        Serial.println(reader.readPosition()) ;
        Serial.print("Corect state: ");
        Serial.println(reader.stillCorrect()) ;

        input.writeNumber(2);
        input.pulseValid();
        
        Serial.print("NUMBER IN: 2\n");
        Serial.print("position: ");
        Serial.println(reader.readPosition()) ;
        Serial.print("Corect state: ");
        Serial.println(reader.stillCorrect()) ;




        input.pulseClear();

        s.interimReport();


    }
}

#endif /* end of include guard: TESTCHECKER_H_AGIZLRKF */
