; ============================================================
; ELECTRIC SHOCK
; Breadboard Frame Builder
; ============================================================

FRAME_BUILD:

    ; --------------------------------------------------------
    ; SYNC
    ; --------------------------------------------------------

    MOV ACC, #0xA5
    CALL FRAME_WRITE


    ; --------------------------------------------------------
    ; VERSION
    ; --------------------------------------------------------

    MOV ACC, #0x01
    CALL FRAME_WRITE


    ; --------------------------------------------------------
    ; MESSAGE TYPE
    ; --------------------------------------------------------

    MOV ACC, #0x01
    CALL FRAME_WRITE


    ; --------------------------------------------------------
    ; SEQUENCE
    ; --------------------------------------------------------

    MOV ACC, SEQ_H
    CALL FRAME_WRITE

    MOV ACC, SEQ_L
    CALL FRAME_WRITE


    ; --------------------------------------------------------
    ; PAYLOAD LENGTH
    ; --------------------------------------------------------

    MOV ACC, #INPUT_PAYLOAD_LENGTH
    CALL FRAME_WRITE


    ; --------------------------------------------------------
    ; PAYLOAD
    ; --------------------------------------------------------

    CALL WRITE_INPUT_PAYLOAD

    RET


WRITE_INPUT_PAYLOAD:

    MOV ACC, BUTTON_STATE
    CALL FRAME_WRITE

    MOV ACC, JOY_X_L
    CALL FRAME_WRITE

    MOV ACC, JOY_Y_L
    CALL FRAME_WRITE

    RET


FRAME_WRITE:

    ; TODO:
    ; FRAME_PTR -> destination
    ; ACC       -> byte

    STORE [FRAME_PTR], ACC

    INC FRAME_PTR

    RET
