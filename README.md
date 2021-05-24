# Crazyflie C++ Link

## Overview

```
This project allow us to get parameter value from a specific parameter in a specific group.
(group.param)
```

## Dependencies

```
sudo apt install -y libusb-1.0-0-dev
```

This relies on pybind11, which is a submodule, so don't forget to

```
git submodule init 
git submodule update
```

## Build C++ lib 

```
mkdir build
cd build
cmake ..
make
```

now run the specific project

```
./example_basicParam
```
![Screenshot from 2021-05-24 14-09-58](https://user-images.githubusercontent.com/67019760/119339385-c1a89080-bc99-11eb-8293-3e178df3f756.png)
