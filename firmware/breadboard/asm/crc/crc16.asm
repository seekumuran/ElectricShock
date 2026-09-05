; ============================================================
; ELECTRIC SHOCK
; CRC16
;
; Polynomial : 0x1021
; Initial    : 0xFFFF
;
; Input:
;     ACC = data byte
;
; State:
;     CRC_H
;     CRC_L
;
; Output:
;     CRC_H:CRC_L
; ============================================================

CRC16_INIT:

    MOV CRC_H, #0xFF
    MOV CRC_L, #0xFF

    RET


CRC16_UPDATE:

    XOR CRC_H, ACC

    MOV BIT_COUNT, #8


CRC16_BIT_LOOP:

    ; Preserve the outgoing MSB.

    TEST CRC_H, #0x80


    ; Shift 16-bit CRC left.

    SHL CRC_L
    ROL CRC_H


    ; Polynomial 0x1021

    IF_SET:

        XOR CRC_H, #0x10
        XOR CRC_L, #0x21


    DEC BIT_COUNT

    JNZ CRC16_BIT_LOOP

    RET
