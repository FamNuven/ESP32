# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Program/Espressif/frameworks/esp-idf-v4.4.2/components/bootloader/subproject"
  "D:/Reposit/ESP32/EXTI01/build/bootloader"
  "D:/Reposit/ESP32/EXTI01/build/bootloader-prefix"
  "D:/Reposit/ESP32/EXTI01/build/bootloader-prefix/tmp"
  "D:/Reposit/ESP32/EXTI01/build/bootloader-prefix/src/bootloader-stamp"
  "D:/Reposit/ESP32/EXTI01/build/bootloader-prefix/src"
  "D:/Reposit/ESP32/EXTI01/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Reposit/ESP32/EXTI01/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
