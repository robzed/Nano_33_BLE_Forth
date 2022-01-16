\ Blocks support for Nano 33 BLE Forth
\ Written by Rob Probin, Jan 2022
\ Copyright (c) 2022 Rob Probin
\ Released under the MIT license
ANEW TASK-BLOCKS.FTH

decimal

\ This definition make assumptions about the location in flash
1024 1024 * (R/W_Size) (R/W_#Blocks) * - constant flash_blocks_addr
1024 constant BLOCKSIZE
255 constant BLANKFLASH
(R/W_Size) BLOCKSIZE / constant BLK/FBLK
64 constant (BLKLINELEN)
BLOCKSIZE (BLKLINELEN) / constant (BLKHEIGHT)

variable SCR 0 SCR !  \ last block shown by list
variable BLK 0 BLK !  \ block being evaluated by load

\ flash_blocks_addr BLOCKSIZE dump 

: (BLKvalid) ( u -- f ) 1 (R/W_#Blocks) 1+ within ;
: (showSCR) ( u -- ) CR ." Scr# " . CR ;
: (list#) ( line -- ) dup 10 < if space then . ; 
: (listc) ( addr -- ) c@ dup 32 255 within if emit else drop [char] ? emit then ;
: (listline) ( addr line -- addr+64 ) 1+ (list#) ." : " (BLKLINELEN) 0 do dup (listc) 1+ loop CR ;
: (blk2faddr) ( block -- flash-addr ) 1- BLOCKSIZE * flash_blocks_addr + ;
: (listcore) ( buff-addr -- ) base @ swap decimal (BLKHEIGHT) 0 do I (listline) loop drop base ! ;
: (list) ( buff-addr u -- ) dup (showSCR) dup (BLKvalid) if SCR ! (listcore) else 2drop ." out of range" then ;
: FLASHLIST ( u -- ) dup (blk2faddr) swap (list) ;


: (blockblank) ( u -- flag ) (blk2faddr) c@ BLANKFLASH = ;

CREATE (buffer) (R/W_Size) ALLOT
variable (dirty) false (dirty) !  \ whole buffer is 1 flag 
\ variable (asigned) false (assigned) !
variable (fblkheld) 
: EMPTY-BUFFERS ( -- ) -1 (fblkheld) ! ;
EMPTY-BUFFERS

: (blk>fblk) ( u -- flash-block ) 1- BLK/FBLK / ; 
: (blk>foff) ( u -- flash-offset ) 1- BLK/FBLK MOD ;
: (blk>bufaddr) ( u -- address ) (blk>foff) BLOCKSIZE * (buffer) + ;

: UPDATE ( -- ) true (dirty) ! ; 

: (checkerr) ( err -- ) dup if CR ." Flash Err " . ABORT else drop then ;
: (readflash) ( buffer flash-block -- ) 1 (R/W) (checkerr) ;
: (writeflash) ( buffer flash-block -- ) 0 (R/W) (checkerr) ;

: SAVE-BUFFERS ( -- ) (dirty) @ if (buffer) (fblkheld) @ (writeflash) false (dirty) ! then ;
: (load-buffer) ( flash-block -- ) (buffer) swap dup (fblkheld) ! (readflash) false (dirty) ! ;

: (isBLKinBuf) ( u -- f ) (blk>fblk) (fblkheld) @ = ;

: BUFFER ( u -- a-addr)  \ return a buffer assigned to a block number
  dup  (isBLKinBuf) false = if SAVE-BUFFERS then
  dup (blk>fblk) (fblkheld) !
  (blk>bufaddr) ;

: LIST ( u -- ) dup (isBLKinBuf) if 
        dup (blk>bufaddr) swap (list) 
    else FLASHLIST then 
;


: BLOCK  ( u -- a-addr ) dup (isBLKinBuf) if (blk>bufaddr) else dup BUFFER swap (blk>fblk) (load-buffer) then ;

: FLUSH ( -- ) SAVE-BUFFERS EMPTY-BUFFERS ;

