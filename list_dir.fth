\ list directory support for Nano 33 BLE Forth
\ Written by Rob Probin, Jan 2022
\ Copyright (c) 2022 Rob Probin
\ Released under the MIT license
ANEW FILE_SYSTEM.FTH

: typec ( cstring-addr -- ) begin dup c@ dup 0<> while emit 1+ repeat 2drop ;
: rootdir ( -- cstring-addr ) s\" /\z" drop ;

create dirstruct 0 xdirentry allot

: .ftype ( c -- ) 
  case
    0 OF ." ???" ENDOF
    1 OF ." FIFO" ENDOF
    2 OF ." CHR" ENDOF
    3 OF ." DIR" ENDOF
    4 OF ." BLK" ENDOF
    5 OF ." REG" ENDOF
    6 OF ." LNK" ENDOF
    7 OF ." SOCK" ENDOF
    dup . 
    ENDCASE
; 

: .file ( -- )
      dirstruct 3 xdirentry + c@ dup . space .ftype
      space
      dirstruct 1 xdirentry + typec 
;

\ File types:
\  0 = UNKNOWN could not be determined.
\  1 = FIFO  named pipe FIFO.
\  2 = CHR,  character device.
\  3 = DIR,  directory.
\  4 = BLK,  block device.
\  5 = REG,  regular file.
\  6 = LNK,  symbolic link.
\  7 = SOCK, UNIX domain socket.


: (.entries) ( dir -- ) #dir CR ." Entries = " . ;

: ls ( cstring-addr -- ) 
  opendir 
  dup if 
    dup (.entries)
    begin
      dup dirstruct readdir  
      1 =
    while
      cr .file
    repeat
    closedir drop 
  else 
    cr ." Open failed " 
  then
  cr
;

\ Not finished
: ls" 
STATE @ IF
ELSE
THEN
;

