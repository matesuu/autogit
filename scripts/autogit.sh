#!/bin/bash

help_str="help"
init_str="init"
remove_str="remove"
info_str="info"
push_str="push"
pull_str="pull"

help(){

    echo "\n\nhelp:\n\n"
    echo "init - initialize a local and remote repository - autogit init <remote_url_name> \n"
    echo "remove - remove currently existing remote - autogit remove \n"
    echo "info - display current information of current remotes - autogit info \n"
    echo "push - push all current changes in local to remote - autogit push \n"
    echo "pull - pull all current changes from remote to local - autogit pull \n\n"

    echo "written by matesuu - (December 2024) \n\n"
}

init(){

    git init && git symbolic-ref HEAD refs/heads/main
    git config --global init.defaultBranch main

    git remote add origin $2
    git remote -v
}

remove(){

    git remote remove origin
    git remote -v
}

info(){
    
    git remote -v
}

push(){

    git status
    git add . --all

    git commit -m "commited to repo using autogit"

    git pull --rebase origin main
    git push -u -f origin main
}

pull(){

    git status
    git pull origin main
}

if [ $# -eq 0 ]; then

    help
    exit 0
fi

if [ "$1" == "$help_str" ]; then

    help

elif [ "$1" == "$init_str" ]; then

    if [ $# -eq 2 ]; then
        init $1 $2
        echo "successfully initialized and added remote repository "

    else

        echo "missing argument: remote repository url "
        exit 1
    fi

elif [ "$1" == "$remove_str" ]; then

    echo "removing... "
    remove

elif [ "$1" == "$info_str" ]; then

    echo "remote repository information \n"
    info

elif [ "$1" == "$push_str" ]; then

    echo "pushing to remote... "
    push

elif [ "$1" == "$pull_str" ]; then

    echo "pulling from remote... "
    pull

else

    echo "error: unknown command "
fi

exit 0