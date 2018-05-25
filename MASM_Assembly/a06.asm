TITLE Assignment6     (a06.asm)

; Author: Gunnar Martin
; Email: martigun@onid.orst.edu
; Class: CS271-400
; Assignment #6A
; Due Date: 3/15/15
;
; Description: This program will...
; 1. Implement the macro getString, which displays a prompt, then gets the users keyboard
;    input into a memory location
; 2. Implement the macro displayString, which prints a string stored to a memory location
;    and gives the user the length of that string
; 3. Implement the procedure readVal, which invokes getString for a users string of digits.
;    it then validates that the user gave an unsigned integer value that will fit within
;    a 32 bit register.
; 4. Implement the procedure writeVal, which converts a numeric value to a string of digits
;    then invokes displayString in order to print these digits
; 5. These 4 implementations will be demostrated within a program that gets (and validates)
;    10 unsigned integers from the user (using readVal) and converts the strings of characters to values.
;	 These values will be loaded to an array that will then be printed using writeVal. Finally,
;    the sum and average of the 10 integers will be displayed. 

INCLUDE Irvine32.inc

;-------------------------------------------------------------------------------------------
; displayString (MACRO)
; 
; Desc: Prints string when given the OFFSET of the array
; Parameter(s): P1 - address in memory of string to be printed
; Registers changed/restored: EDX
;-------------------------------------------------------------------------------------------

displayString MACRO src_address
	pushad							;push registers to stack

	mov		edx, src_address		;move str address into edx
	call	WriteString				;write buffer

	popad							;restore registers
ENDM

;-------------------------------------------------------------------------------------------
; getString (MACRO)
; 
; Desc: Gets a string from the user, puts it in memory at specified address
; Parameter(s): P1 - string address to save string, P2 - length of string
; Registers changed/restored: EDX, EAX
;-------------------------------------------------------------------------------------------

getString MACRO dest_address, str_len
	pushad							;push registers to stack
		
	mov		edx, dest_address		;set edx to the dest_address
	mov		ecx, MAXSIZE			;set ecx to MAXSIZE
	call	ReadString

	mov		str_len, eax			;move EAX into str_len

	popad							;restore registers
ENDM

.data

MAXSIZE	EQU     100					;max size of a string
WARN	EQU		429496729			;32-bit registers max out at 4294967295 - this excl the last digit

myname	BYTE	"Author: Gunnar Martin",0
mytitle	BYTE	"Title: Assignment6",0
txt1	BYTE	"Please provide 10 unsigned decimal integers.",0
txt2	BYTE	"Each number needs to be small enough to fit inside a 32 bit register.",0
txt3	BYTE	"After you have finished with input, I will display a list",0
txt4	BYTE	"of the integers, their sum, and their average value.",0
txt5	BYTE	"Please enter an unsigned number:",0
txt6	BYTE	"Invalid entry. You did not enter an unsigned number",0
txt7	BYTE	"or your number was too big. Please try again.",0
txt8	BYTE	", ",0
txt9	BYTE	"You entered the following numbers:",0
txt10	BYTE	"The sum of these numbers is: ",0
txt11	BYTE	"The average is: ",0
donetxt	BYTE	"Program is done running. Have a nice day.",0

ustr	BYTE	MAXSIZE DUP(?)
ostr	BYTE	MAXSIZE DUP(?)
rstr	BYTE	MAXSIZE DUP(?)
endstr	BYTE	MAXSIZE DUP(?)

vsum	DWORD	0
vavg	DWORD	?
curval	DWORD	?
mcount	DWORD	0
vlist	DWORD	10 DUP(?)

.code
main PROC

	push	OFFSET txt4				;param6 - text by ref
	push	OFFSET txt3				;param5 - text by ref
	push	OFFSET txt2				;param4 - text by ref
	push	OFFSET txt1				;param3 - text by ref
	push	OFFSET mytitle			;param2 - title by ref
	push	OFFSET myname			;param1 - my name by ref
	call	introduction			;introduce user to program

	mov		mcount, 0				;reset mcount to zero
	mov		ecx, 10					;set ecx to 10 for 10 loops

TopOfLoad:
	push	OFFSET curval			;param5 - number value by ref
	push	OFFSET txt7				;param4 - text by ref
	push	OFFSET txt6				;param3 - text by ref
	push	OFFSET txt5				;param2 - text by ref
	push	OFFSET ustr				;param1 - empty space for string memory by ref
	call	readVal					;read in string from user and validate

	mov		eax, curval				;move curval into eax
	add		vsum, eax				;add curval to vsum
	mov		ebx, mcount				;move mcount in ebx
	mov		vlist[ebx], eax			;move curval into vlist	
	
	add		mcount, 4				;increment counter
	loop	TopOfLoad				;jump to top of load loop

	call	CrLf
	displayString OFFSET txt9		;"You entered the following numbers:"
	call	CrLf

	mov		mcount, 0				;reset mcount to zero
	mov		ecx, 10					;reset ecx to 10

TopOfPrint:
	mov		ebx, mcount				;move mcount to ebx
	mov		eax, vlist[ebx]			;move vlist to eax
	mov		curval, eax				;move eax to curval
	
	cmp		ebx, 0					;compare counter to 0
	je		JumpIfZero				;do not add a comma if this is the first item
	displayString OFFSET txt8		;", "

JumpIfZero:
	push	OFFSET rstr				;param3	- empty space for string memory by ref
	push	OFFSET ostr				;param2 - empty space for string memory by ref
	push	curval					;param1 - this is the actual value
	call	writeVal				;write the value as a string

	add		mcount, 4				;increment counter
	loop	TopOfPrint				;jump to top of print loop

	mov		eax, vsum				;move sum into EAX
	call	CrLf
	displayString OFFSET txt10		;"The sum of these numbers is: "
	call	WriteDec
	call	CrLf

	mov		edx, 0					;clear out edx for division
	mov		ebx, 10					;move 10 to ebx for division
	mov		eax, vsum				;move sum to eax for division
	div		ebx						;divide vsum by 10

	displayString OFFSET txt11		;"The average is: "
	call	WriteDec

EndOfMain:
	push	OFFSET donetxt			;param1 - farewell text by ref
	call	farewell				;tell user program is done

	exit							;exit to operating system
main ENDP

;-------------------------------------------------------------------------------------------
; introduction
; 
; Desc: Prints the Authors name and title of program. Gives instructions.
; Recieves on stack (from top): P1 thru P6 - 6 offsets to text instructions
; Returns: Nothing
; Preconditions: Parameters must be on stack in order
; Registers changed/restored: EDX
; Parameter bytes returned to stack: 6 params (24 bytes)
;-------------------------------------------------------------------------------------------

introduction PROC
	enter	0, 0					;set up stack frame
	pushad							;push all registers
	
	displayString [ebp+8]			;param 1 print
	call	Crlf					;"Author: Gunnar Martin"
	displayString [ebp+12]			;param 2 print
	call	Crlf					;"Title: Assignment6"
	call	Crlf

	displayString [ebp+16]			;param 3 print
	call	Crlf					;"Please provide 10 unsigned decimal integers."
	displayString [ebp+20]			;param 4 print
	call	Crlf					;"Each number needs to be small enough to fit inside a 32 bit register."
	displayString [ebp+24]			;param 5 print
	call	Crlf					;"After you have finished with input, I will display a list"
	displayString [ebp+28]			;param 6 print
	call	Crlf					;"of the integers, their sum, and their average value."
	call	Crlf
	
ExitFunction:
	popad							;restore registers
	leave							;restore stack frame
	ret 24							;return bytes for parameter(s)
introduction ENDP

;-------------------------------------------------------------------------------------------
; readVal
; 
; Desc: Get string from user, validates that it is not too big and that it is all digits,
;       and convert to the input to a numeric value
; Recieves on stack (from top): P1(ref) user string memory, P2-4(ref) text instructions,
;                              P5(ref) memory for numeric value
; Returns: Nothing
; Preconditions: Parameters must be on stack in order
; Registers changed/restored: EAX, ESI, ECX, EBX
; Parameter bytes returned to stack: 5 params (20 bytes)
;-------------------------------------------------------------------------------------------

readVal PROC
	LOCAL	len:DWORD,				;for length of the string
			final:DWORD,			;ptr to user string
			curr:DWORD				;current value being parsed

	pushad							;push all registers to stack

	mov		esi, [ebp+8]			;param 1 - @user string to esi
	jmp		FirstRun				;jump to FirstRun on first run

EntryInvalid:
	displayString [ebp+16]			;p3 - "Invalid entry. You did not enter an unsigned number"
	Call	CrLf
	displayString [ebp+20]			;p4 - "or your number was too big. Please try again."
	Call	CrLf

FirstRun:
	displayString [ebp+12]			;p2 - "Please enter an unsigned number:"
	getString esi, len				;get user entry into @esi, length goes to len

	mov		ecx, len				;set ecx to the string length
	cld								;move through string from front to back
	mov		final, 0				;set final number to zero

TopOfLoop:
	lodsb							;read byte into AL (increment esi)
	movzx	eax, al					;move byte into EAX, size extended
	cmp		eax, 48					;compare to zero
	jl		EntryInvalid			;jump to invalid if less than zero
	cmp		eax, 57					;compare to nine
	jg		EntryInvalid			;jump to invalid if greater than nine

	sub		eax, 48					;convert the digit from char to int
	mov		curr, eax				;set current digit to EAX

	mov		eax, final				;set EAX to current final value (excl current digit)
	cmp		eax, WARN				;compare final right now to the warning before we multiply
	jg		EntryInvalid			;if final right now is greater than the warning, it is too big

	cmp		eax, WARN				;compare final right now to the warning (again)
	je		InDanger				;Jump to in danger we are on the edge of overflowing
	jmp		NoDanger				;under normal circumstances, jump to no danger

InDanger:
	mov		eax, curr				;move current digit to EAX
	cmp		eax, 5					;compare current digit to 5 (last digit of 4294967295)
	jg		EntryInvalid			;jump to invalid if the final digit is above 5

NoDanger:
	mov		eax, final				;move final into EAX	
	mov		ebx, 10					;move 10 to EBX for multiplication
	mul		ebx						;multiply final by 10
	mov		final, eax				;move new final from EAX to final
	
	mov		eax, curr				;move current digit to EAX
	add		final, eax				;add EAX to existing number

	loop	TopOfLoop				;decrement ECX, jump to top

	mov		ebx, [ebp+24]			;set ebx to @param5 - the value
	mov		eax, final				;move final into EAX
	mov		[ebx], eax				;move EAX into @param5

ExitFunction:
	popad							;pop all registers from stack
	ret 20							;return bytes for parameter(s)
readVal ENDP

;-------------------------------------------------------------------------------------------
; writeVal
; 
; Desc: Takes numeric value, converst to string and prints it
; Recieves on stack (from top): P1(val) numeric value, P2-3(ref) memory for string,
; Returns: Nothing
; Preconditions:  Parameters must be on stack in order
; Registers changed/restored: EAX, EBX, EDI, EDX, ESI
; Parameter bytes returned to stack: 3 parameters (12 bytes)
;-------------------------------------------------------------------------------------------

writeVal PROC
	LOCAL	temp:DWORD,				;for original integer value
			initial:DWORD,			;ptr to inital string space
			final:DWORD,			;ptr to final string space
			counter:DWORD			;int counter for string length

	pushad							;push all registers to stack
	
	mov		ebx, [ebp+16]			;param 3 - @final output
	mov		final, ebx				;set final to @final

	mov		edi, [ebp+12]			;param 2 - @user output string to edi
	mov		initial, edi			;param 2 - to local variable string		

	mov		eax, [ebp+8]			;param 1 - the integer value
	mov		temp, eax				;move into temp

	mov		counter, 0				;set counter to zero

	cld								;move through loop forwards

TopOfLoop:
	mov		eax, temp				;move temp into eax for division
	mov		edx, 0					;clear EDX for division remainder
	mov		ebx, 10					;move 10 in EBX for division
	div		ebx						;divide the value by 10 (EDX=rem)
	
	mov		temp, eax				;move answer to temp for later

	mov		eax, edx				;move remainder into EAX
	add		eax, 48					;convert EAX to char
	stosb							;store the AL portion to current EDI (and increment EDI)
	inc		counter					;increment counter

	mov		eax, temp				;move answer to EAX
	cmp		eax, 10					;compare EAX to 10
	jge		TopOfLoop				;run again if answer is >= 10

EndOfLoop:
	cmp		eax, 0					;compare EAX to zero
	je		JumpZero				;if zero, dont add to the string

	add		eax, 48					;convert EAX to char
	stosb							;store AL portion to EDI, adding this char to the string
	inc		counter					;increment counter

JumpZero:
	mov		AL, 0					;set AL to zero
	stosb							;0 terminate the string

	mov		ecx, counter			;move number of digits to ecx
	mov		edi, final				;move edi to the address @final first byte
	mov		esi, initial			;move esi to the address @initial
	add		esi, ecx				;move esi to then end of the initial string
	dec		esi						;drop back one character to get to last byte

TopOfReverse:
	std								;get characters from end to beginning
	lodsb							;load ESI to AL
	cld								;store characters from beginning to end
	stosb							;store AL to EDI

	loop	TopOfReverse			;loop to top

	cld								;move through loop forwards
	mov		AL, 0					;set AL to zero
	stosb							;0 terminate the string

	displayString final				;print final string

ExitFunction:
	popad							;pop all registers from stack
	ret 12							;return bytes for parameter(s)
writeVal ENDP

;-------------------------------------------------------------------------------------------
; farewell
; 
; Desc: Prints farewell message
; Recieves on stack (from top): Nothing
; Returns: Nothing
; Preconditions:  Parameters must be on stack in order
; Registers changed: EDX
; Parameter bytes returned to stack: 1 parameter (4 bytes)
;-------------------------------------------------------------------------------------------

farewell PROC
	enter	0, 0				;set up stack frame
	pushad						;push all registers

	call	Crlf
	call	Crlf
	displayString [ebp+8]		;"Program is done running. Have a nice day, "
	call	Crlf

	popad						;pop all registers
	leave						;restore stack frame
	ret		4					;return bytes
farewell ENDP


;-------------------------------------------------------------------------------------------
; END OF CODE
;-------------------------------------------------------------------------------------------
END main