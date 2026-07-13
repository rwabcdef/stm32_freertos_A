/*
 * swTimer.h
 *
 *  Created on: 13 July 2026
 *      Author: rob
 */

 #ifndef SWTIMER_H_
 #define SWTIMER_H_
 
 #include "timer2.h"
 
 
 #define BASE_TICK g_timer2Tick
 //------------------------------------------------------------------------------
 
 //------------------------------------------------------------------------------
 //------------------------------------------------------------------------------
 
 static inline void swTimer_tickReset(uint16_t* tickCount)
 {
   *tickCount = BASE_TICK;
 }
 //------------------------------------------------------------------------------
 
 static inline uint32_t swTimer_tickElapsed(uint16_t startTick)
 {
   return (BASE_TICK - startTick);
 }
 
 //------------------------------------------------------------------------------
 
 static inline bool swTimer_tickCheckTimeout(uint16_t* tickCount, uint16_t timeoutTicks)
 {
   if(swTimer_tickElapsed(*tickCount) >= timeoutTicks)
   {
     swTimer_tickReset(tickCount);
     return true;
   }
   return false;
 }
 
 //------------------------------------------------------------------------------
 
 static inline bool swTimer_tickCheckTimeoutNoReset(uint16_t* tickCount, uint16_t timeoutTicks)
 {
   if(swTimer_tickElapsed(*tickCount) >= timeoutTicks)
   {
     return true;
   }
   return false;
 }
 
 //------------------------------------------------------------------------------
 //------------------------------------------------------------------------------
 
 
 #endif /* SWTIMER_H_ */
 