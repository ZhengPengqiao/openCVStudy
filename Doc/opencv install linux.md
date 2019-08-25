# opencv安装

## opencv-3.4.0 安装

* Doc中有一份opencv-3.4.0.tar.gz源码
  * tar xvf opencv-3.4.0.tar.gz
  * cd opencv-3.4.0/
  * cmake . -DCMAKE_INSTALL_PREFIX=../_install/
  * make
  * sudo make install

## 问题

* cmake .  时出现错误
    ```C
    zpq@zpq-pc:~/WorkSpaces/openCVStudy/Doc/opencv-3.4.0$ cmake .
    CMake Error at CMakeLists.txt:11 (message):

      FATAL: In-source builds are not allowed.

            You should create a separate directory for build files.

    -- Configuring incomplete, errors occurred!
    ```
  * 错误原因:编译路径和源码在同一个目录了
  * 解决: (在opencv-3.2.0目录下)
    * mkdir build
    * cd build
    * cmake .. -DCMAKE_INSTALL_PREFIX=../../opencv-3.4.0_install/
    * make -j4
    * make install

## 配置

* export PATH=$PATH:/home/zpq/WorkSpaces/openCVStudy/Doc/opencv-3.4.0_install/bin
* export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/zpq/WorkSpaces/openCVStudy/Doc/opencv-3.4.0_install/lib

## 报找不到so的错误时，需要手动软链接

```C
ln -sv libopencv_calib3d.so.3.4 libopencv_calib3d.so
ln -sv libopencv_objdetect.so.3.4 libopencv_objdetect.so
ln -sv libopencv_core.so.3.4 libopencv_core.so
ln -sv libopencv_photo.so.3.4 libopencv_photo.so
ln -sv libopencv_dnn.so.3.4 libopencv_dnn.so
ln -sv libopencv_shape.so.3.4 libopencv_shape.so
ln -sv libopencv_features2d.so.3.4 libopencv_features2d.so
ln -sv libopencv_stitching.so.3.4 libopencv_stitching.so
ln -sv libopencv_flann.so.3.4 libopencv_flann.so
ln -sv libopencv_superres.so.3.4 libopencv_superres.so
ln -sv libopencv_highgui.so.3.4 libopencv_highgui.so
ln -sv libopencv_videoio.so.3.4 libopencv_videoio.so
ln -sv libopencv_imgcodecs.so.3.4 libopencv_imgcodecs.so
ln -sv libopencv_video.so.3.4 libopencv_video.so
ln -sv libopencv_imgproc.so.3.4 libopencv_imgproc.so
ln -sv libopencv_videostab.so.3.4 libopencv_videostab.so
ln -sv libopencv_ml.so.3.4 libopencv_ml.so
```