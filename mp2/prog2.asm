; Intro Paragraph

; This program implements a stack calculator that evaluates a postfix expression.
; If the character entered is an operand (0-9) it is pushed to the stack. 
; If the character entered is an operator (+,-,*,/,^), 2 operands are popped from the stack, 
; the operator is applied, and the result is pushed back.
; If the character entered is an '=', the final result is popped from the stack, stored to R5, and printed
; in hex
; If the input is invalid, an error message is displayed. 


; partner: pranay2


; Register Table
; R0:
; R1:
; R2:
; R3:
; R4:
; R5:
; R6:
; R7:

.ORIG x3000	
	
GET_INPUT
    GETC    ;
    OUT     ;
    JSR EVALUATE    ;
    BRnzp GET_INPUT ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
    
    AND R0, R0, #0          ; clear R0 (digit)
    AND R1, R1, #0          ; clear R1 (bit counter)
    AND R2, R2, #0          ; clear R2 (digit counter)
    AND R4, R4, #0          ; clear R4 (offset)
    
    ADD R2, R2, #8          ; Add 8 to R2
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

    LD R5, PRINTVAL         ;

    HALT

NINEOFFSET    .FILL x0030            ; offset for numbers from 0 to 9
AOFFSET       .FILL x0037            ; offset for numbers from 10 to 15
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
EVALUATE
    ST R7, SAVER7   ;
    AND R1, R1, #0  ;
    AND R3, R3, #0  ;
    AND R4, R4, #0  ;

EQUALS
    LD R6, EQUAL    ;
    ADD R1, R0, R6  ;
    BRnp SPACE      ;
    JSR POP         ;

    AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3	    	;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRnp INVALID		;
    
    ADD R3,R3,R0    ;
    ST R3, PRINTVAL ;
    BRnzp PRINT_HEX ;
    
SPACE
    LD R6, SPAC     ;
    ADD R1, R0, R6  ;
    BRnp NUMBER     ;
    LD R7,SAVER7    ;
    RET             ;

NUMBER
    LD R6, NINE     ;
    ADD R1,R0,R6    ;
    BRp PLUS        ;
    LD R6, ZERO     ;
    ADD R1,R0,R6    ;
    BRn PLUS        ;
    ADD R0,R0,R6    ;
    JSR PUSH        ;
    LD R7, SAVER7   ;
    RET             ;

PRINTVAL .BLKW #1   ;
SAVER7 .BLKW #1     ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
    LD R6, ADDI     ;
    ADD R1,R0,R6    ;
    BRnp MIN        ;
    JSR POP         ;
    ADD R5,R5,#0    ; 
    BRp INVALID     ;
    ADD R3,R3,R0    ;
    JSR POP         ;
    ADD R5,R5,#0    ; 
    BRp INVALID     ;
    ADD R4,R4,R0    ;

    ADD R0,R3,R4    ;

    JSR PUSH        ;
    LD R7, SAVER7   ;
    RET             ;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
    LD R6, SUB      ;
    ADD R1,R0,R6    ;
    BRnp MUL        ;
    JSR POP         ;
    ADD R5,R5,#0    ;
    BRp INVALID     ;
    ADD R4,R4,R0    ;
    JSR POP         ;
    ADD R5,R5,#0    ;
    BRp INVALID     ;
    ADD R3,R3,R0    ;

    NOT R4,R4       ;
    ADD R4,R4,#1    ;
    ADD R0,R3,R4    ;

    JSR PUSH        ;
    LD R7, SAVER7   ;
    RET             ;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
    LD R6, MULTI    ;
    ADD R1,R0,R6    ;
    BRnp DIV        ;
    JSR POP         ;
    ADD R3,R3,R0    ;
    ADD R5,R5,#0    ;
    BRp INVALID     ;
    JSR POP         ;
    ADD R5,R5,#0    ;
    BRp INVALID     ;
    ADD R4,R4,R0    ;
                                                            
    MULT_LOOP    ADD R0, R3, R0        ; add R3 to R0, store in R0
    ADD R4, R4, #-1        ; decrement R4, used as mult counter
    BRp MULT_LOOP        ; go to MULT_LOOP while R4 is non negative
    
    JSR PUSH                                                                                     
    LD R7, SAVER7    ;
    RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV
    LD R6, DIVIDE   ;
    ADD R1,R0,R6    ;
    BRnp EXP        ;
    JSR POP         ;
    ADD R5,R5,#0    ;
    BRp INVALID     ;
    ADD R4,R4,R0    ;
    BRz INVALID     ;
    JSR POP         ;
    ADD R5,R5,#0    ;
    BRp INVALID     ;
    ADD R3,R3,R0    ;
    
    AND R0, R0, #0  ;
    NOT R4, R4      ; not R4 for 2's complement
    ADD R4, R4, #1  ; R4 = -R4

DIV_LOOP
    ADD R3, R3, R4        ; subtract R4 from R3
    BRn EXIT_DIV          ;
    ADD R0, R0, #1        ; add one to quotient count
    ADD R3, R3, #0        ;
    BRz EXIT_DIV          ;
    BRnzp DIV_LOOP        ; unconditionally return to DIV_LOOP

EXIT_DIV
    JSR PUSH              ;
    LD R7, SAVER7         ;
    RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
    LD R6, EXPO     ;
    ADD R1,R0,R6    ;
    BRnp INVALID    ;
    JSR POP         ;
    ADD R5,R5,#0    ;
    BRp INVALID     ;
    ADD R4,R4,R0    ;
    JSR POP         ;
    ADD R5,R5,#0    ;
    BRp INVALID     ;
    ADD R3,R3,R0    ;

    AND R0, R0, #0        ; clear R0
    AND R5, R5, #0        ; clear R5
    ADD R0, R3, #0        ; R0 = R3
    ADD R4, R4, #-1       ; decrement to make it work
    BRn ZEROCASE          ; branch to ZEROCASE if power is 0
    BRz EXPDONE           ; branch to EXPDONE if power is 0
                                                                        
EXP_LOOP
    AND R5, R5, #0        ; clear R5
    ADD R5, R0, #0        ; R5 = R0
    AND R0, R0, #0        ; clear R0
                                                                                                                                        
EXPMULT_LOOP
    ADD R0, R3, R0        ; add R3 to R0, store the result in R0
    ADD R5, R5, #-1       ; decrement multiplication counter
    BRp EXPMULT_LOOP      ; go to EXPMULT_LOOP while R5 is positive
    ADD R4, R4, #-1       ; decrement exponent counter
    BRp EXP_LOOP          ; go to EXP_LOOP if R4 is positive
    BRnzp EXPDONE         ; branch to EXPDONE unconditionally
 
ZEROCASE    
    AND R0, R0, #0        ; clear R0
    ADD R0, R0, #1        ; R0 = 1

EXPDONE
    JSR PUSH              ;
    LD R7, SAVER7         ;
    RET

INVALID
    LEA R0, INVAL         ;
    PUTS                  ;
    HALT                  ;

INVAL  .STRINGZ "Invalid Expression"
SPAC   .FILL #-32
EQUAL  .FILL #-61
ADDI   .FILL #-43
SUB    .FILL #-45
MULTI  .FILL #-42
DIVIDE .FILL #-47
EXPO   .FILL #-94
ZERO   .FILL #-48
NINE   .FILL #-57
	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
