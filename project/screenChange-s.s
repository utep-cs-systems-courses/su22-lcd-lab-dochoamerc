	.arch msp430g2553
	.p2align 1,0
	.text

	.global screenChange
	.extern colorRotation, background, letters

jt:
	.word default
	.word case1
	.word case2
	.word case3
	.word case4

screenChange:
	cmp &colorRotation, #4 	;4-colorRotation
	jnc default

	mov &colorRotation, r12
	add r12, r12
	mov jt(r12), r0

case1: 
	add #1, &colorRotation
	mov 0x001f, &background ;red
	mov 0x90bf, &letters ;deep
	jmp end

case2:
	add #1, &colorRotation
	mov 0x0320, &background ;dark green
	mov 0x3666, &letters ;lime green
	jmp end

case3:
	add #1, &colorRotation
	mov 0xf800, &background ;blue
	mov 0xd7ef, &letters ;aquamarine
	jmp end

case4:
	mov #1, &colorRotation
	mov 0xf114, &background ; purple
	mov 0xb35f, &letters 	; hot pink
	jmp end


default:
	mov #1, &colorRotation
	
end:
	pop r0
