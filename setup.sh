sudo apt-get update
sudo apt-get upgrade  
sudo apt-get install python-numpy  python-matplotlib
        python-pandas python-sympy python-nose python-scipy

sudo apt-get install build-essential cmake pkg-config unzip

sudo apt-get install build-essential cmake git
sudo apt-get install pkg-config unzip ffmpeg  python-dev python3-dev python-numpy python3-numpy
sudo apt-get install libopencv-dev libgtk-3-dev libdc1394-22 libdc1394-22-dev libjpeg-dev libpng12-dev 
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libxine2-dev libgstreamer0.10-dev 
sudo apt-get install libv4l-dev libtbb-dev libfaac-dev libmp3lame-dev libtheora-dev 
sudo apt-get install libvorbis-dev libxvidcore-dev v4l-utils libopencore-amrnb-dev libopencore-amrwb-dev
sudo apt-get install libjasper-dev libgstreamer-plugins-base0.10-dev
sudo apt-get install libjpeg8-dev libx264-dev libatlas-base-dev gfortran

cd ~
wget -O opencv.zip https://github.com/Itseez/opencv/archive/3.1.0.zip
unzip opencv.zip

tar xzvf opencv-2.4.9.13.tar.gz
cd opencv-2.4.9.13
mkdir build
cd build

cmake -D CMAKE_BUILD_TYPE=RELEASE -D INSTALL_C_EXAMPLES=ON  
        -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON
        -D WITH_QT=ON -D CMAKE_INSTALL_PREFIX=/usr/local
        -D WITH_OPENGL=ON -D WITH_V4L=ON -D WITH_CUDA=ON
        -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_TBB=ON ..

make
sudo make install

sudo nano /etc/ld.so.conf.d/opencv.conf


