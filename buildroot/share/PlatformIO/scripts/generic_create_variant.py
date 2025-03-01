#
# generic_create_variant.py
#
# Copy one of the variants from buildroot/platformio/variants into
# the appropriate framework variants folder, so that its contents
# will be picked up by PlatformIO just like any other variant.
#
import pioutil
if pioutil.is_pio_build():
<<<<<<< HEAD
	import shutil,marlin
	from pathlib import Path
=======
	import os,shutil,marlin
	from SCons.Script import DefaultEnvironment
	from platformio import util

	env = DefaultEnvironment()
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436

	#
	# Get the platform name from the 'platform_packages' option,
	# or look it up by the platform.class.name.
	#
<<<<<<< HEAD
	env = marlin.env
=======
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
	platform = env.PioPlatform()

	from platformio.package.meta import PackageSpec
	platform_packages = env.GetProjectOption('platform_packages')

	# Remove all tool items from platform_packages
	platform_packages = [x for x in platform_packages if not x.startswith("platformio/tool-")]

	if len(platform_packages) == 0:
		framewords = {
			"Ststm32Platform": "framework-arduinoststm32",
			"AtmelavrPlatform": "framework-arduino-avr"
		}
		platform_name = framewords[platform.__class__.__name__]
	else:
		platform_name = PackageSpec(platform_packages[0]).name

	if platform_name in [ "usb-host-msc", "usb-host-msc-cdc-msc", "usb-host-msc-cdc-msc-2", "usb-host-msc-cdc-msc-3", "tool-stm32duino", "biqu-bx-workaround", "main" ]:
		platform_name = "framework-arduinoststm32"

<<<<<<< HEAD
	FRAMEWORK_DIR = Path(platform.get_package_dir(platform_name))
	assert FRAMEWORK_DIR.is_dir()
=======
	FRAMEWORK_DIR = platform.get_package_dir(platform_name)
	assert os.path.isdir(FRAMEWORK_DIR)
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436

	board = env.BoardConfig()

	#mcu_type = board.get("build.mcu")[:-2]
	variant = board.get("build.variant")
	#series = mcu_type[:7].upper() + "xx"

	# Prepare a new empty folder at the destination
<<<<<<< HEAD
	variant_dir = FRAMEWORK_DIR / "variants" / variant
	if variant_dir.is_dir():
		shutil.rmtree(variant_dir)
	if not variant_dir.is_dir():
		variant_dir.mkdir()

	# Source dir is a local variant sub-folder
	source_dir = Path("buildroot/share/PlatformIO/variants", variant)
	assert source_dir.is_dir()
=======
	variant_dir = os.path.join(FRAMEWORK_DIR, "variants", variant)
	if os.path.isdir(variant_dir):
		shutil.rmtree(variant_dir)
	if not os.path.isdir(variant_dir):
		os.mkdir(variant_dir)

	# Source dir is a local variant sub-folder
	source_dir = os.path.join("buildroot/share/PlatformIO/variants", variant)
	assert os.path.isdir(source_dir)
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436

	marlin.copytree(source_dir, variant_dir)
