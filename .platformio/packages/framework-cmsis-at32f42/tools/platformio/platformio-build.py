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

FRAMEWORK_DIR = platform.get_package_dir("framework-cmsis-at32f42")
CMSIS_DIR = join(platform.get_package_dir("framework-cmsis"), "CMSIS")
assert isdir(FRAMEWORK_DIR)
assert isdir(CMSIS_DIR)

def process_optimization_level(cpp_defines):
    if "OPTIMIZATION_FAST" in cpp_defines:
        env.Append(CCFLAGS=["-O1"])
    elif "OPTIMIZATION_FASTER" in cpp_defines:
        env.Append(CCFLAGS=["-O2"])
    elif "OPTIMIZATION_FASTEST" in cpp_defines:
        env.Append(CCFLAGS=["-O3"])
    else:
        env.Append(CCFLAGS=["-Os"])  # default optimize for size


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
        "-O1",  # optimize for speed O1, CANNOT USE O2 or O3, some bug in code don't allow it
        "-flto", #remove unused code
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
        join(FRAMEWORK_DIR, "libraries", "AT32F42x_StdPeriph_Driver", "include"),      
        join(FRAMEWORK_DIR, "libraries", "AT32F42x_USB-Device_Driver", "include"),  
        join(FRAMEWORK_DIR, "libraries", "AT32F425_board"),      
    ],
    LIBS=[
        "c",
        "m",
        "gcc",
        "stdc++",
    ],
    LIBPATH=[join(CMSIS_DIR, "DSP", "Lib", "GCC")],
)



# copy CCFLAGS to ASFLAGS (-x assembler-with-cpp mode)
env.Append(ASFLAGS=env.get("CCFLAGS", [])[:])

cpp_defines = env.Flatten(env.get("CPPDEFINES", []))
#process_optimization_level(cpp_defines)
#
# Target: Build Core Library
#


libs = []

libs.append(env.BuildLibrary(
        join("$BUILD_DIR", "AT32F42x_StdPeriph"), join(FRAMEWORK_DIR, "libraries", "AT32F42x_StdPeriph_Driver")
    ))
libs.append(env.BuildLibrary(
        join("$BUILD_DIR", "AT32F42x_USB-Device"), join(FRAMEWORK_DIR, "libraries", "AT32F42x_USB-Device_Driver")
    ))
libs.append(env.BuildLibrary(
        join("$BUILD_DIR", "AT32F425_board"), join(FRAMEWORK_DIR, "libraries", "AT32F425_board")
    ))


env.Prepend(LIBS=libs)
