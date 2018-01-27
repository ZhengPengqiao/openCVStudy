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
  * 解决:
    * mkdir build
    * cd build
    * cmake ..
  * 但是我这样做依然没有效果,  打印了CMakeList.txt的两个变量发现是一样的,所以尝试别的方法
    * 将判断的语句注释掉
        ```C
          # Disable in-source builds to prevent source tree corruption.
          if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
            message(FATAL_ERROR "
          FATAL: In-source builds are not allowed.
                You should create a separate directory for build files.
          ")
          endif()
        ```
    * cmake . -DCMAKE_INSTALL_PREFIX=../_install/
    * make
    * make install