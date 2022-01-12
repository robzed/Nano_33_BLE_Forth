\ Blocks support for Nano 33 BLE Forth
\ Written by Rob Probin, Jan 2022
\ Copyright (c) 2022 Rob Probin
\ Released under the MIT license

\ 00000001111111111222222222233333333334444444444566666666666666
\ 34567890123456789012345678901234567890123456789012345678901234


ANEW TASK-BLOCKS_TEST.FTH
decimal

: (blankbuf) ( buffer -- ) ." (blankbuf)> " .s BLOCKSIZE 32 fill ; 
: (bufwr) ( caddr u buffer -- buffer+u ) ." (bufwr)> " .s 2dup + >r swap cmove r> ;
: (buftest) ( num buffer -- ) dup (blankbuf) S" Screen " rot 
  (bufwr)  swap 0 <# #S #> rot (bufwr) drop ;

: TESTBUF
  1 dup buffer cr .s (buftest) update
  2 dup buffer cr .s (buftest) update
  3 dup buffer cr .s (buftest) update
  4 dup buffer cr .s (buftest) update
;

