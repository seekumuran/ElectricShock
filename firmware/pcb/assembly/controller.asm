; ============================================================
; ELECTRIC SHOCK
; PCB CONTROLLER FIRMWARE
; ============================================================
;
; PCB version uses the same logical data pipeline as the
; breadboard version but isolates hardware access so the
; electrical implementation can change independently.
; ============================================================

            .section .text


RESET:

            CALL SYSTEM_INIT

LOOP:

            CALL INPUT_SAMPLE
            CALL INPUT_PROCESS
            CALL STATE_PACK
            CALL FRAME_BUILD
            CALL FRAME_CRC
            CALL FRAME_SEND
            CALL SEQUENCE_NEXT

            JMP LOOP


; ============================================================
; SYSTEM
; ============================================================

SYSTEM_INIT:

            CALL STACK_INIT
            CALL CLOCK_INIT
            CALL GPIO_INIT
            CALL ADC_INIT
            CALL TIMER_INIT
            CALL TRANSPORT_INIT

            RET


STACK_INIT:

            ; Initialize stack
            RET


CLOCK_INIT:

            ; Initialize system clock
            RET


GPIO_INIT:

            ; Configure PCB digital inputs
            RET


ADC_INIT:

            ; Configure joystick channels
            RET


TIMER_INIT:

            ; Configure periodic sampling
            RET


TRANSPORT_INIT:

            ; Configure USB/UART/serial transport
            RET


; ============================================================
; INPUT
; ============================================================

INPUT_SAMPLE:

            CALL READ_BUTTONS
            CALL READ_LEFT_STICK
            CALL READ_RIGHT_STICK
            CALL READ_TRIGGERS

            RET


READ_BUTTONS:

            ; Read all digital controller inputs
            RET


READ_LEFT_STICK:

            ; ADC X/Y
            RET


READ_RIGHT_STICK:

            ; ADC X/Y
            RET


READ_TRIGGERS:

            ; ADC/digital trigger inputs
            RET


; ============================================================
; PROCESSING
; ============================================================

INPUT_PROCESS:

            CALL BUTTON_DEBOUNCE
            CALL JOYSTICK_FILTER
            CALL JOYSTICK_DEADZONE
            CALL AXIS_NORMALIZE

            RET


BUTTON_DEBOUNCE:

            RET


JOYSTICK_FILTER:

            RET


JOYSTICK_DEADZONE:

            RET


AXIS_NORMALIZE:

            RET


; ============================================================
; STATE
; ============================================================

STATE_PACK:

            ; Convert controller inputs into compact state.

            RET


; ============================================================
; FRAME
; ============================================================

FRAME_BUILD:

            ; SYNC
            ; TYPE
            ; SEQUENCE
            ; FLAGS
            ; LENGTH
            ; PAYLOAD

            RET


FRAME_CRC:

            CALL CRC16_INIT

            ; Feed frame bytes to CRC16_UPDATE.

            RET


FRAME_SEND:

            ; Send completed frame.

            RET


SEQUENCE_NEXT:

            INC SEQ_L

            JNZ SEQUENCE_DONE

            INC SEQ_H

SEQUENCE_DONE:

            RET
