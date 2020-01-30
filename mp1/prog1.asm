; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code

;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

        ; note that we no longer need the current character
        ; so we can reuse R2 for the pointer to the correct
        ; histogram entry for incrementing

ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

        ; subtracting as below yields the original character minus '`'

MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop
				

PRINT_HIST
				; New code starts here
	AND R6, R6, #0          ; RESET R1,
PRINT 
	LD R1, LOOPS            ; Load Loops value into R1
	LD R0, SYMBOL           ; Load first symbol
        ADD R0, R0, R6          ; Add 
	OUT		        ; Print symbol
	LD R0, SPACE            ; Load Space
	OUT		        ; Print Space
	ADD R6, R6, #1          ; Increment R6

        AND R0, R0, #0          ; clear R0 (digit)
        AND R1, R1, #0          ; clear R1 (bit counter)
        AND R2, R2, #0          ; clear R2 (digit counter)
        AND R3, R3, #0          ; clear R3 (value)
        AND R4, R4, #0          ; clear R4 (offset)
	AND R5, R5, #0          ;

        LDI R3, HIST_ADDR       ; 
        LD R5, HIST_ADDR        ;
	ADD R5, R5, #1          ;
	ST R5, HIST_ADDR        ;

        ADD R2, R2, #8
        ADD R2, R2, #8          ; R2 holds 16

BITSTRING  
        ADD R1, R1, #4          ; R1 = 4
        AND R0, R0, #0          ; clear R0 (digit)
        AND R5, R5, #0          ; clear R5 (test value)

DIGLOOP
        ADD R0, R0, R0          ; left shift R0
        ADD R3, R3, #0          ; bring R3 in front of BRANCH statement
        BRzp NEXTDIG            ; skip adding 1 if R3 has 0 in MSB
        ADD R0, R0, #1          ; add 1 if MSB is 1
NEXTDIG    
        ADD R3, R3, R3          ; left shift for next digit check
        ADD R1, R1, #-1         ; decrease bit counter
        BRp DIGLOOP             ; decrease 

        LD R4, NINEOFFSET       ; load R4 with the offset for numbers 0 to 9 if the number is less than 10
        ADD R5, R0, #-9         ; check if R0 holds 9
        BRnz ADDOFFSET          ; branch to ADDOFFSET if number is less than 9
TENOFF 
        LD R4, AOFFSET          ; load R4 with the offset for numbers 10 to 15 if the number is greater than 10

ADDOFFSET
        ADD R0, R0, R4          ; add the offset to the hex for the digit
        OUT                     ; print the correct ASCII
        ADD R2, R2, #-4         ; decrement digit counter
        BRp BITSTRING           ; loop for remaining digits

	LD R0, NEWLINE          ; Load NEWLINE
	OUT                     ; Print NEWLINE
	LD R1, LOOPS            ; Load LOOPS into R1
	ADD R1, R1,#-1          ; Decrement R1
	ST R1, LOOPS            ; Store R1 back into loops
	BRp PRINT               ; Branch to PRINT_HIST if R1 is positive
	

       

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments



DONE	HALT			; done


; the data needed by the program

NINEOFFSET      .FILL x0030     ; offset for numbers 0 to 9
AOFFSET         .FILL x0037     ; offset for numbers 10 to 15
SYMBOL          .FILL x0040     ; HEX Code for ASCII @ symbol
SPACE		.FILL x0020     ; Space
NEWLINE         .FILL x000A     ; New Line
LOOPS           .FILL x001B     ; 27 loops
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
