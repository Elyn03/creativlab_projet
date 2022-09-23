/*!
   Arduino digital meter manager project
   Autor : thlg
   File : Display4Digit7Segments.h

   Based on Haljia Arduino starter kit
   http://www.haljia.com/
   Component :
   - Arduino Uno
   - 4 digits/7 segments Led display 5641BH

   Released under the MIT license
   https://opensource.org/licenses/MIT

   Date: 2017-12-27
*/

#ifndef Display4Digit7Segments_h
#define Display4Digit7Segments_h

#include <Arduino.h>

#define SEGMENT_OFF 10
#define SEGMENT_UNKNOW 11

/*
   Arduino digital meter manager
*/
class Display4Digit7Segments
{
  public:
    /*
      Clas constructor

      segmentIdBase : Arduino port id for A segment
                      Segments B, C, D, E, F and G must be the next
      digitIdBase   : Arduino port id for digit 1
                      Digits 2, 3 and 4 must be the next.
    */
    Display4Digit7Segments(int segmentIdBase, int digitIdBase);

    /*
      Initialize pinMode for segments and digits
      Must be call from arduino setup() method
    */
    void Setup();

    /*
      Display a number.

      value : value to display
              Value must be greater than 0
    */
    void Display(int value);

    /*
      Display a number

      value            : value to display
                         Value must be greater than 0
      nbDigitToDisplay : Digit max count
                         Must be between 1 to 4
    */
    void Display(int value, int nbDigitToDisplay);

  private:
    int mSegmentId;
    int mDigitId;
    int mDigits[5];
    unsigned long mPreviousMillis = 0;
    const int MaxDigit = 4;
    const int DTime = 4;
    const byte Segments[12][8] = {
      // A     B     C     D     E     F     G
      { LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  HIGH }, // 0
      { HIGH, LOW,  LOW,  HIGH, HIGH, HIGH, HIGH }, // 1
      { LOW,  LOW,  HIGH, LOW,  LOW,  HIGH, LOW }, // 2
      { LOW,  LOW,  LOW,  LOW,  HIGH, HIGH, LOW }, // 3
      { HIGH, LOW,  LOW,  HIGH, HIGH, LOW,  LOW }, // 4
      { LOW,  HIGH, LOW,  LOW,  HIGH, LOW,  LOW }, // 5
      { LOW,  HIGH, LOW,  LOW,  LOW,  LOW,  LOW }, // 6
      { LOW,  LOW,  LOW,  HIGH, HIGH, HIGH, HIGH  }, // 7
      { LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW }, // 8
      { LOW,  LOW,  LOW,  LOW,  HIGH, LOW,  LOW }, // 9
      { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH },  // all off
      { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW }  // -
    };

    void GetDigits(int value);
    void DisplayDigits(int nbDigitToDisplay);
    void DisplayDigit(int digitValue);
};

#endif