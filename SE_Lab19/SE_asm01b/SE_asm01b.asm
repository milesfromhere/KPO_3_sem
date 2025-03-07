﻿.586P
.MODEL FLAT, STDCALL

includelib kernel32.lib

ExitProcess			PROTO: DWORD
SetConsoleTitleA	PROTO: DWORD
GetStdHandle		PROTO: DWORD
WriteConsoleA		PROTO: DWORD, : DWORD, : DWORD, : DWORD, : DWORD
getmin				PROTO: DWORD, : DWORD
getmax				PROTO: DWORD, : DWORD

.STACK 4096

.CONST 
consoletitle	DB 'SE_asm01b', 0
Arr				DD 2, 67, -5, 91, 10, -24, 21, 7, 9, 10

.DATA
result1			BYTE "getmax + getmin = ", 0
result			sdword 0
result2			BYTE 40 dup(0)
consolehandle	DD 0h

.CODE
main PROC

	invoke SetConsoleTitleA, offset consoletitle

	push -11
	call GetStdHandle
	mov consolehandle, eax

	invoke getmin, offset Arr, lengthof Arr

	mov result, eax

	invoke getmax, offset Arr, lengthof Arr

	add result, eax
	xor eax, eax

	push result
	push offset result2
	call tochar

	invoke WriteConsoleA, consolehandle, offset result1, sizeof result1, 0, 0
	invoke WriteConsoleA, consolehandle, offset result2, sizeof result2, 0, 0

	push 0
	call ExitProcess

main ENDP

tochar PROC uses eax ebx ecx edi esi, pstr : dword, intfield : sdword
	mov edi, pstr
	mov esi, 0
	mov eax, intfield
	cdq
	mov ebx, 10
	idiv ebx
cycle:
	push dx
	inc esi
	test eax, eax
	jz fin
	cdq
	idiv ebx
	jmp cycle
fin:
	mov ecx, esi
write: 
	pop bx
	add bl, '0'
	mov[edi], bl
	inc edi
	loop write
	ret
tochar ENDP

END mainожно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
