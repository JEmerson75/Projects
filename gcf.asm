;GCF Program that will accept any combination of numbers in a text file

INCLUDE Irvine32.inc

.data
inFileName byte "gcf3.txt", 0
outFileName byte "results.txt", 0
IFD dword ?
OFD dword ?
num1 dword ?
num2 dword ?
lineIn byte 32 dup(? )
myString byte "Largest common factor: ", 0; 46, 120 is the first result, 5677,12523 is second
myAry byte 32 dup(? )
endl byte 0dh, 0ah, 0
answer dword ?

.code
main proc
lea edx, outFileName
call CreateOutputFile
mov OFD, eax; open output file

lea edx, inFileName
call OpenInputFile
mov IFD, eax; open input file

lea edx, lineIn
mov ecx, 32; bytes to read in
mov eax, IFD
call ReadFromFile; read infile

lea edi, lineIn; esi points to first byte

mainLoop :
call getNumbers

push num1
push num2

call lcf

pop eax
pop ebx; ebx has answer
mov answer, ebx

lea esi, myString
call fileOut; print "Largest common factor: "

lea esi, myAry
mov ch, 32
call blankout; clear out esi

mov eax, answer
call itoa
call fileOut; print result to file

lea esi, endl
call fileOut; print new line to file

mov bl, '.'
cmp[edi], bl; check for end of file
jne mainLoop

exit
main endp

lcf proc
push ebp
mov ebp, esp

mov ebx, 12[ebp]; N
mov ecx, 8[ebp]; M
cmp ecx, 0
jne recursion; base case

jmp returnLcf

recursion :
mov edx, 0; prepare edx for division
mov eax, ebx
idiv ecx; get mod

push ecx
push edx
call lcf
pop ebx
pop ecx

mov 12[ebp], ecx

returnLcf :
pop ebp

ret
lcf endp

getNumbers proc
call atoi
mov num1, eax
inc edi

call atoi
mov num2, eax
inc edi

ret
getNumbers endp

itoa proc
itoaLoop :
mov edx, 0
mov ecx, 10

idiv ecx
add dl, '0'
dec esi
mov[esi], dl
cmp eax, 0
jne itoaLoop

ret
itoa endp

fileOut proc
mov bl, NULL

nextChar :
mov eax, OFD
mov edx, esi
mov ecx, 1
call WriteToFile
add esi, 1

cmp[esi], bl; check if null
jne nextChar

ret
fileOut endp

blankout proc
blnkLoop :
mov cl, ' '
mov[esi], cl
inc esi
dec ch
cmp ch, 0
jne blnkLoop

ret
blankout endp

atoi proc
mov eax, 0

nextDigit:
mov edx, 0
mov dl, [edi]

cmp dl, '0'
jl  outOfHere
cmp dl, '9'
jg outOfHere; check if char is digit

add dl, -'0'

imul eax, 10

add eax, edx
inc edi

jmp nextDigit

outOfHere :

ret
atoi endp

end main