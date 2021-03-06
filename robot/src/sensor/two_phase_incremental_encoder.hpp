#ifndef TWO_PHASE_INCREMENTAL_ENCODER_H
#define TWO_PHASE_INCREMENTAL_ENCODER_H

#include <arduino/Arduino.h>
#include <arduino/wiring_private.h>// for voidFuncPtr
//#include <macro/macro.h>

namespace crim {

class TwoPhaseIncrementalEncoder {
 public:
  TwoPhaseIncrementalEncoder(size_t out_a_pin, size_t out_b_pin, uint64_t resolution);
  ~TwoPhaseIncrementalEncoder();
  
  /**
   * @brief return the number of rising-edge of the a phase pulse
   * 
   */


  int64_t pos();
  double rot();
  void reset_Enc();
  
 private:
  size_t out_a_pin_;// external interrupt 0 pin
  size_t out_b_pin_;// external interrupt 1 pin
  uint64_t resolution_;
  static int64_t counter_;
  static bool phase_a_state_;
  static bool phase_b_state_;
  
  void ext_int0_handler();
  void ext_int1_handler();
};

}// namespace crim

#endif
