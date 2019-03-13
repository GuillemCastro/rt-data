# rt-data

rt-data is a data acquisition framework for embedded systems.

## Build instructions

```
mkdir build && cd build
cmake ..
make
```

## Build instructions for cross compilation for ARMv7+ (armhf)

```
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE:PATH="..\toolchain.cmake"
make
```

## License

Copyright (C) 2019 Guillem Castro

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.
