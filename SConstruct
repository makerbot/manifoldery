import commands

# SConstruct file for manifoldery project.

env = Environment()

operating_system = commands.getoutput("uname")
if operating_system == "Linux":
	env.Append(CCFLAGS = '-DON_DARWIN')
if operating_system.find("_NT") > 0:
	env.Append(CCFLAGS = '-DON_WIN32')
if operating_system == "Darwin":
	env.Append(CCFLAGS = '-DON_DARWIN')



env.MergeFlags('-O3')

sources=[
	'main.cc',
	'Mesh.cc',
	'BinarySTL.cc',
	'AsciiSTL.cc'
]

env.Program('manifoldery',sources)

