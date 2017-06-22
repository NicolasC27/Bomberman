hg clone https://bitbucket.org/sinbad/ogre
return=$?
if [ return == 0 ]
then
    echo "Error: hg not found: install mercurial"
    exit
fi

hg clone https://bitbucket.org/cabalistic/ogredeps

cd ogredeps
cmake .
make -j9
make install
cd ../

cd ogre
cmake . -DOGRE_DEPENDENCIES_DIR=../ogredeps/ ..
make -j9

rm -rf ogre