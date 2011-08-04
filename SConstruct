
# SConstruct file for manifoldery project.

env = Environment()

env.MergeFlags('-O3')

sources=[
	'main.cc',
	'Mesh.cc',
	'STL.cc',
	'BinarySTL.cc',
	'AsciiSTL.cc'
]

env.Program('manifoldery',sources)

