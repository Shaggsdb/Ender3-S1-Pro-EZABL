#
# pioutil.py
#

# Make sure 'vscode init' is not the current command
def is_pio_build():
<<<<<<< HEAD
	from SCons.Script import DefaultEnvironment
	env = DefaultEnvironment()
	return not env.IsIntegrationDump()

def get_pio_version():
	from platformio import util
	return util.pioversion_to_intstr()
=======
	from SCons.Script import COMMAND_LINE_TARGETS
	return "idedata" not in COMMAND_LINE_TARGETS and "_idedata" not in COMMAND_LINE_TARGETS
>>>>>>> af308590f4efa68068226d4f6b05924d56f02436
