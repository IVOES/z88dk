;;
;; C stubs for Arkos invocation from zcc
;;

section code_sound_ay

;; public C symbols, matching .h header file
PUBLIC _msx_rom_ply_akg_stop

;; external Arkos 2 entry points
EXTERN asm_msx_rom_PLY_AKG_STOP

;;
;; void ply_akg_stop( void );
;;
defc _msx_rom_ply_akg_stop = asm_msx_rom_PLY_AKG_STOP
