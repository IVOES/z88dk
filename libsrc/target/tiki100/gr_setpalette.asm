;
;	TIKI-100 graphics routines
;	by Stefano Bodrato, Fall 2015
;
;	Edited by Frode van der Meeren
;
;   Palette is always 16 colors long, 'len' is the number
;   of colors being passed, which will be copied many times
;
; void __FASTCALL__ gr_setpalette(int len, char *palette)
;
;	Changelog:
;
;	v1.2 - FrodeM
;	   * Made sure no palette writes take place when palette register is updated
;	   * Palette register is only written to once per entry in char palette
;	   * Use address $F04D to store graphics mode instead of dedicated byte
;
;	$Id: gr_setpalette.asm,v 1.3 2016-06-10 23:01:47 dom Exp $
;

SECTION code_clib
PUBLIC gr_setpalette
PUBLIC _gr_setpalette

INCLUDE	"target/cpm/def/tiki100.def"

gr_setpalette:
_gr_setpalette:
	pop	bc
	pop	hl		; *palette
	pop	de		; len
	push	de
	push	hl
	push	bc

	ld	d,e		; Number of colours in selected mode
	ld	b,0		; Palette index

	ld	a,e
set_loop:
	push	af
	ld	a,(hl)
	inc	hl
	push	bc
	push	de
	push	hl
	call	do_set
	pop	hl
	pop	de
	pop	bc
	inc	b
	pop	af
	dec	a
	jr	nz,set_loop

	ret
	

;
; Writes a single palette color from a palette of a given size,
; where the palette is looping through all 16 palette entries.
; Size 2, 4 and 16 makes sense, and no other values for size
; should be used.
;
;
; Input:
; 	A = Palette color
; 	B = Palette index
;	D = number of colours in selected mode
;
.do_set
	cpl
	LD E,A
	ld	hl,PORT_0C_COPY
.palette_loop
	PUSH	DE
	DI
	ld	a,(hl)
	and	$7F
	OUT	($0C),A		; Make sure write-flag is clear in advance to avoid hardware race-conditions
	LD	A,E
	OUT	($14),A		; Set palette register (prepare the color to be loaded)
	ld	a,(hl)
	and	$70
	or	b
	OUT	($0C),A		; Set index
	or	$80
	OUT	($0C),A		; Initiate write
	LD	C,18
.wait_loop
	DEC	C
	JP	NZ,wait_loop	; wait 288 clocks, 72usec for HBLANK to trigger (64usec period + 8usec margin)
	and	$7F
	OUT	($0C),A		; End write
	ld	(hl),a
	EI
	POP	DE

	LD	A,B
	ADD	D		; move to next palette position
	LD	B,A
	CP	16
	JR	C,palette_loop
	RET


