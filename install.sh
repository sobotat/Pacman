sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev cmake gcc g++ build-essential
rm -r build
mkdir build
cd build
cmake ..
make