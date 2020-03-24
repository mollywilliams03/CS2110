;;=============================================================
;;CS 2110 - Spring 2019
;;Homework 6 - Phone Number
;;=============================================================
;;Name: Molly Williams
;;=============================================================

.orig x3000

LD R0, STRING	;loads R0 with the string
AND R1, R1, 0	;sets r1 to 0
AND R2, R2, 0	;sets r2 to 0
ADD R2, R2, 14	;sets r2 to 14

LOOP
LD R6, STRING 	;loads string into r6
NOT R5, R0	;subtraction
ADD R5, R5, 1
ADD R5, R5, R6
BRZ FIRST	;branch to first
LD R6, FOUR	;loads four into r6
NOT R5, R0	;subtraction
ADD R5, R5, 1
ADD R5, R5, R6
BRZ FOURTH	;branch to fourth
LD R6, FIVE	;loads five into r6
NOT R5, R0	;subtraction
ADD R5, R5, 1
ADD R5, R5, R6
BRZ FIFTH	;branch to fifth
LD R6, NINE	;loads nine into r6
NOT R5, R0	;subtraction
ADD R5, R5, 1
ADD R5, R5, R6
BRZ NINTH	;branch to 9

;if should be a number 0-9
LDR R4, R0, 0	;loads value of r0 into r4
LD R3, ZERO	;loads zero into r3
NOT R3, R3	;negates r3
ADD R3, R3, 1	;2s substitution
ADD R3, R3, R4	;checks for 0
BRN SETTOZERO
LD R3, HIGH	;loads high into r3
NOT R3, R3	;subtraction
ADD R3, R3, 1
ADD R3, R3, R4
BRP SETTOZERO

CHECK
ADD R1, R1, 1	;increments R1
LDR R4, R0, 0	;loads value of r0 into r4
ADD R4, R4, 0	;checks for 0
BRZ SETTOZERO
ADD R0, R0, 1	;switches to the next address
NOT R3, R2	;subtraction
ADD R3, R3, 1
ADD R3, R3, R1
BRN LOOP
LDR R4, R0, 0	;loads value of r0 into r4
ADD R4, R4, 0	;checks for 0
BRZ END
BRNP SETTOZERO



;I = 0
FIRST
LDR R6, R0, 0	;puts element from current address into R6
AND R7, R7, 0	;sets R7 to 0
ADD R7, R7, 15	;Puts 40 in R7
ADD R7, R7, 15
ADD R7, R7, 10
NOT R7, R7	;subtraction
ADD R7, R7, 1
ADD R7, R7, R6	;checks to see if same
BRZ CHECK
BR SETTOZERO

;I = 4
FOURTH
LDR R6, R0, 0	;puts element from current address into R6
AND R7, R7, 0	;sets R7 to 0
ADD R7, R7, 15	;Puts 41 in R7
ADD R7, R7, 15
ADD R7, R7, 11
NOT R7, R7	;negates R7
ADD R7, R7, 1	;2s compliment
ADD R7, R7, R6	;checks to see if same
BRZ CHECK
BR SETTOZERO

;I = 5
FIFTH
LDR R6, R0, 0	;puts element from current address into R6
AND R7, R7, 0	;sets R7 to 0
ADD R7, R7, 15	;Puts 32 in R7
ADD R7, R7, 15
ADD R7, R7, 2
NOT R7, R7	;negates R7
ADD R7, R7, 1	;2s compliment
ADD R7, R7, R6	;checks to see if same
BRZ CHECK
BR SETTOZERO

;I = 9
NINTH
LDR R6, R0, 0	;puts element from current address into R6
AND R7, R7, 0	;sets R7 to 0
ADD R7, R7, 15	;Puts 45 in R7
ADD R7, R7, 15
ADD R7, R7, 15
NOT R7, R7	;negates R7
ADD R7, R7, 1	;2s compliment
ADD R7, R7, R6	;checks to see if same
BRZ CHECK

SETTOZERO
AND R2, R2, 0
ST R2, ANSWER	;stores answer in r2
HALT
END 
AND R2, R2, 0
ADD R2, R2, 1
ST R2, ANSWER	;stores answer in r2
HALT

FOUR .fill x4004
FIVE .fill x4005
NINE .fill x4009
ZERO .fill 48
HIGH .fill 57
STRING .fill x4000
ANSWER .blkw 1
.end

.orig x4000
.stringz "(704) 555-2110"
.end