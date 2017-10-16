# TM4C123G

Tiva C Series TM4C123GH6PM Launchpad Code.

# Generic

* Not yet added

# FreeRTOS

Recreating examples with the FreeRTOS

*NOTE: Default Folder contains FreeRTOSConfig.h file and mainTest.c file for
testing with MCU*

*All the examples are built on top of the mainTest.c file*


### Libs

 * `Serial.h`
    * Serial Communication library
* `Utility.h`
    * Utility library commonly used functions


### Example Programs

* Blinky
    * Uses the default mainTest.c file to blink the led.

* Serial
    * Blinks while printing to the screen
    * Also makes use of the `vTaskDelayUntil` function.

* IdleHook
    * Make sure `configUSE_IDLE_HOOK` is set to **1** in FreeRTOSConfig.h
    * When the functions aren't running `vApplicationIdleHook` is called
    * We can use the idle hook to print common background messages

* PriorityLevel
    * We can change the priority level of Tasks dynamically

* TaskDelete
    * We can delete a task dynamically
    * Task1 creates Task2
    * Task2 just deletes itself
