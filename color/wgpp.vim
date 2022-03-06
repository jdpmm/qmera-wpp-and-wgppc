" Vim syntax file
" Language: wgpp

" Usage Instructions
" Put this file in .vim/syntax/wgpp.vim
" and add in your .vimrc file the next line:
" autocmd BufRead,BufNewFile *.wgpp set filetype=wgpp

if exists("b:current_syntax")
    finish
endif

syntax keyword wgppTodos TODO XXX FIXME NOTE

" Language keywords
syntax keyword wgppKeywords exit wout printf
syntax keyword wgppKeywords int chr ptr
syntax keyword wgppKeywords CHG NEG INC DEC ARITH
syntax keyword wgppKeywords sub add mul div mod pow

" Comments
syntax region wgppCommentLine start="#" end="#" contains=wgppTodos

" Strings
syntax region wgppString start=/\v"/ skip=/\v\\./ end=/\v"/
syntax region wgppString start=/\v'/ skip=/\v\\./ end=/\v'/

" Set highlights
highlight default link wgppTodos Todo
highlight default link wgppKeywords Keyword
highlight default link wgppCommentLine Comment
highlight default link wgppString String

let b:current_syntax = "wgpp"
