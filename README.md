# Using CMake with gcov

After cloning this directory, an "out-of-source build" is recommended to
test the project. To perform an out-of-source build, run the following commands
from the project root directory:

```
mkdir build
cd build
cmake ..
```

From the build directory you may build the project using `make`. The coverage
files from gcov can be generated using `make gcov`. A summary of the two source
files will be output and stored in `build/coverage/TestHello.tmp`. Running
`make clean` will remove the enitre coverage directory.

## lcov

``` bash
lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info '/usr/*' "${HOME}"'/.cache/*' '*tests/*' --output-file coverage.info
genhtml coverage.info --output-directory result
```


## Credits
- From the [Blog](https://github.com/jhbell/cmake-gcov) of Jeffrey H. Bell and his [GitHub Repository](https://jhbell.com/using-cmake-and-gcov).
- From [coverage.yml](https://github.com/ipc-sim/ipc-toolkit/blob/main/.github/workflows/coverage.yml).
