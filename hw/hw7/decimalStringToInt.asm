;;=======================================
;; CS 2110 - Spring 2019
;; Homework 7
;;=======================================
;; Name: Molly Williams
;;=======================================

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate Subroutine
;; Call' and choose the 'decimalStringToInt' label.

.orig x3000

halt

MULT
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


AND R1, R1, 0	;sets result = 0

MULTLOOP
ADD R1, R1, R2	;result = result + a
ADD R3, R3, -1	;b--
BRP MULTLOOP

STR R1, R5, 3	;place the return value in the return value place of the stack

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


LENGTH
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

LDR R0, R5, 4	;R0 <= loads string into R0
AND R1, R1, 0	;sets counter to 0
AND R2, R2, 0
LOOP
ADD R2, R1, R0	;sets counter to 1
LDR R2, R2, 0	;loads value of r0 into r4
BRZ BASE
ADD R1, R1, 1	;switches to the next address
BR LOOP


BASE
STR R1, R5, 3	;place the return value in the return value place of the stack

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

decimalStringToInt
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

LDR R0, R5, 4	;stores decimal
ADD R6, R6, -1	;clears parameter for length
STR R0, R6, 0	;stores R0 in R6
JSR LENGTH	;goes to length subroutine, R6 holds the length
LDR R1, R6, 0	;now R1 holds lengtH
ADD R6, R6, 2
AND R2, R2, 0	;sets ret to 0
AND R4, R4, 0	;I = 0

LOOP2
NOT R4, R4
ADD R4, R4, 1
AND R3, R3, 0	;clears R3
ADD R3, R4, R1	;makes sure another loop is needed
BRNZ OUTOFTHIS
ADD R6, R6, -2	;clears 2 spots on stack
LD R3, TEN	;loads 10 into R3
STR R2, R6, 0	;stores ret in R6
STR R3, R6, -1	;stores 10 in R6
JSR MULT
LDR R2, R6, 0	;stores return of MULT in R2
ADD R6, R6, 3	;clears the stack from how it was just manipulated
ADD R4, R4, -1
NOT R4, R4	;restores I to actual number
AND R3, R3, 0	;sets R3 to 0 again
ADD R3, R0, R4	;R3 is now address of current decimal thing
LDR R3, R3, 0	;R3 is now the value of decimal
ADD R2, R2, R3	;ret is now decimal plus old ret
LD R3, NUM	;R3 holds 48
NOT R3, R3
ADD R3, R3, 1	;R3 now holds -48
ADD R2, R2, R3	;R2 holds correct return for that loop

ADD R4, R4, 1	;increments I
BRZP LOOP2

OUTOFTHIS

STR R2, R5, 3

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


NUM .fill 48
; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
STRING .fill x6000
TEN .fill 10
.end

.orig x6000
.stringz "10098"
.end
