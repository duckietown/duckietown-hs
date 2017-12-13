#ifndef TCS3200_H
#define TCS3200_H
 
#include "mbed.h"
 
class TCS3200 {
  public:

    /** Create a TCS3200 object connected to the specified pins.
    * @param S0 Frequency scaling output pin S0
    * @param S1 Frequency scaling output pin S1
    * @param S2 Photo diode selection output pin S2
    * @param S3 Photo diode selection output pin S3
    * @param OUT Frequency input pin
    */
    TCS3200(PinName S0, PinName S1, PinName S2, PinName S3, PinName OUT);
    
    enum TCS3200Mode {
        POWERDOWN = 0,
        SCALE_2 = 1,
        SCALE_20 = 2,
        SCALE_100 = 3,
    };


    /** Reads the output signal's HIGH pulse for RED.
    * @param 
    *     None
    * @return 
    *     Duration as nanoseconds (ns).
    */
    long ReadRed();
    
    /** Reads the output signal's HIGH pulse for GREEN.
    * @param 
    *     None
    * @return 
    *     Duration as nanoseconds (ns).
    */
    long ReadGreen();
    
    /** Reads the output signal's HIGH pulse for BLUE.
    * @param 
    *     None
    * @return 
    *     Duration as nanoseconds (ns).
    */
    long ReadBlue();
    
    /** Reads the output signal's HIGH pulse for CLEAR.
    * @param 
    *     None
    * @return 
    *     Duration as nanoseconds (ns).
    */
    long ReadClear();
    
    /** Sets the mode of operation. 
    * @param 
    *     mode POWERDOWN, SCALE_2 (2% scaling), SCALE_20 (20% scaling), SCALE_100 (100% scaling).
    * @return 
    *     None
    */
    void SetMode(TCS3200Mode mode);
    
  private:
    DigitalOut mS0;
    DigitalOut mS1;
    DigitalOut mS2;
    DigitalOut mS3;
    InterruptIn signal;
    Timer timer;
    long pulsewidth;
    void HighTrigger();
    void LowTrigger();
};
 
#endif
