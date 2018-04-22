# Image Processing

Image processing using OpenCV C++ to make some basic filtering on images, such as GrayScale, Thresholding, Zoom In/Out, Inverted Colors, etc...

## Getting Started
To get this running, you'll only need a working C++ compiler and the most recent OpenCV version downloaded.

### Prerequisites

What things you need to install the software and how to install them

```
Give examples
```

### Installing
After the downloads mentionted above, extract the OpenCv file in this folder and proceed with the following:
```
cd ~/opencv*version*
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j7 # runs 7 jobs in parallel
sudo make install
```
## Authors

* **Getúlio Vieira Benincá** 
