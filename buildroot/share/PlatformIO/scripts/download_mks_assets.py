#
# download_mks_assets.py
# Added by HAS_TFT_LVGL_UI to download assets from Makerbase repo
#
import pioutil
if pioutil.is_pio_build():
	Import("env")
<<<<<<< HEAD
	import requests,zipfile,tempfile,shutil
	from pathlib import Path

	url = "https://github.com/makerbase-mks/Mks-Robin-Nano-Marlin2.0-Firmware/archive/0263cdaccf.zip"
	deps_path = Path(env.Dictionary("PROJECT_LIBDEPS_DIR"))
	zip_path = deps_path / "mks-assets.zip"
	assets_path = Path(env.Dictionary("PROJECT_BUILD_DIR"), env.Dictionary("PIOENV"), "assets")
=======
	import os,requests,zipfile,tempfile,shutil

	url = "https://github.com/makerbase-mks/Mks-Robin-Nano-Marlin2.0-Firmware/archive/0263cdaccf.zip"
	deps_path = env.Dictionary("PROJECT_LIBDEPS_DIR")
	zip_path = os.path.join(deps_path, "mks-assets.zip")
	assets_path = os.path.join(env.Dictionary("PROJECT_BUILD_DIR"), env.Dictionary("PIOENV"), "assets")
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436

	def download_mks_assets():
		print("Downloading MKS Assets")
		r = requests.get(url, stream=True)
		# the user may have a very clean workspace,
		# so create the PROJECT_LIBDEPS_DIR directory if not exits
<<<<<<< HEAD
		if not deps_path.exists():
			deps_path.mkdir()
		with zip_path.open('wb') as fd:
=======
		if os.path.exists(deps_path) == False:
			os.mkdir(deps_path)
		with open(zip_path, 'wb') as fd:
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
			for chunk in r.iter_content(chunk_size=128):
				fd.write(chunk)

	def copy_mks_assets():
		print("Copying MKS Assets")
<<<<<<< HEAD
		output_path = Path(tempfile.mkdtemp())
		zip_obj = zipfile.ZipFile(zip_path, 'r')
		zip_obj.extractall(output_path)
		zip_obj.close()
		if assets_path.exists() and not assets_path.is_dir():
			assets_path.unlink()
		if not assets_path.exists():
			assets_path.mkdir()
		base_path = ''
		for filename in output_path.iterdir():
			base_path = filename
		fw_path = (output_path / base_path / 'Firmware')
		font_path = fw_path / 'mks_font'
		for filename in font_path.iterdir():
			shutil.copy(font_path / filename, assets_path)
		pic_path = fw_path / 'mks_pic'
		for filename in pic_path.iterdir():
			shutil.copy(pic_path / filename, assets_path)
		shutil.rmtree(output_path, ignore_errors=True)

	if not zip_path.exists():
		download_mks_assets()

	if not assets_path.exists():
=======
		output_path = tempfile.mkdtemp()
		zip_obj = zipfile.ZipFile(zip_path, 'r')
		zip_obj.extractall(output_path)
		zip_obj.close()
		if os.path.exists(assets_path) == True and os.path.isdir(assets_path) == False:
			os.unlink(assets_path)
		if os.path.exists(assets_path) == False:
			os.mkdir(assets_path)
		base_path = ''
		for filename in os.listdir(output_path):
			base_path = filename
		for filename in os.listdir(os.path.join(output_path, base_path, 'Firmware', 'mks_font')):
			shutil.copy(os.path.join(output_path, base_path, 'Firmware', 'mks_font', filename), assets_path)
		for filename in os.listdir(os.path.join(output_path, base_path, 'Firmware', 'mks_pic')):
			shutil.copy(os.path.join(output_path, base_path, 'Firmware', 'mks_pic', filename), assets_path)
		shutil.rmtree(output_path, ignore_errors=True)

	if os.path.exists(zip_path) == False:
		download_mks_assets()

	if os.path.exists(assets_path) == False:
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
		copy_mks_assets()
