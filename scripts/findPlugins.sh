if test -e $HOME/.vimrc
then
    grep "Plug" ${HOME}/.vimrc | grep -c "[\'].*[\']" > pluglist.raw
    grep "Plug" ${HOME}/.vimrc | grep -sEo "[\'].*[\']" >> pluglist.raw
    cat pluglist.raw
fi
if test -e $HOME/.config/nvim/init.vim
then
    grep "Plug" ${HOME}/.config/nvim/init.vim | grep -c "[\'].*[\']" > pluglist.raw
    grep "Plug" ${HOME}/.config/nvim/init.vim | grep -sEo "[\'].*[\']" >> pluglist.raw
    cat pluglist.raw
fi	
