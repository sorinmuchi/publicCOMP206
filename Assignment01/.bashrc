# .bashrc

# Source global definitions
if [ -f /usr/socs/Profile ]; then
        . /usr/socs/Profile
fi

# User specific aliases and functions
export PATH=$PATH:$HOME/Source
export PS1=["\u"]["\h"]["\w"]["What doesn't kill you makes you stronger"]

alias lsa='ls -l -a'
alias backup='backup.sh'

pushd Source
backup
popd
