"-------------- Key-mapping(F2-F11 are free) ------------""
"Switch between .c/.h files
nnoremap <F2> :FSHere<CR>

function! FormatCurrentFile()
    silent execute "!clang-format -i ". " " . expand('%:p')
    :e
endfunction
au BufEnter,BufWrite *.c call FormatCurrentFile()
au BufEnter,BufWrite *.h call FormatCurrentFile()

function! FormatMakeFile()
    :set noet|retab!
endfunction
au BufWrite linux/Makefile call FormatMakeFile()

"------------- vim-quickui settings  ------------------"
let s:update = "update | w |"
let s:make_debug = "cd linux; make debug; \n"
let s:make_release = "cd linux; make; \n"
let s:clean = "cd linux; make clean; \n"

call quickui#menu#clear('P&roject')
" kmdr--io
call quickui#menu#install('P&roject', [
            \ [ 'ma&ke_debug', s:update.'call HTerminal(0.4, 300.0, "'. s:make_debug .'")' ],
            \ [ '&make_release', s:update.'call HTerminal(0.4, 300.0, "'. s:make_release .'")' ],
            \ [ 'run_&debug', s:update.'call FTerminal("clear; linux/debug/iproc \n")' ],
            \ [ '&run_release', s:update.'call FTerminal("clear; linux/release/iproc \n")' ],
            \ [ '&clean', s:update.'call HTerminal(0.4, 300.0, "'. s:clean .'")' ],
            \ [ "--", '' ],
            \ [ "l&ibc-help", 'call LibcSH()' ],
            \ [ "libc-help-under-curs&or", 'call LibcSHUC()' ],
            \ ], 5000)
