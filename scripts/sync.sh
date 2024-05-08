#!/bin/bash
highlight="\e[34m" # red
warn_highlight="\e[31m" # blue
reset_format="\e[0m"

# shellcheck disable=SC2059
printf "\n⚓ ${highlight}Syncing Remote Repo with ALL current changes${reset_format}\n"

(git add -A)
(git commit -am "sync ALL changes")
(git push)

# TODO update script to support syncing with specific directories