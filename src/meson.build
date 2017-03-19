sources = ['graph.c', 'wav.c']

audiograph = library('audiograph',
    sources,
    dependencies: [cairo, math, sndfile])

cli = executable('audiograph-cli',
    'cli.c',
    link_with: audiograph,
    dependencies: [cairo, math, sndfile])
