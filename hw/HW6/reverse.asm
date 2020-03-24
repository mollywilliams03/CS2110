;;=============================================================
;;CS 2110 - Spring 2019
;;Homework 6 - Reverse
;;=============================================================
;;Name: Molly Williams
;;=============================================================

.orig x3000
LD R0, ARRAY	;Loads array into R0
LD R6, LENGTH	;Loads length into R6
AND R1, R1, 0	;Sets R1 to 0
AND R2, R2, 0	;Sets R2 to 0
ADD R2, R6, -1	;Sets R2 to length - 1
LOOP
AND R5, R5, 0	;Sets R5 to 0
ADD R5, R0, R1	;puts address of first element into R5
LDR R3, R5, 0	;R3 holds first element in array
AND R7, R7, 0	;Sets R7 to 0
ADD R7, R0, R2	;puts address of last element in R7
LDR R4, R7, 0	;R4 holds last element
STR R3, R7, 0	;stores first element in last address
STR R4, R5, 0	;stores last element in first address
ADD R1, R1, 1	;increments R1
ADD R2, R2, -1	;decrements R2
AND R5, R5, 0	;sets R5 to 0
NOT R5, R2	;subtraction
ADD R5, R5, 1
ADD R5, R5, R1
BRNZ LOOP	;loops

HALT



ARRAY .fill x4000
LENGTH .fill 7
.end

.orig x4000
.fill 2
.fill 9
.fill 7
.fill 0
.fill 5
.fill 3
.fill 10
.end
