\ Blocks support for Nano 33 BLE Forth
\ Written by Rob Probin, Jan 2022
\ Copyright (c) 2022 Rob Probin
\ Released under the MIT license
ANEW TASK-BLOCKS2.FTH

decimal

: (keyinblock) ( addr -- addr | 0 ) key dup 3 = if drop exit then dup 10 = addr ;  
: rxtextblock ( n -- ) (buffer) 0 ( n address offset ) begin 2dup (blockinput1) dup BLOCKSIZE >= until 2drop true (dirty) ! ;

: LOAD ( n -- ) drop ;

: EDIT ( -- ) ;

\ 00000001111111111222222222233333333334444444444566666666666666
\ 34567890123456789012345678901234567890123456789012345678901234

\ update the following words: EVALUATE \ REFILL 
