; ============================================================
; ELECTRIC SHOCK
; Frame Parser
; ============================================================

FRAME_PARSE:

    ; Check synchronization byte.

    LOAD ACC, [FRAME_PTR]

    CMP ACC, #0xA5

    JNZ FRAME_BAD_SYNC

    INC FRAME_PTR


    ; Check protocol version.

    LOAD ACC, [FRAME_PTR]

    CMP ACC, #0x01

    JNZ FRAME_BAD_VERSION

    INC FRAME_PTR


    ; Read message type.

    LOAD ACC, [FRAME_PTR]

    STORE MESSAGE_TYPE, ACC

    INC FRAME_PTR


    ; Read sequence.

    LOAD ACC, [FRAME_PTR]
    STORE RECEIVED_SEQ_H, ACC

    INC FRAME_PTR

    LOAD ACC, [FRAME_PTR]
    STORE RECEIVED_SEQ_L, ACC

    INC FRAME_PTR


    ; Read payload length.

    LOAD ACC, [FRAME_PTR]
    STORE PAYLOAD_LENGTH, ACC

    INC FRAME_PTR


    CALL VALIDATE_LENGTH

    JNZ FRAME_BAD_LENGTH


    CALL VERIFY_FRAME_CRC

    JNZ FRAME_BAD_CRC


    CALL UPDATE_SEQUENCE

    RET


FRAME_BAD_SYNC:

    MOV ERROR_CODE, #0x01
    RET


FRAME_BAD_VERSION:

    MOV ERROR_CODE, #0x02
    RET


FRAME_BAD_LENGTH:

    MOV ERROR_CODE, #0x03
    RET


FRAME_BAD_CRC:

    MOV ERROR_CODE, #0x04
    RET
