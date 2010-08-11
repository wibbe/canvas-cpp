#! /bin/sh

cd `dirname $0`
platform=`uname`

echo "Fetching Skia..."
svn checkout http://skia.googlecode.com/svn/trunk/ skia

cd skia
if [$platform -eq 'darwin' ] ; then
  echo "Building Skia for mac..."
  make SKIA_BUILD_FOR=mac SKIA_DEBUG=true
else
  echo "Building Skia for linux..."
  make SKIA_DEBUG=true
fi

cd ..

echo "Fetching V8..."
svn checkout http://v8.googlecode.com/svn/trunk/ v8

cd v8
echo "Building V8..."
scons mode=debug library=static snapshot=off -j4

if [$platform -eq 'Linux'] ; then
  mv libv8_g.a libv8.a
fi
