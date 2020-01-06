__DYNAMIC  =  0;

MEMORY
{
  ram1 (rwx) : ORIGIN = 0x0, LENGTH = 4K /* vector table */
  ram2 (rwx) : ORIGIN = 0x408, LENGTH = 510K
}

/* Set Stack to end of memory */
PROVIDE (__stack = 0x80000 - 1K);

/*
 * Initalize some symbols to be zero so we can reference them in the
 * crt0 without core dumping. These functions are all optional, but
 * we do this so we can have our crt0 always use them if they exist. 
 * This is so BSPs work better when using the crt0 installed with gcc.
 * We have to initalize them twice, so we cover a.out (which prepends
 * an underscore) and coff object file formats.
 */
PROVIDE (hardware_init_hook = 0);
PROVIDE (_hardware_init_hook = 0);
PROVIDE (software_init_hook = 0);
PROVIDE (_software_init_hook = 0);
/*
 * stick everything in ram (of course)
 */
SECTIONS
{
/* .vecs : { vectors.obj } > ram1 */
  VECTORS : {
     __vectors = .;
     *(VECTORS)
  } > ram1
  .text :
  {
    *(.text)
    . = ALIGN(0x4);
     __CTOR_LIST__ = .;
    ___CTOR_LIST__ = .;
    LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2)
    *(.ctors)
    LONG(0)
    __CTOR_END__ = .;
    __DTOR_LIST__ = .;
    ___DTOR_LIST__ = .;
    LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2)
    *(.dtors)
     LONG(0)
    __DTOR_END__ = .;
    *(.rodata)
    *(.gcc_except_table) 

    __INIT_SECTION__ = . ;
    LONG (0x4e560000)	/* linkw %fp,#0 */
    *(.init)
    SHORT (0x4e5e)	/* unlk %fp */
    SHORT (0x4e75)	/* rts */

    __FINI_SECTION__ = . ;
    LONG (0x4e560000)	/* linkw %fp,#0 */
    *(.fini)
    SHORT (0x4e5e)	/* unlk %fp */
    SHORT (0x4e75)	/* rts */

    _etext = .;
    *(.lit)
  } > ram2

  .data :
  {
    *(.shdata)
    *(.data)
    _edata = .;
  } > ram2

  .bss :
  {
    . = ALIGN(0x4);
    __bss_start = . ;
    *(.shbss)
    *(.bss)
    *(COMMON)
    __bss_end = .;
    _end =  ALIGN (0x8);
    __end = _end;
  } > ram2

  .stab 0 (NOLOAD) :
  {
    *(.stab)
  }

  .stabstr 0 (NOLOAD) :
  {
    *(.stabstr)
  }
}