# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/prog/Espressif/frameworks/esp-idf-v4.4.2/components/bootloader/subproject"
  "E:/Reposit/ESP32/Blink01/build/bootloader"
  "E:/Reposit/ESP32/Blink01/build/bootloader-prefix"
  "E:/Reposit/ESP32/Blink01/build/bootloader-prefix/tmp"
  "E:/Reposit/ESP32/Blink01/build/bootloader-prefix/src/bootloader-stamp"
  "E:/Reposit/ESP32/Blink01/build/bootloader-prefix/src"
  "E:/Reposit/ESP32/Blink01/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/Reposit/ESP32/Blink01/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
