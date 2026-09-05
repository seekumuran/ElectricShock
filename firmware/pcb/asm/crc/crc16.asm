; ============================================================
; ELECTRIC SHOCK
; PCB CRC16
; ============================================================

CRC16_INIT:

    MOV CRC_H, #0xFF
    MOV CRC_L, #0xFF

    RET


CRC16_UPDATE:

    XOR CRC_H, ACC

    MOV BIT_COUNT, #8


CRC_LOOP:

    TEST CRC_H, #0x80

    SHL CRC_L
    ROL CRC_H

    IF_SET:

        XOR CRC_H, #0x10
        XOR CRC_L, #0x21

    DEC BIT_COUNT

    JNZ CRC_LOOP

    RET
