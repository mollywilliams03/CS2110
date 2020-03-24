;;=============================================================
;;CS 2110 - Spring 2019
;;Homework 6 - Linked List
;;=============================================================
;;Name: Molly Williams
;;=============================================================

.orig x3000
AND R2, R2, 0	;sets R2 to 0
LD R6, DATA	;loads R6 with data
LDI R0, LL	;loads R0 with LL, which is the head
LOOP LDR R1, R0, 0	;loads the next address into R1
AND R0, R0, 0	;clears R0
ADD R0, R1, 0	;loads R1 into R0
ADD R2, R2, 1	;counter for length
ADD R0, R0, 0	;checks if the current node is null
BRNP LOOP	;Breaks to null if list is null
LDI R0, LL	;loads R0 with LL, which is the head
LOOP2 LDR R1, R0, 0	;loads the next address into R1
AND R3, R3, 0	;sets R3 to 0
ADD R3, R0, 1	;gets the address for storing
LDR R4, R3, 0	;loads R4 with memory of R3
NOT R4, R4	;negates R4 for subtraction
ADD R4, R4, 1	;Finished 2's compliment
AND R5, R5, 0	;Sets R5 to 0
ADD R5, R4, R6	;subtracts R4 and R2
BRz MATCH	;Branches to match if they match
AND R0, R0, 0	;clears R0
ADD R0, R1, 0	;loads R1 into R0
ADD R0, R0, 0	;checks if the current node is null
BRNP LOOP2	;Breaks to null if list is null
BR DONE
MATCH STR R2, R0, 1 ;stores length in address of current node +1
AND R0, R0, 0	;clears R0
ADD R0, R1, 0	;loads R1 into R0
ADD R0, R0, 0	;checks if the current node is null
BRNP LOOP2	;Breaks to null if list is null
DONE
HALT



DATA .fill 10
LL .fill x6000
.end

.orig x4000
.fill x4008
.fill 5
.fill x400A
.fill 2
.fill x4002
.fill 9
.fill x0000 
.fill 3
.fill x4004
.fill 10
.fill x4006
.fill 7
.end

.orig x6000
.fill x4000
.fill 6
.end
