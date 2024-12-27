#!/bin/bash

help_str="help"
init_str="init"
deinit_str="remove"
info_str="info"
new_str="new"
switch_str="switch"
delete_str="delete"
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

deinit(){

    git remote remove origin
    git remote -v
}

info(){

    git remote -v
    git branch
}

new(){

    git checkout -b $2
}

change(){

    git checkout $2
}

delete(){

    git branch -d $2
}

push(){

    git status
    git add . --all

    git commit -m "commited to repo using autogit"

    git pull --rebase origin $2
    git push -u origin $2
}

push_commit(){

    git status
    git add . --all

    git commit -m $3

    git pull --rebase origin $2
    git push -u origin $2

}

pull(){

    git status
    git pull origin $2
}

if [ $# -eq 0 ]; then

    help
    exit 0
fi

if [ "$1" == "$help_str" ]; then

    help

elif [ "$1" == "$init_str" ]; then

    if [ $# -eq 2 ]; then

        init $2
        echo "process finished "

    else

        echo "missing argument: remote repository url "
        exit 1
    fi

elif [ "$1" == "$deinit_str" ]; then

    deinit
    echo "process finished "

elif [ "$1" == "$info_str" ]; then

    info
    echo "process finished "

elif [ "$1" == "$new_str" ]; then

    if [ $# -eq 2 ]; then

        new $2
        echo "process finished "

    else

        echo "missing argument: target branch name "
        exit 1
    fi

elif [ "$1" == "$switch_str" ]; then

    if [ $# -eq 2 ]; then

        change $2
        echo "process finished "

    else

        echo "missing argument: target branch name "
        exit 1
    fi

elif [ "$1" == "$delete_str" ]; then

    if [ $# -eq 2 ]; then

        delete $2
        echo "process finished "

    else

        echo "missing argument: target branch name "
        exit 1
    fi

elif [ "$1" == "$push_str" ]; then

    if [ $# -ge 2 ]; then

        if [ $# -eq 2 ]; then

        push $2
        echo "process finished "

        else

        push_commit $2 $3
        echo "process finished "
        
        fi

    else

        push
        echo "process finished "
    
    fi

elif [ "$1" == "$pull_str" ]; then

    if [ $# -eq 2 ]; then

        pull $2
        echo "process finished "

    else

        echo "missing argument: branch name "
        exit 1
    fi

else

    echo "error: unknown command "
fi

exit 0
