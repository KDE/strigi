#! /bin/bash
# script to create a release tarball for strigi
# this is needed since the project is split up in separate git moduls
TAG=0.7.6
git archive --format=tar --prefix=strigi-$TAG/ -o strigi-$TAG.tar v$TAG
for f in libstreams libstreamanalyzer strigidaemon strigiclient strigiutils; do
  cd $f
  git archive --format=tar --prefix=strigi-$TAG/$f/ -o tmptar v$TAG
  tar Af ../strigi-$TAG.tar tmptar
  rm tmptar
  cd -
done
bzip2 -9 strigi-$TAG.tar
