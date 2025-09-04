.MODEL SMALL
.STACK 1000H
.DATA
FIXED_POINT_MULTIPLIER DW 64H
.CODE
main PROC
;>>
	PUSH BP
	MOV BP , SP
	;Line 5: DATA SEGMENT INITIALIZATION
	MOV AX, @DATA
	MOV DS, AX
	SUB SP , 2
	SUB SP , 2
	SUB SP , 4
	;Line 4: integar = 0
	MOV CX , 0
	;Line 4: get array element from stack
	PUSH BP
	SAL CX , 1
	ADD CX , -8
	ADD BP , CX
	MOV CX , PTR WORD [BP]
	POP BP
	ADD SP , 8
	main_exit:
	POP BP
	;Line 5: EXIT 0
	MOV AH, 4CH
	INT 21H
	RET 0
	;<<
main ENDP
END main
