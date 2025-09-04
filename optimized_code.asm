.MODEL SMALL
.STACK 1000H
.DATA
FIXED_POINT_MULTIPLIER DW 64H
.CODE
main PROC
;>>
	PUSH BP
	MOV BP , SP
	;Line 8: DATA SEGMENT INITIALIZATION
	MOV AX, @DATA
	MOV DS, AX
	SUB SP , 2
	SUB SP , 2
	SUB SP , 2
	SUB SP , 2
	;Line 7: start of for loop
	for_loop1:
	;>>
		;Line 4: Relational operator checking
		MOV CX , -2[BP]
		PUSH CX
		;Line 4: integar = 0
		MOV CX , 0
		POP AX
		CMP AX , CX
		JG relop_is_ok0
		MOV CX , 0
		JMP relop_end0
		relop_is_ok0:
		MOV CX , 1
		relop_end0:
		JCXZ for_end1
		;>>
			;Line 7: start of for loop statement
			;Line 6: integar = 3
			MOV CX , 3
			MOV -4[BP] , CX
			;Line 6: CX = assigned value
			;<<
		;Line 7: start of for loop step
		JMP for_loop1
		;<<
	for_end1:
	ADD SP , 8
	POP BP
	;Line 8: EXIT 0
	MOV AH, 4CH
	INT 21H
	RET 0
	;<<
main ENDP
END main
