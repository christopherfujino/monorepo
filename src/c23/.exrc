let s:cpo_save=&cpo
set cpo&vim
imap <C-G>S <Plug>ISurround
imap <C-G>s <Plug>Isurround
inoremap <silent> <Plug>(fzf-maps-i) :call fzf#vim#maps('i', 0)
inoremap <expr> <Plug>(fzf-complete-buffer-line) fzf#vim#complete#buffer_line()
inoremap <expr> <Plug>(fzf-complete-line) fzf#vim#complete#line()
inoremap <expr> <Plug>(fzf-complete-file-ag) fzf#vim#complete#path('ag -l -g ""')
inoremap <expr> <Plug>(fzf-complete-file) fzf#vim#complete#path("find . -path '*/\.*' -prune -o -type f -print -o -type l -print | sed 's:^..::'")
inoremap <expr> <Plug>(fzf-complete-path) fzf#vim#complete#path("find . -path '*/\.*' -prune -o -print | sed '1d;s:^..::'")
inoremap <expr> <Plug>(fzf-complete-word) fzf#vim#complete#word()
inoremap <C-W> u
inoremap <C-U> u
nnoremap  <Cmd>nohlsearch|diffupdate|normal! 
nnoremap  :Files
nnoremap  :tabe
nmap  d
omap <silent> % <Plug>(MatchitOperationForward)
xmap <silent> % <Plug>(MatchitVisualForward)
nmap <silent> % <Plug>(MatchitNormalForward)
nnoremap & :&&
vnoremap <4MiddleMouse <Nop>
nnoremap <4MiddleMouse <Nop>
vnoremap <3MiddleMouse <Nop>
nnoremap <3MiddleMouse <Nop>
vnoremap <2MiddleMouse <Nop>
nnoremap <2MiddleMouse <Nop>
vnoremap <1MiddleMouse <Nop>
nnoremap <1MiddleMouse <Nop>
xnoremap <silent> <expr> @ mode() ==# 'V' ? ':normal! @'.getcharstr().'' : '@'
xnoremap <silent> <expr> Q mode() ==# 'V' ? ':normal! @=reg_recorded()' : 'Q'
xmap S <Plug>VSurround
nnoremap Y y$
omap <silent> [% <Plug>(MatchitOperationMultiBackward)
xmap <silent> [% <Plug>(MatchitVisualMultiBackward)
nmap <silent> [% <Plug>(MatchitNormalMultiBackward)
omap <silent> ]% <Plug>(MatchitOperationMultiForward)
xmap <silent> ]% <Plug>(MatchitVisualMultiForward)
nmap <silent> ]% <Plug>(MatchitNormalMultiForward)
xmap a% <Plug>(MatchitVisualTextObject)
nmap cS <Plug>CSurround
nmap cs <Plug>Csurround
nmap ds <Plug>Dsurround
omap <silent> g% <Plug>(MatchitOperationBackward)
xmap <silent> g% <Plug>(MatchitVisualBackward)
nmap <silent> g% <Plug>(MatchitNormalBackward)
xmap gS <Plug>VgSurround
nmap ySS <Plug>YSsurround
nmap ySs <Plug>YSsurround
nmap yss <Plug>Yssurround
nmap yS <Plug>YSurround
nmap ys <Plug>Ysurround
xmap <silent> <Plug>(MatchitVisualTextObject) <Plug>(MatchitVisualMultiBackward)o<Plug>(MatchitVisualMultiForward)
onoremap <silent> <Plug>(MatchitOperationMultiForward) :call matchit#MultiMatch("W",  "o")
onoremap <silent> <Plug>(MatchitOperationMultiBackward) :call matchit#MultiMatch("bW", "o")
xnoremap <silent> <Plug>(MatchitVisualMultiForward) :call matchit#MultiMatch("W",  "n")m'gv``
xnoremap <silent> <Plug>(MatchitVisualMultiBackward) :call matchit#MultiMatch("bW", "n")m'gv``
nnoremap <silent> <Plug>(MatchitNormalMultiForward) :call matchit#MultiMatch("W",  "n")
nnoremap <silent> <Plug>(MatchitNormalMultiBackward) :call matchit#MultiMatch("bW", "n")
onoremap <silent> <Plug>(MatchitOperationBackward) :call matchit#Match_wrapper('',0,'o')
onoremap <silent> <Plug>(MatchitOperationForward) :call matchit#Match_wrapper('',1,'o')
xnoremap <silent> <Plug>(MatchitVisualBackward) :call matchit#Match_wrapper('',0,'v')m'gv``
xnoremap <silent> <Plug>(MatchitVisualForward) :call matchit#Match_wrapper('',1,'v'):if col("''") != col("$") | exe ":normal! m'" | endifgv``
nnoremap <silent> <Plug>(MatchitNormalBackward) :call matchit#Match_wrapper('',0,'n')
nnoremap <silent> <Plug>(MatchitNormalForward) :call matchit#Match_wrapper('',1,'n')
nnoremap <silent> <Plug>SurroundRepeat .
tnoremap <silent> <Plug>(fzf-normal) 
tnoremap <silent> <Plug>(fzf-insert) i
nnoremap <silent> <Plug>(fzf-normal) <Nop>
nnoremap <silent> <Plug>(fzf-insert) i
onoremap <silent> <Plug>(fzf-maps-o) :call fzf#vim#maps('o', 0)
xnoremap <silent> <Plug>(fzf-maps-x) :call fzf#vim#maps('x', 0)
nnoremap <silent> <Plug>(fzf-maps-n) :call fzf#vim#maps('n', 0)
nnoremap <C-T> :tabe
nnoremap <C-P> :Files
nmap <C-W><C-D> d
nnoremap <C-L> <Cmd>nohlsearch|diffupdate|normal! 
imap S <Plug>ISurround
imap s <Plug>Isurround
inoremap  u
inoremap  u
inoremap <4MiddleMouse <Nop>
inoremap <3MiddleMouse <Nop>
inoremap <2MiddleMouse <Nop>
inoremap <1MiddleMouse <Nop>
let &cpo=s:cpo_save
unlet s:cpo_save
set background=light
set expandtab
set grepformat=%f:%l:%c:%m
set grepprg=rg\ --vimgrep\ -uu\ 
set helplang=en
set ignorecase
set noloadplugins
set makeprg=mk
set packpath=~/git/chris-monorepo/share/nvim/runtime
set rulerformat=%-10.(%4l,%3c%)
set runtimepath=~/.config/nvim,~/.local/share/nvim/lazy/lazy.nvim,~/.local/share/nvim/lazy/base16-vim,~/.local/share/nvim/lazy/vim-eunuch,~/.local/share/nvim/lazy/nvim-lspconfig,~/.local/share/nvim/lazy/vim-surround,~/.local/share/nvim/lazy/fzf,~/.local/share/nvim/lazy/vim-fugitive,~/.local/share/nvim/lazy/nvim-autopairs,~/.local/share/nvim/lazy/fzf.vim,~/git/chris-monorepo/share/nvim/runtime,~/git/chris-monorepo/share/nvim/runtime/pack/dist/opt/netrw,~/git/chris-monorepo/share/nvim/runtime/pack/dist/opt/matchit,~/git/chris-monorepo/lib/nvim,~/.local/state/nvim/lazy/readme
set shiftwidth=2
set smartcase
set splitbelow
set splitright
set tabstop=2
set termguicolors
set window=38
" vim: set ft=vim :
