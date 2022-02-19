# Copyright 2014-present PlatformIO <contact@platformio.org>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""
No Comments
"""

import json
from os.path import isfile, isdir, join

from platformio.util import get_systype

from SCons.Script import COMMAND_LINE_TARGETS, DefaultEnvironment

env = DefaultEnvironment()
platform = env.PioPlatform()
board_config = env.BoardConfig()

FRAMEWORK_DIR = platform.get_package_dir("framework-cmsis-at32f43")
CMSIS_DIR = join(platform.get_package_dir("framework-cmsis"), "CMSIS")
assert isdir(FRAMEWORK_DIR)
assert isdir(CMSIS_DIR)


mcu = board_config.get("build.mcu", "")
mcu_type = mcu[:-2]
series = mcu_type[:7].upper() + "xx"
upload_protocol = env.subst("$UPLOAD_PROTOCOL")

env.Append(
    ASFLAGS=["-x", "assembler-with-cpp"],
    CFLAGS=[
        "-std=gnu11",
        ],
    CCFLAGS=[
        "-O1",  # optimize for speed Os
        "-mcpu=%s" % board_config.get("build.cpu"),
        "-mthumb",
        "-ffunction-sections",  # place each function in its own section
        "-fdata-sections",
        "-nostdlib",
        "--param",
        "max-inline-insns-single=500",
        #"-print-multi-lib", #to check library versions
    ],
    CXXFLAGS=[
        "-fno-rtti",
        "-fno-exceptions",
    ],
    CPPPATH=[
        join(FRAMEWORK_DIR, "libraries", "AT32F43x_StdPeriph_Driver", "include"),      
        join(FRAMEWORK_DIR, "libraries", "AT32F43x_USB-Device_Driver", "include"),  
        join(FRAMEWORK_DIR, "libraries", "AT32F435_437_board"),      
    ],
    LIBS=[
        "c",
        "m",
        "gcc",
        "stdc++",
    ],
    LIBPATH=[join(CMSIS_DIR, "DSP", "Lib", "GCC")],
)

#Floating point unit: hard (hardware) | softfp (software)
if (
    any(cpu in board_config.get("build.cpu") for cpu in ("cortex-m4"))
):
    env.Append(
        CFLAGS=["-mfpu=fpv4-sp-d16", "-mfloat-abi=hard"],
        CCFLAGS=["-mfpu=fpv4-sp-d16", "-mfloat-abi=hard"],
        LINKFLAGS=["-mcpu=%s" % board_config.get("build.cpu"), "-mfpu=fpv4-sp-d16", "-mfloat-abi=hard"],
    )

# copy CCFLAGS to ASFLAGS (-x assembler-with-cpp mode)
env.Append(ASFLAGS=env.get("CCFLAGS", [])[:])

#
# Target: Build Core Library
#


libs = []

libs.append(env.BuildLibrary(
        join("$BUILD_DIR", "AT32F43x_StdPeriph"), join(FRAMEWORK_DIR, "libraries", "AT32F43x_StdPeriph_Driver")
    ))
libs.append(env.BuildLibrary(
        join("$BUILD_DIR", "AT32F43x_USB-Device"), join(FRAMEWORK_DIR, "libraries", "AT32F43x_USB-Device_Driver")
    ))
libs.append(env.BuildLibrary(
        join("$BUILD_DIR", "AT32F435_437_board"), join(FRAMEWORK_DIR, "libraries", "AT32F435_437_board")
    ))


#print("BuildLibrary(): " + env.subst(join(FRAMEWORK_DIR, "libraries", "AT32F43x_USB-FS-Device_Driver")) )

env.Prepend(LIBS=libs)
