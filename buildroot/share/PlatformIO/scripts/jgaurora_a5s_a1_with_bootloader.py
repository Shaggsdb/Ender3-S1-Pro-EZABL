#
# jgaurora_a5s_a1_with_bootloader.py
# Customizations for env:jgaurora_a5s_a1
#
import pioutil
if pioutil.is_pio_build():
<<<<<<< HEAD

	# Append ${PROGNAME}.bin firmware after bootloader and save it as 'jgaurora_firmware.bin'
	def addboot(source, target, env):
		from pathlib import Path

		fw_path = Path(target[0].path)
		fwb_path = fw_path.parent / 'firmware_with_bootloader.bin'
		with fwb_path.open("wb") as fwb_file:
			bl_path = Path("buildroot/share/PlatformIO/scripts/jgaurora_bootloader.bin")
			bl_file = bl_path.open("rb")
			while True:
				b = bl_file.read(1)
				if b == b'': break
				else: fwb_file.write(b)

			with fw_path.open("rb") as fw_file:
				while True:
					b = fw_file.read(1)
					if b == b'': break
					else: fwb_file.write(b)

		fws_path = Path(target[0].dir.path, 'firmware_for_sd_upload.bin')
		if fws_path.exists():
			fws_path.unlink()

		fw_path.rename(fws_path)

	import marlin
=======
	import os,marlin
	# Append ${PROGNAME}.bin firmware after bootloader and save it as 'jgaurora_firmware.bin'
	def addboot(source, target, env):
		firmware = open(target[0].path, "rb")
		lengthfirmware = os.path.getsize(target[0].path)
		bootloader_bin = "buildroot/share/PlatformIO/scripts/" + "jgaurora_bootloader.bin"
		bootloader = open(bootloader_bin, "rb")
		lengthbootloader = os.path.getsize(bootloader_bin)

		firmware_with_boothloader_bin = target[0].dir.path + '/firmware_with_bootloader.bin'
		if os.path.exists(firmware_with_boothloader_bin):
			os.remove(firmware_with_boothloader_bin)
		firmwareimage = open(firmware_with_boothloader_bin, "wb")
		position = 0
		while position < lengthbootloader:
			byte = bootloader.read(1)
			firmwareimage.write(byte)
			position += 1
		position = 0
		while position < lengthfirmware:
			byte = firmware.read(1)
			firmwareimage.write(byte)
			position += 1
		bootloader.close()
		firmware.close()
		firmwareimage.close()

		firmware_without_bootloader_bin = target[0].dir.path + '/firmware_for_sd_upload.bin'
		if os.path.exists(firmware_without_bootloader_bin):
			os.remove(firmware_without_bootloader_bin)
		os.rename(target[0].path, firmware_without_bootloader_bin)
		#os.rename(target[0].dir.path+'/firmware_with_bootloader.bin', target[0].dir.path+'/firmware.bin')

>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
	marlin.add_post_action(addboot);
