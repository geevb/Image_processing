# Image Processing
Image processing using OpenCV C++ to make some basic filtering on images, such as GrayScale, Thresholding, Zoom In/Out, Inverted Colors, etc...

## Getting Started
To get this running, you'll only need a working C++ compiler and the most recent OpenCV version downloaded alongside a Linux environment.

### Installing
After donwloading, extract the OpenCV file in this folder and proceed with the following:
```
cd ~/opencv*version*
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j7 # runs 7 jobs in parallel
sudo make install
```
For further instructions see this: https://docs.opencv.org/trunk/d7/d9f/tutorial_linux_install.html
## Authors
* **Getúlio Vieira Benincá** 
