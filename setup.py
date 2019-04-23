#!/usr/bin/env python

"""Setup script for libais"""

import os
import sys

from setuptools import setup, find_packages, Extension

<<<<<<< HEAD
version = file('VERSION').readline().strip()

ais_module = Extension('ais',
                    sources = ['ais_py.cpp',
                               'ais.cpp',
                               'ais1_2_3.cpp', # Class A position
                               'ais4_11.cpp', # Basestation report, '=' - UTC time response
                               'ais5.cpp', # Static data report / ship name
                               'ais6.cpp', # Addressed binary message (ABM)
                               'ais7_13.cpp',
                               'ais8.cpp', # Broadcast binary message (BBM)
                               'ais8_001_22.cpp', # Area notice
                               'ais8_001_26.cpp', # Environmental Sensor Report
                               'ais8_200_10.cpp', # Inland ENCs
                               'ais8_366_22.cpp',
                               'ais9.cpp',
                               'ais10.cpp', # :
                               # 11 See 4 - ;
                               'ais12.cpp', # <
                               # 13 See 7 - =
                               'ais14.cpp', # >
                               'ais15.cpp', # ?
                               'ais16.cpp', # @
                               'ais17.cpp', # A
                               'ais18.cpp', # B
                               'ais19.cpp', # C
                               'ais20.cpp', # D
                               'ais21.cpp', # E
                               'ais22.cpp', # F
                               'ais23.cpp', # G
                               'ais24.cpp', # H
                               'ais25.cpp', # I - single slot binary message
                               'ais26.cpp', # J - Multi-slot binary message with comm-state
                               'ais27.cpp', # K - Long-range position
                               # 'ais28.cpp', # L - Not yet defined
                               ])

setup (name = 'libais',
       version = version,
       description = 'Automatic Identification System decoding - ship tracking',
       author='Kurt Schwehr',
       author_email='schwehr@gmail.com',
       url='https://github.com/schwehr/libais',
       license='LGPL v3+',
       ext_modules = [ais_module],
       classifiers=[
            'License :: OSI Approved :: GNU Lesser General Public License v3 or later (LGPLv3+)',
            'Topic :: System :: Networking',
            'Development Status :: 4 - Beta',
            'Intended Audience :: Science/Research',
            'Topic :: Communications',
            'Topic :: Scientific/Engineering :: Information Analysis',
            'Topic :: Scientific/Engineering :: Interface Engine/Protocol Translator',
            'Topic :: Scientific/Engineering :: GIS',
    ],
       )
=======

with open('README.rst') as f:
    readme = f.read()


with open(os.path.join('ais', '__init__.py')) as f:
  for line in f:
    if line.strip().startswith('__version__'):
      # Get version from line but leave as str: __version__ = "0.16" -> 0.16
      VERSION = line.split('=')[1].strip()[1:-1].strip()
      break

EXTRA_COMPILE_ARGS = []
if sys.platform in ('darwin', 'linux', 'linux2'):
  EXTRA_COMPILE_ARGS = ['-std=c++11']


AIS_MODULE = Extension(
  '_ais',
  extra_compile_args=EXTRA_COMPILE_ARGS,
  sources=[os.path.join('src', 'libais', fn) for fn in (
    'ais_py.cpp',
    'ais.cpp',
    'ais_bitset.cpp',
    'ais1_2_3.cpp',  # Class A position
    'ais4_11.cpp',  # Basestation report, '=' - UTC time response
    'ais5.cpp',  # Static data report / ship name
    'ais6.cpp',  # Addressed binary message (ABM)
    'ais7_13.cpp',
    'ais8.cpp',  # Broadcast binary message (BBM)
    'ais8_1_22.cpp',  # Area notice
    'ais8_1_26.cpp',  # Environmental Sensor Report
    'ais8_200.cpp',
    'ais8_366.cpp',
    'ais8_367.cpp',
    'ais9.cpp',
    'ais10.cpp',  # :
    # 11 See 4 - ;
    'ais12.cpp',  # <
    # 13 See 7 - =
    'ais14.cpp',  # >
    'ais15.cpp',  # ?
    'ais16.cpp',  # @
    'ais17.cpp',  # A
    'ais18.cpp',  # B
    'ais19.cpp',  # C
    'ais20.cpp',  # D
    'ais21.cpp',  # E
    'ais22.cpp',  # F
    'ais23.cpp',  # G
    'ais24.cpp',  # H
    'ais25.cpp',  # I - single slot binary message
    'ais26.cpp',  # J - Multi-slot binary message with comm-state
    'ais27.cpp',  # K - Long-range position
    #  'ais28.cpp', # L - Not yet defined
    )
  ]
)

tests_require = [
    'pytest',
    'pytest-cov',
    'pytest-runner',
]

setup(
  name='libais',
  version=VERSION,
  description='Automatic Identification System decoding - ship tracking',
  long_description=readme,
  author='Kurt Schwehr',
  author_email='schwehr@gmail.com',
  url='https://github.com/schwehr/libais',
  license='Apache 2.0',
  classifiers=[
    'License :: OSI Approved :: Apache Software License',
    'Development Status :: 4 - Beta',
    'Intended Audience :: Science/Research',
    'Operating System :: Android',
    'Operating System :: iOS',
    'Operating System :: POSIX',
    'Programming Language :: C++',
    'Programming Language :: Python :: 2.7',
    'Programming Language :: Python :: 3.4',
    'Programming Language :: Python :: Implementation :: CPython',
    'Topic :: Communications',
    'Topic :: Scientific/Engineering :: Information Analysis',
    'Topic :: System :: Networking',
    'Topic :: Scientific/Engineering :: GIS',
    'Topic :: Scientific/Engineering :: Interface Engine/Protocol Translator',
  ],

  platforms=["POSIX"],
  scripts=[os.path.join('bin', 'aisdecode')],
  entry_points={
    'console_scripts': [
      'libais_stats=ais.stats:main',
    ]
  },

  ext_modules=[AIS_MODULE],
  packages=find_packages(exclude=['test']),
  install_requires=['six'],
  extras_require={
      'tests': tests_require,
  },
  tests_require=tests_require,
  test_suite="test"
)
>>>>>>> e464cf8ccf4458bcc64fb763f906ee54eb0ce984
