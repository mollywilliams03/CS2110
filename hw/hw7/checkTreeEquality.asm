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

checkTreeEquality
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

LDR R0, R5, 4	;R0 <= loads B1 into param1 (address)
BRZ B1ZERO
LDR R1, R5, 5	;loads B2 into param2 (address)
BRZ B2ZERO

;;now we know b1 and b2 are both not zero
LDR R2, R0, 2
LDR R3, R1, 2
NOT R2, R2
ADD R2, R2, 1
ADD R2, R2, R3	;checks to see if values match
BRNP RETURNZERO
LDR R2, R0, 2
ADD R6, R6, -2	;clears 2 spots for children
LDR R2, R0, 0	;loads left child
LDR R3, R1, 0	;loads left child
STR R2, R6, 0	;left child b1
STR R3, R6, 1	;left child b2
JSR checkTreeEquality	;checks is left children are same
LDR R4, R6, 0	;stores either 1 or 0 depending on subroutine
BRZ RETURNZERO
ADD R6, R6, -2	;clears 2 spots for parameter
LDR R2, R0, 1	;loads left child
LDR R3, R1, 1	;loads left child
STR R2, R6, 0	;checks right child B1
STR R3, R6, 1	;checks right child B2
JSR checkTreeEquality
LDR R4, R6, 0	;loads result into R4
BRZ RETURNZERO
BR RETURNONE


B1ZERO
ADD R2, R2, 0	;to check if both trees are empty
BRZ RETURNONE
BR RETURNZERO
;;done with B1ZERO

B2ZERO
;;we know B1 is not zero and B2 is zero
BR RETURNZERO
;;done with B2ZERO

RETURNONE
AND R4, R4, 0
ADD R4, R4, 1
BR END

RETURNZERO
AND R4, R4, 0

END

STR R4, R5, 3

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


; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end
