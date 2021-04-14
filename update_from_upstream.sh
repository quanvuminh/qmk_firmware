#!/bin/sh
#https://docs.qmk.fm/#/newbs_git_using_your_master_branch
git checkout master
git fetch upstream
git pull upstream master
git push origin master
