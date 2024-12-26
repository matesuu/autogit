#!/bin/bash

help_str="help"
init_str="init"
remove_str="remove"
info_str="info"
push_str="push"
pull_str="pull"

help(){

    echo "\n\nhelp:\n\n"
    echo "init - initialize a local and remote repository and create branch main - autogit init <remote_url_name> \n"
    echo "deinit - remove currently existing remote - autogit deinit \n"
    echo "info - display current information of current remotes and branches - autogit info \n"
    echo "new - creates a new branch within remote - autogit new <branch_name> \n"
    echo "switch - changes current working branch - autogit change <branch_name> \n"
    echo "delete - deletes a given branch from remote - autogit delete <branch_name> \n"
    echo "push - push all current changes to a specified branch - autogit push <branch_name> <optional: commit message> \n"
    echo "pull - pull all current changes from a specified branch - autogit pull <branch_name> \n\n"

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
    git branch
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
        echo "process finished "

    else

        echo "missing argument: remote repository url "
        exit 1
    fi

elif [ "$1" == "$remove_str" ]; then

    remove
    echo "process finished "

elif [ "$1" == "$info_str" ]; then
    info
    echo "process finished "

elif [ "$1" == "$push_str" ]; then

    push
    echo "process finished "

elif [ "$1" == "$pull_str" ]; then

    pull
    echo "process finished "

else

    echo "error: unknown command "
fi

exit 0


