;;=======================================
;; CS 2110 - Spring 2019
;; Timed Lab 4
;;=======================================
;; Name: Molly Williams
;;=======================================

;; A little reminder from your friendly neighborhood 2110 TA staff:
;; Do not try to run this directly by pressing 'RUN' in Complx.
;; Instead, load it and use 'Debug' -> 'Simulate Subroutine Call'
;; and choose the 'countMult7' label.

.orig x3000

halt ; Do not remove this line – see note above

; mod(a, b)
;
; This looks funky, but it is a subroutine you can call
; like normal. Just be sure to use the LC3 calling convention!
;
; return 1 if a % b == 0 and 0 otherwise
mod
    .fill x1dbf
    .fill x1dbf
    .fill x7f80
    .fill x1dbf
    .fill x7b80
    .fill x1dbf
    .fill x1ba0
    .fill x1dbe
    .fill x7381
    .fill x7580
    .fill x6344
    .fill x6545
    .fill x94bf
    .fill x14a1
    .fill x1242
    .fill x0402
    .fill x0805
    .fill x03fc
    .fill x5260
    .fill x1261
    .fill x7343
    .fill x0e02
    .fill x5260
    .fill x7343
    .fill x6580
    .fill x6381
    .fill x1d63
    .fill x6f42
    .fill x6b41
    .fill xc1c0

; return count of arguments that are multiples of 7
countMult7 ; countMult7(a, ...)
    ; TODO Stack SETUP code here
ADD R6, R6, -4 ;place stack pointer to build up first portion of the stack (a)
STR R7, R6, 2  ;save old return address
STR R5, R6, 1  ;save old frame pointer
ADD R5, R6, 0  ;set current frame pointer
ADD R6, R6, -5 ;place stack pointer to save all of the registers on the stack (b)
STR R0, R5, -1  ;save R0
STR R1, R5, -2  ;save R1
STR R2, R5, -3  ;save R2
STR R3, R5, -4  ;save R3
STR R4, R5, -5  ;save R4

AND R3, R3, 0	;counter
LDR R0, R5, 4	;loads first number
ST R0, CHECKPOINT1	;stores value in checkpoint1
BRNZ OUTLOOP
AND R1, R1, 0
ADD R1, R6, 10
ST R1, CHECKPOINT2
;ADD R1, R1, -1	;brings to first address


BEGINLOOP
LDR R2, R1, 0
ADD R6, R6, -2	;clears spots for parameter
AND R4, R4, 0
ADD R4, R4, 7
STR R2, R6, 0
STR R4, R6, 1
JSR mod
LDR R4, R6, 0	;stores return of mod
BRZ SKIPCOUNT
ADD R3, R3, 1
SKIPCOUNT
ADD R6, R6, 3
ADD R1, R1, 1
ADD R0, R0, -1
BRP BEGINLOOP


OUTLOOP
STR R3, R5, 3
    ; TODO your TEARDOWN code here
LDR R4, R5, -5 ;restore R4
LDR R3, R5, -4 ;restore R3
LDR R2, R5, -3 ;restore R2
LDR R1, R5, -2 ;restore R1
LDR R0, R5, -1 ;restore R0
ADD R6, R5, 0  ;bring R6 back down to R5
LDR R5, R6, 1  ;restore old frame pointer
LDR R7, R6, 2  ;restore return address
ADD R6, R6, 3  ;have R6 point to the return value
RET

; Do not remove or modify anything below this line
; Needed for subroutine calls and grading
STACK .fill xF000
CHECKPOINT1 .blkw 1 ; Should store n
CHECKPOINT2 .blkw 1 ; Should store address of first variable argument

.end
