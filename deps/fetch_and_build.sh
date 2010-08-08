#! /bin/sh

cd `dirname $0`

echo "Fetching Skia..."
svn checkout http://skia.googlecode.com/svn/trunk/ skia

cd skia
cp ../wscript.skia wscript
cp ../../waf .

echo "Building Skia..."
./waf configure
./waf -j4 -p

cd ..

echo "Fetching V8..."
svn checkout http://v8.googlecode.com/svn/trunk/ v8

cd v8
echo "Building V8..."
scons mode=release library=static snapshot=off