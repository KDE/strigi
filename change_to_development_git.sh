#! /bin/bash

# This script will retrieve the strigi submodules for you

# if you checkout out via git@git.kde.org, also check out the
# submodules like that
if grep -q git@git.kde.org .git/config; then
	perl -pi -e 's#http://anongit.kde.org/#git\@git.kde.org:#' .gitmodules
fi
git submodule sync
git submodule init
git submodule update
# revert, so that the change will not be accidentally committed
git checkout .gitmodules
