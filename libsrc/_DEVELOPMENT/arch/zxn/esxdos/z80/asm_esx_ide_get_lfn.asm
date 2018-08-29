; unsigned char esx_ide_get_lfn(struct esx_lfn *dir, struct esx_cat_entry *query)

INCLUDE "config_private.inc"

SECTION code_esxdos

PUBLIC asm_esx_ide_get_lfn

EXTERN __esxdos_error_mc, error_znc
EXTERN __nextos_nstr_to_cstr

IF __ZXNEXT

asm_esx_ide_get_lfn:

   ; enter : hl = struct esx_lfn *dir
   ;         de = struct esx_cat_entry *query
   ;
   ; exit  : success
   ;
   ;            hl = 0
   ;            carry reset
   ;
   ;         fail
   ;
   ;            hl = -1
   ;            carry set, errno set to zxnextos code
   ;
   ; uses  : all except af', iy

   push de                    ; save query
   
   ld e,(hl)
   inc hl
   ld d,(hl)
   inc hl
   
   ld c,l
   ld b,h                      ; bc = &lfn

   ex (sp),hl
   push hl
   
   ld hl,__ESX_FILENAME_LFN_MAX + 1
   add hl,bc
   
   ex (sp),hl                  ; save &time
   push hl                     ; save query

   ex de,hl                    ; hl = struct esx_cat *dir

   ; bc = &lfn
   ; hl = struct esx_cat *
   ; stack = &lfn, &time, query
   
   inc hl
   ld e,(hl)
   inc hl
   ld d,(hl)                   ; de = dir.filename
   
   push de                     ; save dir.filename
   
   inc hl
   ld e,(hl)
   inc hl
   ld d,(hl)                   ; de = dir.dir_handle
   
IF __SDCC_IY

   push de
   pop iy

ELSE

   push de
   pop ix                      ; ix = dir.dir_handle

ENDIF

   pop hl                      ; hl = dir.filename
   pop de                      ; de = query

   ; bc = &lfn
   ; de = query
   ; hl = filename
   ; ix = dir_handle
   ; stack = &lfn, &time
   
   exx
   
   ld de,__NEXTOS_IDE_GET_LFN
   ld c,7
   
   rst __ESX_RST_SYS
   defb __ESX_M_P3DOS
   
   jr nc, error_get_lfn

   ex (sp),hl                  ; hl = &time
   
   ld (hl),e
   inc hl
   ld (hl),d                   ; write dos_time
   inc hl
   
   ld (hl),c
   inc hl
   ld (hl),b                   ; write dos_date
   inc hl
   
IF __SDCC_IY

   push iy
   pop de

ELSE

   push ix
   pop de

ENDIF

   ld (hl),e
   inc hl
   ld (hl),d
   inc hl
   
   pop de
   
   ld (hl),e
   inc hl
   ld (hl),d                   ; write file size

   ; zero terminate lfn
   
   pop hl                      ; hl = &lfn

   call __nextos_nstr_to_cstr
   jp error_znc

error_get_lfn:

   pop hl
   pop hl

   jp __esxdos_error_mc

ELSE

asm_esx_ide_get_lfn:

   ld a,__ESX_ENONSENSE
   jp __esxdos_error_mc

ENDIF
