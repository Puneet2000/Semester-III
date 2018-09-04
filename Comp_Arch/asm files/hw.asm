@ CS17BTECH11029
.main:
	movu r0,40
	add r8,r0,0
	movu r3,0
	movu r9,0
.start:
	cmp r0,0
	beq .return
	mod r10,r0,10
	add r9,r9,r10
	movu r4,1
	movu r5,1
	.loop:
		cmp r5,r10
		bgt .break
		mul r4,r4,r5
		add r5,r5,1
		b .loop
	.break:
		add r3,r3,r4
		div r0,r0,10
		call .start

.is_factorian:
	movu r1,1
	call .output
.is_dudeny:
	movu r2,1
	call .output2
.return:
	movu r1,0
	cmp r3,r8
	beq .is_factorian
.output:
	.print r1
	movu r2,0
	mul r11,r9,r9
	mul r11,r11,r9
	cmp r11,r8
	beq .is_dudeny
.output2:
	.print r2









