#
# preflight-checks.py
# Check for common issues prior to compiling
#
import pioutil
if pioutil.is_pio_build():

	import os,re,sys
<<<<<<< HEAD
	from pathlib import Path
	Import("env")

	def get_envs_for_board(board):
		ppath = Path("Marlin/src/pins/pins.h")
		with ppath.open() as file:
=======
	Import("env")

	def get_envs_for_board(board):
		with open(os.path.join("Marlin", "src", "pins", "pins.h"), "r") as file:
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436

			if sys.platform == 'win32':
				envregex = r"(?:env|win):"
			elif sys.platform == 'darwin':
				envregex = r"(?:env|mac|uni):"
			elif sys.platform == 'linux':
				envregex = r"(?:env|lin|uni):"
			else:
				envregex = r"(?:env):"

			r = re.compile(r"if\s+MB\((.+)\)")
			if board.startswith("BOARD_"):
				board = board[6:]

			for line in file:
				mbs = r.findall(line)
				if mbs and board in re.split(r",\s*", mbs[0]):
					line = file.readline()
					found_envs = re.match(r"\s*#include .+" + envregex, line)
					if found_envs:
						envlist = re.findall(envregex + r"(\w+)", line)
						return [ "env:"+s for s in envlist ]
		return []

	def check_envs(build_env, board_envs, config):
		if build_env in board_envs:
			return True
		ext = config.get(build_env, 'extends', default=None)
		if ext:
			if isinstance(ext, str):
				return check_envs(ext, board_envs, config)
			elif isinstance(ext, list):
				for ext_env in ext:
					if check_envs(ext_env, board_envs, config):
						return True
		return False

	def sanity_check_target():
		# Sanity checks:
		if 'PIOENV' not in env:
			raise SystemExit("Error: PIOENV is not defined. This script is intended to be used with PlatformIO")

<<<<<<< HEAD
		# Require PlatformIO 6.1.1 or later
		vers = pioutil.get_pio_version()
		if vers < [6, 1, 1]:
			raise SystemExit("Error: Marlin requires PlatformIO >= 6.1.1. Use 'pio upgrade' to get a newer version.")

=======
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
		if 'MARLIN_FEATURES' not in env:
			raise SystemExit("Error: this script should be used after common Marlin scripts")

		if 'MOTHERBOARD' not in env['MARLIN_FEATURES']:
			raise SystemExit("Error: MOTHERBOARD is not defined in Configuration.h")

		build_env = env['PIOENV']
		motherboard = env['MARLIN_FEATURES']['MOTHERBOARD']
		board_envs = get_envs_for_board(motherboard)
		config = env.GetProjectConfig()
		result = check_envs("env:"+build_env, board_envs, config)

		if not result:
			err = "Error: Build environment '%s' is incompatible with %s. Use one of these: %s" % \
				  ( build_env, motherboard, ", ".join([ e[4:] for e in board_envs if e.startswith("env:") ]) )
			raise SystemExit(err)

		#
		# Check for Config files in two common incorrect places
		#
<<<<<<< HEAD
		epath = Path(env['PROJECT_DIR'])
		for p in [ epath, epath / "config" ]:
			for f in ("Configuration.h", "Configuration_adv.h"):
				if (p / f).is_file():
=======
		for p in [ env['PROJECT_DIR'], os.path.join(env['PROJECT_DIR'], "config") ]:
			for f in [ "Configuration.h", "Configuration_adv.h" ]:
				if os.path.isfile(os.path.join(p, f)):
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
					err = "ERROR: Config files found in directory %s. Please move them into the Marlin subfolder." % p
					raise SystemExit(err)

		#
<<<<<<< HEAD
		# Find the name.cpp.o or name.o and remove it
		#
		def rm_ofile(subdir, name):
			build_dir = Path(env['PROJECT_BUILD_DIR'], build_env);
			for outdir in (build_dir, build_dir / "debug"):
				for ext in (".cpp.o", ".o"):
					fpath = outdir / "src/src" / subdir / (name + ext)
					if fpath.exists():
						fpath.unlink()

		#
		# Give warnings on every build
		#
		rm_ofile("inc", "Warnings")
=======
		# Give warnings on every build
		#
		srcpath = os.path.join(env['PROJECT_BUILD_DIR'], build_env, "src", "src")
		warnfile = os.path.join(srcpath, "inc", "Warnings.cpp.o")
		if os.path.exists(warnfile):
			os.remove(warnfile)
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436

		#
		# Rebuild 'settings.cpp' for EEPROM_INIT_NOW
		#
		if 'EEPROM_INIT_NOW' in env['MARLIN_FEATURES']:
<<<<<<< HEAD
			rm_ofile("module", "settings")
=======
			setfile = os.path.join(srcpath, "module", "settings.cpp.o")
			if os.path.exists(setfile):
				os.remove(setfile)
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436

		#
		# Check for old files indicating an entangled Marlin (mixing old and new code)
		#
		mixedin = []
<<<<<<< HEAD
		p = Path(env['PROJECT_DIR'], "Marlin/src/lcd/dogm")
		for f in [ "ultralcd_DOGM.cpp", "ultralcd_DOGM.h" ]:
			if (p / f).is_file():
				mixedin += [ f ]
		p = Path(env['PROJECT_DIR'], "Marlin/src/feature/bedlevel/abl")
		for f in [ "abl.cpp", "abl.h" ]:
			if (p / f).is_file():
=======
		p = os.path.join(env['PROJECT_DIR'], "Marlin", "src", "lcd", "dogm")
		for f in [ "ultralcd_DOGM.cpp", "ultralcd_DOGM.h" ]:
			if os.path.isfile(os.path.join(p, f)):
				mixedin += [ f ]
		p = os.path.join(env['PROJECT_DIR'], "Marlin", "src", "feature", "bedlevel", "abl")
		for f in [ "abl.cpp", "abl.h" ]:
			if os.path.isfile(os.path.join(p, f)):
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
				mixedin += [ f ]
		if mixedin:
			err = "ERROR: Old files fell into your Marlin folder. Remove %s and try again" % ", ".join(mixedin)
			raise SystemExit(err)

	sanity_check_target()
