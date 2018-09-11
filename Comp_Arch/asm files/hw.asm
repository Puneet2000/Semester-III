.main:
	movu r0,1
.check:
	addu r3,r0,0
	movu r4,0
	movu r5,0
.start:
	cmp r0,0
	beq .return
	mod r6,r0,10
	add r5,r5,r6
	movu r7,1
	cmp r6,0
	beq .break
	.loop:
		cmp r6,0
		beq .break
		mul r7,r7,r6
		sub r6,r6,1
		b .loop
	.break:
		add r4,r4,r7
		div r0,r0,10
		call .start
.is_factorian:
	movu r1,1
	call .output_factorian
.is_dudeny:
	movu r2,1
	call .output_dudeny
.return:
	movu r1,0
	cmp r4,r3
	beq .is_factorian
.output_factorian:
	.print r1
	movu r2,0
	mul r4,r5,r5
	mul r4,r4,r5
	cmp r4,r3
	beq .is_dudeny
.output_dudeny:
	.print r2
	add r0,r3,1
	cmpu r0,60000
	beq .exit
	b .check
.exit:











