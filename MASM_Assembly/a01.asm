TITLE Assignment1     (a01.asm)

;
; Author: Gunnar Martin
; Email: martigun@onid.orst.edu
; Class: CS271-400
; Assignment #1
; Due Date: 1/18/15
; Note: I elected to use a grace day to turn this assignment in on 1/19/15
;
; Description: This program will ask the user for 2 numbers.
; The use will input 2 numbers.
; The program will outpu the sum, difference, product, 
; quotient and remainder of these 2 numbers.
;

INCLUDE Irvine32.inc

.data
a	DWORD	?		;first number
b	DWORD	?		;second number
sum	DWORD	?		;sum varaible
dif	DWORD	?		;diff variable
prd	DWORD	?		;product variable
quo	DWORD	?		;quotient
rem	DWORD	?		;remainder from division

myname	BYTE	"Author: Gunnar Martin",0
mytitle	BYTE	"Title: Assignment1",0
rules1	BYTE	"Please enter two positive integers and I'll show you the sum,",0
rules2	BYTE	"difference, product, quotient, and remainder.",0
prompt1	BYTE	"First (bigger) Integer: ",0
prompt2	BYTE	"Second (smaller) Integer: ",0
add_t	BYTE	" + ",0
sub_t	BYTE	" - ",0
mul_t	BYTE	" * ",0
div_t	BYTE	" / ",0
eq_t	BYTE	" = ",0
rem_t	BYTE	" remainder ",0
donetxt	BYTE	"Program is done running. Have a nice day!",0

.code
main PROC
;Display author name
	mov		edx,OFFSET myname		;set up for call to WriteString
	call	WriteString				;Write the Authors name
	call	Crlf
;Display title
	mov		edx,OFFSET mytitle
	call	WriteString				;Write the title
	call	Crlf
	call	Crlf

;Display rules1
	mov		edx,OFFSET rules1		;write the rules part 1	
	call	WriteString
	call	Crlf

;Display rules2
	mov		edx,OFFSET rules2		;write the rules part 2
	call	WriteString
	call	Crlf
	call	Crlf

;get an integer for a
	mov		edx,OFFSET prompt1
	call	WriteString
	call	ReadInt			;read in a from user, the larger integer
	mov	a,eax

;get an integer for b
	mov		edx,OFFSET prompt2
	call	WriteString
	call	ReadInt			;read in b from user, the smaller integer
	mov	b,eax
	call	Crlf

;calculate sum of a and b
	mov		eax,a
	mov		ebx,b
	add		eax,ebx			;add a and b
	mov		sum,eax			;store sum in variable

;calculate diff of a and b
	mov		eax,a
	mov		ebx,b
	sub		eax,ebx			;subtract b from a
	mov		dif,eax			;store subtract in variable
	
;calculate product of a and b
	mov		eax,a
	mov		ebx,b
	mul		ebx				;multiply a by b
	mov		prd,eax			;store product in variable

;calculate quotient
	mov		eax,a
	mov		ebx,b
	mov		edx,0
	div		ebx				;divide a by b
	mov		quo,eax			;store quotient in variable
	mov		rem,edx			;store remainder in variable

;display sum
	mov		eax,a				;display number a
	call	WriteDec

	mov		edx,OFFSET add_t	;display +
	call	WriteString		

	mov		eax,b				;display number b
	call	WriteDec

	mov		edx,OFFSET eq_t		;display =
	call	WriteString

	mov		eax,sum				;disply the sum
	call	WriteDec
	call	Crlf

;display diff
	mov		eax,a				;display number a
	call	WriteDec

	mov		edx,OFFSET sub_t	;display -
	call	WriteString		

	mov		eax,b				;display number b
	call	WriteDec

	mov		edx,OFFSET eq_t		;display =
	call	WriteString

	mov		eax,dif
	call	WriteDec			;display the difference
	call	Crlf

;display product
	mov		eax,a				;display number a
	call	WriteDec

	mov		edx,OFFSET mul_t	;display *
	call	WriteString		

	mov		eax,b				;display number b
	call	WriteDec

	mov		edx,OFFSET eq_t		;display =
	call	WriteString

	mov		eax,prd
	call	WriteDec			;display the product
	call	Crlf

;display quotient
	mov		eax,a				;display number a
	call	WriteDec

	mov		edx,OFFSET div_t	;display /
	call	WriteString		

	mov		eax,b				;display number b
	call	WriteDec

	mov		edx,OFFSET eq_t		;display =
	call	WriteString

	mov		eax,quo
	call	WriteDec			;display the quotient
	
	mov		edx,OFFSET rem_t
	call	WriteString			;display remainder text

	mov		eax,rem
	call	WriteDec			;display the remainder
	call	Crlf
	call	Crlf
	
;Display finished text-------------------------
	mov		edx,OFFSET donetxt	
	call	WriteString			;display the done text
	call	Crlf
	exit				;exit to operating system
main ENDP

END main