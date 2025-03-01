#
# marlin.py
# Helper module with some commonly-used functions
#
<<<<<<< HEAD
import shutil
from pathlib import Path
=======
import os,shutil
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436

from SCons.Script import DefaultEnvironment
env = DefaultEnvironment()

<<<<<<< HEAD
def copytree(src, dst, symlinks=False, ignore=None):
	for item in src.iterdir():
		if item.is_dir():
			shutil.copytree(item, dst / item.name, symlinks, ignore)
		else:
			shutil.copy2(item, dst / item.name)
=======
from os.path import join

def copytree(src, dst, symlinks=False, ignore=None):
	for item in os.listdir(src):
		s = join(src, item)
		d = join(dst, item)
		if os.path.isdir(s):
			shutil.copytree(s, d, symlinks, ignore)
		else:
			shutil.copy2(s, d)
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436

def replace_define(field, value):
	for define in env['CPPDEFINES']:
		if define[0] == field:
			env['CPPDEFINES'].remove(define)
	env['CPPDEFINES'].append((field, value))

# Relocate the firmware to a new address, such as "0x08005000"
def relocate_firmware(address):
	replace_define("VECT_TAB_ADDR", address)

# Relocate the vector table with a new offset
def relocate_vtab(address):
	replace_define("VECT_TAB_OFFSET", address)

# Replace the existing -Wl,-T with the given ldscript path
def custom_ld_script(ldname):
<<<<<<< HEAD
	apath = str(Path("buildroot/share/PlatformIO/ldscripts", ldname).resolve())
=======
	apath = os.path.abspath("buildroot/share/PlatformIO/ldscripts/" + ldname)
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
	for i, flag in enumerate(env["LINKFLAGS"]):
		if "-Wl,-T" in flag:
			env["LINKFLAGS"][i] = "-Wl,-T" + apath
		elif flag == "-T":
			env["LINKFLAGS"][i + 1] = apath

# Encrypt ${PROGNAME}.bin and save it with a new name. This applies (mostly) to MKS boards
# This PostAction is set up by offset_and_rename.py for envs with 'build.encrypt_mks'.
def encrypt_mks(source, target, env, new_name):
	import sys

	key = [0xA3, 0xBD, 0xAD, 0x0D, 0x41, 0x11, 0xBB, 0x8D, 0xDC, 0x80, 0x2D, 0xD0, 0xD2, 0xC4, 0x9B, 0x1E, 0x26, 0xEB, 0xE3, 0x33, 0x4A, 0x15, 0xE4, 0x0A, 0xB3, 0xB1, 0x3C, 0x93, 0xBB, 0xAF, 0xF7, 0x3E]

	# If FIRMWARE_BIN is defined by config, override all
	mf = env["MARLIN_FEATURES"]
	if "FIRMWARE_BIN" in mf: new_name = mf["FIRMWARE_BIN"]

<<<<<<< HEAD
	fwpath = Path(target[0].path)
	fwfile = fwpath.open("rb")
	enfile = Path(target[0].dir.path, new_name).open("wb")
	length = fwpath.stat().st_size
=======
	fwpath = target[0].path
	fwfile = open(fwpath, "rb")
	enfile = open(target[0].dir.path + "/" + new_name, "wb")
	length = os.path.getsize(fwpath)
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
	position = 0
	try:
		while position < length:
			byte = fwfile.read(1)
<<<<<<< HEAD
			if 320 <= position < 31040:
=======
			if position >= 320 and position < 31040:
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
				byte = chr(ord(byte) ^ key[position & 31])
				if sys.version_info[0] > 2:
					byte = bytes(byte, 'latin1')
			enfile.write(byte)
			position += 1
	finally:
		fwfile.close()
		enfile.close()
<<<<<<< HEAD
		fwpath.unlink()

def add_post_action(action):
	env.AddPostAction(str(Path("$BUILD_DIR", "${PROGNAME}.bin")), action);
=======
		os.remove(fwpath)

def add_post_action(action):
	env.AddPostAction(join("$BUILD_DIR", "${PROGNAME}.bin"), action);
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
