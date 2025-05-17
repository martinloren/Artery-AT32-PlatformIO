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

#
# Default flags for bare-metal programming (without any framework layers)
#

from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()

env.Append(
    ASFLAGS=["-x", "assembler-with-cpp"],

    CCFLAGS=[
        "-O3",  # optimize for size
        "-ffunction-sections",  # place each function in its own section
        "-fdata-sections",
        "-Wall",
        "-mthumb"
    ],

    CXXFLAGS=[
        "-fno-rtti",
        "-fno-exceptions",
    ],

    CPPDEFINES=[
        ("F_CPU", "$BOARD_F_CPU")
    ],

    LINKFLAGS=[
        "-O3",
        "-Wl,--gc-sections,--relax",
        "-mthumb",
    ],

    LIBS=["c", "gcc", "m", "stdc++"]
)

#Floating point unit: hard (hardware) | softfp (software)

#if (
#    any(cpu in board_config.get("build.cpu") for cpu in ("cortex-m4"))
#):
#    env.Append(
#        CFLAGS=["-mfpu=fpv4-sp-d16", "-mfloat-abi=hard"],
#        CCFLAGS=["-mfpu=fpv4-sp-d16", "-mfloat-abi=hard"],
#        LINKFLAGS=["-mfpu=fpv4-sp-d16", "-mfloat-abi=hard", "-u _printf_float"],
#    )

if "BOARD" in env:
    env.Append(
        CCFLAGS=[
            "-mcpu=%s" % env.BoardConfig().get("build.cpu")
        ],
        LINKFLAGS=[
            "-mcpu=%s" % env.BoardConfig().get("build.cpu")
        ]
    )

# copy CCFLAGS to ASFLAGS (-x assembler-with-cpp mode)
env.Append(ASFLAGS=env.get("CCFLAGS", [])[:])
