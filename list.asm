;/ Inventory and kiosk program in MASM32 Assembly

include Irvine32.inc

.data
null		equ		00h
cr			equ		0dh
lf			equ		0ah
buffer		byte	'a', 2000 dup(? )
itemPrice	dword	225, 399, 1375, 259, 350, 95, 215
dword	160, 740, 329, 220, 895, 126, 375
itemST		dword	14 dup(0)
ten			dword	10
menuMsg		byte	"  Welcome to the 'Happy Supply' Shop.", cr, lf
byte	"  Please make your selection.", cr, lf
byte	"                                  Sub Total", cr, lf
byte	"   Construction Paper  $2.25               ", cr, lf
byte	"   Bic Pens            $3.99               ", cr, lf
byte	"   Planner Notebook    $13.75              ", cr, lf
byte	"   10 Pk Pencils       $2.59               ", cr, lf
byte	"   Mini Stapler        $3.50               ", cr, lf
byte	"   Research Binder     $.95                ", cr, lf
byte	"   Staples             $2.15               ", cr, lf
byte	"   Scotch Tape         $1.60               ", cr, lf
byte	"   Folders             $7.40               ", cr, lf
byte	"   Screen Wipes        $3.29               ", cr, lf
byte	"   Note Pads           $2.20               ", cr, lf
byte	"   High Lighters       $8.95               ", cr, lf
byte	"   Paper Clips         $1.26               ", cr, lf
byte	"   Staple Remover      $3.75               ", cr, lf

; byte	"   HELP									", cr, lf

byte	"   ALL DONE (PRESS ENTER TO LEAVE)         ", cr, lf
billMsg		byte    "                   Your Bill               ", cr, lf, null
iSubMsg		byte	7 dup(? ), null
blanked		byte	7 dup(20h), null
bTotMsg		byte	8 dup(? ), null
subStart	byte	36
billStCol	byte	35
billStRow	byte	18
lastMsg		byte	"Your order is being processed!", cr, lf
byte	"Have a great day, and tell Dr. Rimes to pass me", cr, lf, null
testBit		byte	'0'
boolBit		byte	'0'
boolBS		byte	'0'
response	dword ?
caption1	byte	"Keep Shopping?", null
caption2	byte	"Would you like to keep shopping?", null


.code
main proc
lea esi, menuMsg
call WriteLine
lea esi, buffer; keeps all keystrokes entered for checking purposes
inc esi; bumps past the 'a'
mov dh, 3; goes to the first item's row
mov dl, 1; goes to the middle col
call gotoXY; places the cursor there ^
loop1:
mov eax, 0; clear out eax so just the entered char is there
sub ah, ah
call readChar
mov[esi], al; moves it into key buffer
call checkKeyStroke; validates input and calculates totals
inc esi; bumps key buffer
mov boolBS, '0'
cmp al, cr; see if an enter has been pushed
jne loop1; if not, do it again
cmp dh, 17; if it is enter, then check what line its on
jne loop1; if not last line, do it again
push edx
mov ebx, offset caption1
mov edx, offset caption2
call msgBoxAsk
cmp eax, 6
je finito
pop edx
jmp loop1
finito :
pop edx
mov dh, 20; moves down to row past the items
mov dl, 0; moves to far left
call gotoXY; moves cursor there
lea esi, lastMsg; print "polite" messages
call writeLine; write it
call Waitmsg
invoke exitProcess, 0
main endp

checkKeyStroke proc
mov boolBit, '0'; clears bool val for checking if more than 2 nums ent
cmp al, '0'; checking to see if its a digit
jl notADigit; if not, cmp further
cmp al, '9'; ^^^^^^
jg notADigit; ^^^^^^
cmp dh, 17; dont want anything for all done line
je three; go to loop for three num
call digitPressed; if it is digit, go process
cmp boolBit, '1'; if '1',
je three; go to loop for three num
call updateQuantity; update item total
call updateBill; update bill total
call gotoXY; go back to col 1
three:
ret; if 3rd, do nothing
notADigit :
call nonDigitPressed; check to see if arrow key
ret
checkKeyStroke endp

updateQuantity proc
push esi; keep esi from getting stepped on
cmp boolBS, '1'; cmp for backspace
je not2Digi; if so process 1 digit num
mov ebx, 0; clear ebx out
mov bl, [esi - 1]; check the last keystroke before current
cmp bl, '0'; check for if it is a digit
jl not2Digi; if not, then quan is 1 num
cmp bl, '9'; ^^^^^^^^^
jg not2Digi; ^^^^^^^^^
mov testBit, '1'; update bool val for being 2 digit num
not2Digi :
mov bl, al; save al
mov eax, 0; clear eax out
mov al, bl; mov it back to al
mov ebx, 0; clear ebx out
mov bl, dh; mov current row to get to correct array ele
sub bl, 3; sub 3 since rowStart is 3
shl ebx, 2; 
lea edi, itemPrice; how much the items are
add edi, ebx; add how many bytes away to correct array ele
lea esi, itemST; how much each item costs per quan given
add esi, ebx; add how many bytes away
sub al, 30h; get int of val
imul eax, [edi]; mult item price by quan
cmp testBit, '0'; checking for 2 digit num
jne twoDigi; if 2 digit num, jmp to 2 digit manip
mov[esi], eax; mov subtotal for item in array
jmp print; go to print
twoDigi :
mov ebx, [esi]; mov the 1st subtotal of item to ebx
imul ebx, ten; mult by 10
mov[esi], ebx; mov it back in array
add[esi], eax; add 2nd subtotal to array
mov eax, [esi]; mov subtotal for item into eax for printing
print :
cmp boolBS, '1'; cmp for backspace
je specialCase; special print
cmp eax, 0
je specialCase
lea esi, iSubMsg; subtotal msg
mov ecx, 7; linkage
call blankOut
call modItoA; put it in iSubMsg
mov dl, subStart; mov col to subStart
call gotoXY; move cursor there
lea esi, iSubMsg; linkage for printing
call writeLine; write it
mov dl, 1; mov back to input compl
call gotoXY; move cursor there
mov testBit, '0'; reset bool val
pop esi; restore esi
ret
specialCase :
lea esi, blanked; load blanked array
mov dl, subStart; start at subtotal col
call gotoXY; move cursor there
call writeLine
mov dl, 1; move input col into dl
call gotoXY; move cursor there
pop esi; restore esi
ret
updateQuantity endp

updateBill proc
pushad; pushes all regs
lea esi, itemST; mov start of ary of item subTotal
mov ecx, 14; for adding them up
mov eax, 0; to update the bill total
addEm :
add eax, [esi]; add each item to accum
add esi, 4; bump esi
loop addEm; go through all ary ele
lea esi, bTotMsg; bill total msg
mov ecx, 8; linkage for blankout
call blankOut
call modItoA; puts bill total in msg
mov dh, billStRow; linkage
mov dl, billStCol; linkage
call gotoXY; go to start of bill total msg
lea esi, bTotMsg; linkage
call writeLine; print it
popad; pops all registers
ret
updateBill endp

digitPressed proc
push ebx; keep ebx from getting stepped on
push edx; keep edx from getting stepped on
mov bl, [esi - 1]; mov last keystroke into bl
cmp bl, '0'; check if its a num
jl oneNumber; ^^^^^^^
cmp bl, '9'; ^^^^^^^
jg oneNumber; ^^^^^^^
mov bl, [esi - 2]; check if keystroke before last one is digit
cmp bl, '0'; ^^^^^^^
jl continues; ^^^^^^^
cmp bl, '9'; ^^^^^^^
jg continues; ^^^^^^^
pop edx; restore edx
pop ebx; restore ebx
mov boolBit, '1'; mov '1' in since its the 3rd digit
jmp youCantGetMe; your 3 or more digits dont fool me
continues :
call gotoXY; 2nd digit so print in current spot
call writeChar; write it
call gotoXY; go back to current spot
pop edx; restore edx
pop ebx; restore ebx
ret
oneNumber :
dec dl; mov to far left col
call gotoXY; mov cursor there
call writeChar; write it
pop edx; restore edx
call gotoXY; mov cursor to input col
mov bl, al; save al
mov al, 20h; mov blank in input col in case this isnt the first time
call writeChar; write it
mov al, bl; restore al
pop ebx; restore ebx
youCantGetMe :
ret
digitPressed endp

nonDigitPressed proc
mov boolBS, '0'
cmp ah, 48h; check if up arrow keystroke
jne notUp; if not check for down
dec dh; if so, then go up a row
call checkLowerBound; make sure you dont blow through top
call gotoXY; mov cursor to input col
ret
notUp :
cmp ah, 50h; check if down
jne notDown; if not, dont care what it is
inc dh; if so, go down a row
call checkUpperBound; make sure you dont blow through bottom
call gotoXY; mov cursor to input col
ret
notDown :
cmp al, 8h; cmp to backspace
jne notBack; if not, skip
cmp dh, 17; if all done line
je notBack; skip
push esi; keep esi from getting stepped on
mov dl, subStart; mov col to subStart
call gotoXY; move cursor there
lea esi, blanked; linkage for printing
call writeLine; write it
mov dl, 0; mov back to input compl
call gotoXY; move cursor there
mov al, 20h; mov blank in to erase anything there
call writeChar; write first blank
call writeChar; write second blank
mov dl, 1; go back to input col
call gotoXY; mov cursor back
mov al, '0'; mov for correct calc
mov boolBS, '1'; bool bit for backspace
call updateQuantity; update to 0
call updateBill; update after 0
call gotoXY; go back to input col
pop esi; restore esi
ret
notBack :
ret
nonDigitPressed endp

checkLowerBound proc
cmp dh, 3; check if blown
jge itsFine; if not, go back
mov dh, 3; if so, mov it to top
itsFine :
ret
checkLowerBound endp

checkUpperBound proc
cmp dh, 17; check if blown
jle itsOK; if not, go back
mov dh, 17; if so, mov it to bottom
itsOK :
ret
checkUpperBound endp

WriteLine proc
; esi = beginning of message
nextChar :
mov al, [esi]
cmp al, 00h
je allDone
call WriteChar
inc esi
jmp nextChar
allDone :
ret
WriteLine endp

modItoA proc
; esi = back of the mem location
; eax = number being converted
; ecx = number til decimal place
; modified from the original one
pushad
mov ecx, 2
beforeDec:
mov edx, 0
div ten
add dl, 30h
dec esi
mov[esi], dl
loop beforeDec
dec esi
mov dl, '.'
mov[esi], dl
modNextDigit :
mov edx, 0
div ten
add dl, 30h
dec esi
mov[esi], dl
cmp eax, 0
jne modNextDigit
dec esi
mov dl, '$'
mov[esi], dl
popad
ret
modItoA endp

BlankOut proc
; ecx - length
; esi - what is being blanked out
mov dl, 20h
blank :
mov[esi], dl
inc esi
dec ecx
cmp ecx, 0
jne blank
ret
BlankOut endp
end main