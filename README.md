# rt-data

[![Build Status](https://travis-ci.org/GuillemCastro/rt-data.svg?branch=master)](https://travis-ci.org/GuillemCastro/rt-data)
[![CII Best Practices](https://bestpractices.coreinfrastructure.org/projects/2944/badge)](https://bestpractices.coreinfrastructure.org/projects/2944)
[![ko-fi](https://www.ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/A0A8Y9TP)

rt-data is a data acquisition framework for embedded systems.

## Build instructions

```
mkdir build && cd build
cmake ..
make
```

## Build instructions with documentation

```
mkdir build && cd build
cmake .. -DBUILD_DOCS=ON
make
```

## Build instructions for cross compilation for ARMv7+ (armhf)

```
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE:PATH="..\toolchain.cmake"
make
```

## Dependencies

```
sudo apt install libcurl4-gnutls-dev gpsd libqgpsmm23 libqgpsmm-dev libgps libgps-dev
```

## License

rt-data is licensed under the **[GNU Lesser General Public License]**. The terms of the license are as follows: 


```
Copyright (C) 2019 Guillem Castro

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
```

[GNU Lesser General Public License]: https://github.com/GuillemCastro/rt-data/raw/master/LICENSE
