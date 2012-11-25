#!/bin/sh

# This script will retrieve the strigi submodules for you
# Please note that unless you edit .gitmodules the submodules will be
# cloned from anongit.kde.org, even if you have cloned via
# git@git.kde.org (which you should not have done, anyway).
# See http://community.kde.org/Sysadmin/GitKdeOrgManual#Let_Git_rewrite_URL_prefixes
# This script assumes that you have the following lines in your .gitconfig file:
#
#[url "git://anongit.kde.org/"]
#    insteadOf = kde:
#[url "git@git.kde.org:"]
#    pushInsteadOf = kde:
#

git submodule sync
git submodule init
git submodule update
