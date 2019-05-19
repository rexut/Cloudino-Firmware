# See PlatformIO documentation "Advanced Scripting" at:
# https://docs.platformio.org/en/latest/projectconf/advanced_scripting.html

Import("env")

import os
import shutil
from base64 import b64decode

def after_build_copy_to_bin(source, target, env):
  if not os.path.exists("./bin"):
    os.mkdir("./bin")
  target_name = b64decode(ARGUMENTS.get("BOARD"))
  shutil.copy(target[0].path, "./bin/Cloudino_"+target_name.lower()+".bin")

env.AddPostAction("$BUILD_DIR/firmware.bin", after_build_copy_to_bin)