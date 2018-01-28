# opencv安装

## opencv-3.4.0 安装

* Doc中有一份opencv-3.4.0.tar.gz源码
  * tar xvf opencv-3.4.0.tar.gz
  * cd opencv-3.2.0/
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