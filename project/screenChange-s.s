	.arch msp430g2553
	.p2align 1,0
	.text

	.global screenChange
	.extern COLOR_DARK_GREEN, COLOR_LIME_GREEN, COLOR_BLUE, COLOR_AQUAMARINE, COLOR_PURPLE, COLOR_HOT_PINK, colorRotation

jt:	.word case1
	.word case2
	.word case3


screenChange:
	cmp #3, &colorRotation 	; 3-colorRotation
	jnc default

	mov &colorRotation, r12
	add r12, r12
	mov jt(r12), r0

case1:
	add #1, &colorRotation
	mov &COLOR_DARK_GREEN, &background
	mov &COLOR_LIME_GREEN, &letters
	jmp end

case2:
	add #1, &colorRotation
	mov &COLOR_BLUE, &background
	mov &COLOR_AQUAMARINE, &letters
	jmp end

case3:
	mov #0, &colorRotation
	mov &COLOR_PURPLE, &background
	mov &COLOR_HOT_PINK, &letters
	jmp end


default:
	mov #0, &colorRotation
	
end:
	pop r0
