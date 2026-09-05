; ============================================================
; ELECTRIC SHOCK
; Breadboard Controller Firmware
; ============================================================
;
; Pipeline:
;   INPUT -> DEBOUNCE -> STATE -> SERIALIZE -> CRC -> TX
;
; Hardware-specific register definitions are intentionally
; isolated at the top of this file.
; ============================================================

            .section .text

; ------------------------------------------------------------
; Hardware configuration
; ------------------------------------------------------------

BUTTON_PORT     EQU 0x10
JOYSTICK_X      EQU 0x20
JOYSTICK_Y      EQU 0x21
UART_DATA       EQU 0x30
UART_STATUS     EQU 0x31

UART_READY      EQU 0x01

CRC_INIT_H      EQU 0xFF
CRC_INIT_L      EQU 0xFF

; ------------------------------------------------------------
; RAM
; ------------------------------------------------------------

BUTTON_STATE    EQU 0x80
BUTTON_PREV    EQU 0x81

JOY_X_H         EQU 0x82
JOY_X_L         EQU 0x83
JOY_Y_H         EQU 0x84
JOY_Y_L         EQU 0x85

SEQ_H           EQU 0x86
SEQ_L           EQU 0x87

CRC_H           EQU 0x88
CRC_L           EQU 0x89

FRAME_INDEX     EQU 0x8A

; ------------------------------------------------------------
; RESET
; ------------------------------------------------------------

RESET:

            CALL INIT

MAIN_LOOP:

            CALL SAMPLE_INPUTS
            CALL DEBOUNCE
            CALL BUILD_STATE
            CALL BUILD_FRAME
            CALL CALCULATE_CRC
            CALL TRANSMIT_FRAME

            CALL INCREMENT_SEQUENCE

            JMP MAIN_LOOP


; ============================================================
; INITIALIZATION
; ============================================================

INIT:

            CALL INIT_STACK
            CALL INIT_GPIO
            CALL INIT_ADC
            CALL INIT_UART

            MOV BUTTON_STATE, #0
            MOV BUTTON_PREV,  #0

            MOV SEQ_H, #0
            MOV SEQ_L, #0

            RET


INIT_STACK:

            ; Hardware-specific stack initialization
            RET


INIT_GPIO:

            ; Configure button inputs
            RET


INIT_ADC:

            ; Configure joystick ADC channels
            RET


INIT_UART:

            ; Configure serial interface
            RET


; ============================================================
; INPUT ACQUISITION
; ============================================================

SAMPLE_INPUTS:

            LOAD ACC, [BUTTON_PORT]
            STORE BUTTON_STATE, ACC

            LOAD ACC, [JOYSTICK_X]
            STORE JOY_X_L, ACC

            LOAD ACC, [JOYSTICK_Y]
            STORE JOY_Y_L, ACC

            RET


; ============================================================
; BUTTON DEBOUNCE
; ============================================================

DEBOUNCE:

            LOAD ACC, BUTTON_STATE
            XOR  ACC, BUTTON_PREV

            ; ACC now contains changed bits.

            LOAD TEMP, BUTTON_STATE
            STORE BUTTON_PREV, TEMP

            RET


; ============================================================
; CONTROLLER STATE
; ============================================================

BUILD_STATE:

            ; Normalize joystick values here if required.

            ; Button state:
            ;   BUTTON_STATE

            ; Joystick:
            ;   JOY_X_L
            ;   JOY_Y_L

            RET


; ============================================================
; FRAME
; ============================================================

BUILD_FRAME:

            ; Frame:
            ;
            ; 0  SYNC
            ; 1  TYPE
            ; 2  SEQ_H
            ; 3  SEQ_L
            ; 4  BUTTONS
            ; 5  JOY_X
            ; 6  JOY_Y
            ; 7  CRC_H
            ; 8  CRC_L

            RET


; ============================================================
; CRC16
; Polynomial: 0x1021
; Initial value: 0xFFFF
; ============================================================

CALCULATE_CRC:

            MOV CRC_H, #CRC_INIT_H
            MOV CRC_L, #CRC_INIT_L

            ; Process protocol bytes here.
            ; The loop below is the reference bitwise algorithm.

            MOV COUNT, #8

CRC_BYTE:

            ; DATA_REG must contain current byte.

            XOR CRC_H, DATA_REG

            MOV BIT_COUNT, #8

CRC_BIT:

            SHL CRC_L
            ROL CRC_H

            ; Carry handling is MCU-specific.
            ; If carry was set before the shift:

            IF_CARRY:
                XOR CRC_H, #0x10
                XOR CRC_L, #0x21

            DEC BIT_COUNT
            JNZ CRC_BIT

            DEC COUNT
            JNZ CRC_BYTE

            RET


; ============================================================
; TRANSMISSION
; ============================================================

TRANSMIT_FRAME:

            ; Wait until transport is ready.

WAIT_TX:

            LOAD ACC, [UART_STATUS]
            AND  ACC, #UART_READY
            JZ   WAIT_TX

            ; Send frame bytes.

            LOAD ACC, #0xA5
            CALL UART_SEND

            LOAD ACC, #0x01
            CALL UART_SEND

            LOAD ACC, SEQ_H
            CALL UART_SEND

            LOAD ACC, SEQ_L
            CALL UART_SEND

            LOAD ACC, BUTTON_STATE
            CALL UART_SEND

            LOAD ACC, JOY_X_L
            CALL UART_SEND

            LOAD ACC, JOY_Y_L
            CALL UART_SEND

            LOAD ACC, CRC_H
            CALL UART_SEND

            LOAD ACC, CRC_L
            CALL UART_SEND

            RET


UART_SEND:

            STORE [UART_DATA], ACC

UART_WAIT:

            LOAD TEMP, [UART_STATUS]
            AND TEMP, #UART_READY
            JZ UART_WAIT

            RET


; ============================================================
; SEQUENCE
; ============================================================

INCREMENT_SEQUENCE:

            INC SEQ_L

            JNZ SEQ_DONE

            INC SEQ_H

SEQ_DONE:

            RET
