.main:
	movu r0,59999 @ main variable
	add r3,r0,0  @ copy of r0
	movu r4,0   @ sum of factorials of digits
	movu r5,0  @ sum of digits  
.start:
	cmp r0,0  
	beq .return  @ if r0 is 0 print r1 and r2
	mod r6,r0,10 @ find the next significiant digit
	add r5,r5,r6 @ sum of digits
	movu r7,1  @factorial of digit
	cmp r6,0   
	beq .break @ if digit is 0 r7 = 1 and jump to next digit
	.loop:
		cmp r6,0 @ if digit reaches 0 stop calculating factorial
		beq .break
		mul r7,r7,r6
		sub r6,r6,1 @ subtract 1 from digit r6
		b .loop
	.break:
		add r4,r4,r7  @ add factorial of digit in r4
		div r0,r0,10  @ remove the current digit from r0
		call .start
.is_factorian:
	movu r1,1  @ r0 is a factorian number
	call .output_factorian
.is_dudeny:
	movu r2,1
	call .output_dudeny
.return:
	movu r1,0
	cmp r4,r3 @ compare r4 with copy of r0
	beq .is_factorian
.output_factorian:
	.print r1 @ print r1
	movu r2,0
	mul r4,r5,r5  @ find cube of r5
	mul r4,r4,r5
	cmp r4,r3   @ check if cube of r5 is r0
	beq .is_dudeny
.output_dudeny:
	.print r2 @ print dudeny









