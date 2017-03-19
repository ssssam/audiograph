project('audiograph', 'c')

cairo = dependency('cairo')
sndfile = dependency('sndfile')

math = meson.get_compiler('c').find_library('m')

sources = ['graph.c', 'wav.c']

audiograph = library('audiograph',
    sources,
    dependencies: [cairo, math, sndfile])

cli = executable('audiograph-cli',
    'audiograph.c',
    link_with: audiograph,
    dependencies: [cairo, math, sndfile])
