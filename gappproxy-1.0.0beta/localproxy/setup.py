#! /usr/bin/env python
# coding=utf-8
#############################################################################
#                                                                           #
#   File: setup.py                                                          #
#                                                                           #
#   Copyright (C) 2008 Du XiaoGang <dugang@188.com>                         #
#                                                                           #
#   Home: http://gappproxy.googlecode.com                                   #
#                                                                           #
#   This file is part of GAppProxy.                                         #
#                                                                           #
#   GAppProxy is free software: you can redistribute it and/or modify       #
#   it under the terms of the GNU General Public License as                 #
#   published by the Free Software Foundation, either version 3 of the      #
#   License, or (at your option) any later version.                         #
#                                                                           #
#   GAppProxy is distributed in the hope that it will be useful,            #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of          #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           #
#   GNU General Public License for more details.                            #
#                                                                           #
#   You should have received a copy of the GNU General Public License       #
#   along with GAppProxy.  If not, see <http://www.gnu.org/licenses/>.      #
#                                                                           #
#############################################################################

from distutils.core import setup
import py2exe
import datetime, glob

now = datetime.datetime.now();

setup(
    options = {"py2exe": 
        { "optimize": 2,
          "compressed": 1,
          "bundle_files": 1
        }
    },

    name = "GAppProxy",
    version = "%d.%d.%d" % (now.year, now.month, now.day),
    description = "HTTP Proxy. 127.0.0.1:8000",

    zipfile = None,
    windows=['proxy.py', 'gui.pyw'],
    
    data_files = [
        ('images', ['images/gap.png']),
        ('service', glob.glob('service/*')),
        ('ssl', glob.glob('ssl/*'))
    ]
)

#python -OO setup.py py2exe --dist-dir GAppProxy --include sip && del GAppProxy\w9xpopen.exe
