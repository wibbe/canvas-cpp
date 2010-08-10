#! /bin/sh

cd `dirname $0`

echo "Fetching Skia..."
svn checkout http://skia.googlecode.com/svn/trunk/ skia

cd skia
make SKIA_BUILD_FOR=mac SKIA_DEBUG=true

cd ..

echo "Fetching V8..."
svn checkout http://v8.googlecode.com/svn/trunk/ v8

cd v8
echo "Building V8..."
scons mode=debug library=static snapshot=off -j4