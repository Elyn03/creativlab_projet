/*!
   Arduino digital meter manager project
   Autor : thlg
   File : Display4Digit7Segments.cpp

   Based on Haljia Arduino starter kit
   http://www.haljia.com/
   Component :
   - Arduino Uno
   - 4 digits/7 segments Led display 5641BH

   Released under the MIT license
   https://opensource.org/licenses/MIT

   Date: 2017-12-27
 */
 
#include <Arduino.h>
#include "Display4Digit7Segments.h"

/*
 * Clas constructor
 * 
 * segmentIdBase : Arduino port id for A segment
 *                 Segments B, C, D, E, F and G must be the next
 * digitIdBase   : Arduino port id for digit 1
 *                 Digits 2, 3 and 4 must be the next.
*/
Display4Digit7Segments::Display4Digit7Segments(int segmentIdBase, int digitIdBase)
{
  mSegmentId = segmentIdBase;
  mDigitId = digitIdBase;
}

/*
 * Initialize pinMode for segments and digits
 * Must be call from arduino setup() method 
*/
void Display4Digit7Segments::Setup()
{
  // configure outputs
  for (int i = 0; i < 7; i++) {
    pinMode(mSegmentId + i, OUTPUT);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(mDigitId + i, OUTPUT);
  }
}

/*
 * Display a number.
 * 
 * value : value to display
 *         Value must be greater than 0
 */
void Display4Digit7Segments::Display(int value)
{
  Display(value, MaxDigit);
}

/*
 * Display a number
 * 
 * value            : value to display
 *                    Value must be greater than 0
 * nbDigitToDisplay : Digit max count
 *                    Must be between 1 to 4
 */
void Display4Digit7Segments::Display(int value, int nbDigitToDisplay)
{
  if (nbDigitToDisplay < 1) {
    nbDigitToDisplay = 1;
  }
  if (nbDigitToDisplay > MaxDigit) {
    nbDigitToDisplay = MaxDigit;
  }

  if (value < 0) {
    value = 0;
  }
  
  GetDigits(value);
  DisplayDigits(nbDigitToDisplay);
}

/*
 * Transform a number to a digit array
 * If the number is greater than 10000 then only last 4 digits are keep.
 * Store digits to mDigits global variable
 * 
 * value : value to transform to a digit array
 */
void Display4Digit7Segments::GetDigits(int value)
{
  mDigits[0] = value / 1000;
  mDigits[0] = mDigits[0] % 10;
  value = value - (mDigits[0] * 1000);
  mDigits[1] = value / 100;
  value = value - (mDigits[1] * 100);
  mDigits[2] = value / 10;
  mDigits[3] = value - (mDigits[2] * 10);
}

/*
 * Display digits to the display led component.
 * 
 * nbDigitToDisplay : Number to digits to display.
 *                    Must be between 1 and 4
 */
void Display4Digit7Segments::DisplayDigits(int nbDigitToDisplay)
{
  for (int i = 0; i < 4; i++) {
    digitalWrite( mDigitId + i, LOW);
  }

  for (int i = 4 - nbDigitToDisplay; i < 4; i++) {
    digitalWrite( mDigitId + i, HIGH);
    DisplayDigit(mDigits[i]);
    delay(DTime);
    digitalWrite( mDigitId + i, LOW);
  }

  delay(DTime);
}

/*
 * Display a single value on a 7 segments component
 * 
 * digitValue : value to display
 */
void Display4Digit7Segments::DisplayDigit(int digitValue)
{
  for (int i = 0; i < 7; i++) {
    digitalWrite( mSegmentId + i, Segments[digitValue][i]);
  }
}