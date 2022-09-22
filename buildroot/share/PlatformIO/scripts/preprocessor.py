#
# preprocessor.py
#
<<<<<<< HEAD
import subprocess,re
=======
import subprocess,os,re
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436

nocache = 1
verbose = 0

def blab(str):
	if verbose:
		print(str)

################################################################################
#
# Invoke GCC to run the preprocessor and extract enabled features
#
preprocessor_cache = {}
def run_preprocessor(env, fn=None):
	filename = fn or 'buildroot/share/PlatformIO/scripts/common-dependencies.h'
	if filename in preprocessor_cache:
		return preprocessor_cache[filename]

	# Process defines
	build_flags = env.get('BUILD_FLAGS')
	build_flags = env.ParseFlagsExtended(build_flags)

	cxx = search_compiler(env)
	cmd = ['"' + cxx + '"']

	# Build flags from board.json
	#if 'BOARD' in env:
	#	cmd += [env.BoardConfig().get("build.extra_flags")]
	for s in build_flags['CPPDEFINES']:
		if isinstance(s, tuple):
			cmd += ['-D' + s[0] + '=' + str(s[1])]
		else:
			cmd += ['-D' + s]

	cmd += ['-D__MARLIN_DEPS__ -w -dM -E -x c++']
	depcmd = cmd + [ filename ]
	cmd = ' '.join(depcmd)
	blab(cmd)
<<<<<<< HEAD
	try:
		define_list = subprocess.check_output(cmd, shell=True).splitlines()
	except:
		define_list = {}
=======
	define_list = subprocess.check_output(cmd, shell=True).splitlines()
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
	preprocessor_cache[filename] = define_list
	return define_list


################################################################################
#
# Find a compiler, considering the OS
#
def search_compiler(env):

<<<<<<< HEAD
	from pathlib import Path, PurePath

	ENV_BUILD_PATH = Path(env['PROJECT_BUILD_DIR'], env['PIOENV'])
	GCC_PATH_CACHE = ENV_BUILD_PATH / ".gcc_path"

	try:
		gccpath = env.GetProjectOption('custom_gcc')
		blab("Getting compiler from env")
		return gccpath
=======
	ENV_BUILD_PATH = os.path.join(env['PROJECT_BUILD_DIR'], env['PIOENV'])
	GCC_PATH_CACHE = os.path.join(ENV_BUILD_PATH, ".gcc_path")

	try:
		filepath = env.GetProjectOption('custom_gcc')
		blab("Getting compiler from env")
		return filepath
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
	except:
		pass

	# Warning: The cached .gcc_path will obscure a newly-installed toolkit
<<<<<<< HEAD
	if not nocache and GCC_PATH_CACHE.exists():
		blab("Getting g++ path from cache")
		return GCC_PATH_CACHE.read_text()

	# Use any item in $PATH corresponding to a platformio toolchain bin folder
	path_separator = ':'
	gcc_exe = '*g++'
	if env['PLATFORM'] == 'win32':
		path_separator = ';'
		gcc_exe += ".exe"

	# Search for the compiler in PATH
	for ppath in map(Path, env['ENV']['PATH'].split(path_separator)):
		if ppath.match(env['PROJECT_PACKAGES_DIR'] + "/**/bin"):
			for gpath in ppath.glob(gcc_exe):
				gccpath = str(gpath.resolve())
				# Cache the g++ path to no search always
				if not nocache and ENV_BUILD_PATH.exists():
					blab("Caching g++ for current env")
					GCC_PATH_CACHE.write_text(gccpath)
				return gccpath

	gccpath = env.get('CXX')
	blab("Couldn't find a compiler! Fallback to %s" % gccpath)
	return gccpath
=======
	if not nocache and os.path.exists(GCC_PATH_CACHE):
		blab("Getting g++ path from cache")
		with open(GCC_PATH_CACHE, 'r') as f:
			return f.read()

	# Find the current platform compiler by searching the $PATH
	# which will be in a platformio toolchain bin folder
	path_regex = re.escape(env['PROJECT_PACKAGES_DIR'])
	gcc = "g++"
	if env['PLATFORM'] == 'win32':
		path_separator = ';'
		path_regex += r'.*\\bin'
		gcc += ".exe"
	else:
		path_separator = ':'
		path_regex += r'/.+/bin'

	# Search for the compiler
	for pathdir in env['ENV']['PATH'].split(path_separator):
		if not re.search(path_regex, pathdir, re.IGNORECASE):
			continue
		for filepath in os.listdir(pathdir):
			if not filepath.endswith(gcc):
				continue
			# Use entire path to not rely on env PATH
			filepath = os.path.sep.join([pathdir, filepath])
			# Cache the g++ path to no search always
			if not nocache and os.path.exists(ENV_BUILD_PATH):
				blab("Caching g++ for current env")
				with open(GCC_PATH_CACHE, 'w+') as f:
					f.write(filepath)

			return filepath

	filepath = env.get('CXX')
	blab("Couldn't find a compiler! Fallback to %s" % filepath)
	return filepath
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
