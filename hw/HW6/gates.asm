;;=============================================================
;;CS 2110 - Spring 2019
;;Homework 6 - Gates
;;=============================================================
;;Name: Molly Williams
;;=============================================================

.orig x3000
LD R1, A	;R1 = A
LD R2, B	;R2 = B
LD R0, X	;R0 = X

;A minus X
NOT R3, R0	;negates R3 for subtraction
ADD R3, R3, 1	;Finished 2's compliment
AND R5, R5, 0	;Sets R5 to 0
ADD R5, R3, R1	;A-X
BRN BMINUSXNEG
BRP BMINUSXPOS
BRZ ELSE


BMINUSXPOS
NOT R3, R0	;negates R3 for subtraction
ADD R3, R3, 1	;Finished 2's compliment
AND R5, R5, 0	;Sets R5 to 0
ADD R5, R3, R2	;B-X
BRN NAND
BRP NOR
BRZ ELSE



BMINUSXNEG
NOT R3, R0	;negates R3 for subtraction
ADD R3, R3, 1	;Finished 2's compliment
AND R5, R5, 0	;Sets R5 to 0
ADD R5, R3, R2	;B-X
BRN OR
BRP ANDD
BRZ ELSE


NAND
AND R3, R3, 0
AND R3, R1, R2	;R3 = A && B
AND R4, R4, 0
NOT R4, R3	;R4 = Not(R3)
ST R4, ANSWER	;Returns the ANSWER

HALT

NOR
NOT R3, R1	;R3 = Not A
NOT R4, R2	;R4 = Not B
AND R5, R5, 0
AND R5, R3, R4	;R5 = Not A and Not B
ST R5, ANSWER	;Returns the ANSWER

HALT

OR
NOT R3, R1	;R3 = Not A
NOT R4, R2	;R4 = Not B
AND R5, R5, 0
AND R5, R3, R4	;R5 = Not A and Not B
NOT R6, R5	;R6 = Not R5
ST R6, ANSWER	;Returns the ANSWER

HALT

ANDD
AND R3, R3, 0
AND R3, R1, R2	;R3 = A and B
ST R3, ANSWER	;Returns the ANSWER

HALT

ELSE
NOT R3, R1	;R3 = Not A
ST R3, ANSWER	;Returns the ANSWER

HALT

A   .fill x3030
B   .fill x4040
X   .fill x4040

INDEX .blkw 1

ANSWER .blkw 1

.end
