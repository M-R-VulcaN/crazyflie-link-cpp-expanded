# Crazyflie C++ Lib 

A library which you could include into your c++ project and run the functions in here to code yourself a program for the crazyflie. A c++ version of [crazyflie-lib-python](https://github.com/bitcraze/crazyflie-lib-python)

## Development

### Repo Structure

* `src` - source files for crazyflie lib classes and functions

* `examples` - example files which you can run

* `include` - contains all header files for crazyflie lib

### For Visual Studio Editting Best Experience

1. Install c/c++ add-on
2. Install CMakeLists add-on
3. Open Directory in Vscode
4. Allow intelisense for c/c++
5. Allow intelisense for CMakeLists (let the compiler guess which g++ version to use) 



## How to run

### Dependencies

```
sudo apt install -y libusb-1.0-0-dev
```

### Build C++ lib and examples

```
mkdir build
cd build
cmake ..
make
```

The library can be tested from the build directory using the example applications, e.g.,:

```
./example_scan
```
# IMPORTANT DATA SOURCES and REFERENCES 


*   [Bitcraze parameters documentation](https://www.bitcraze.io/documentation/repository/crazyflie-firmware/master/functional-areas/crtp/crtp_parameters/) 


*   parameter [TOC structure](https://github.com/bitcraze/crazyflie-lib-python/blob/master/cflib/crazyflie/toc.py)


*   [Bitcraze python lib](https://github.com/bitcraze/crazyflie-lib-python)


*   [How to properly setup usb of crazyflie in ubuntu](https://www.bitcraze.io/documentation/repository/crazyflie-lib-python/0.1.9/usb_permissions/)


# METHODS and ARCHITECTURE

Note: The difference between V2 and V1 is the use of 2 bytes instead of 1 to represent the ID of the param, increasing the potential size of the TOC by 256 times.


## Set Param Protocol Structure

**<span style="text-decoration:underline;">Set Param Value:</span>**

**Send:**


<table>
  <tr>
   <td>Byte #
   </td>
   <td>2
   </td>
   <td>sizeof(&lt;param type>)
   </td>
  </tr>
  <tr>
   <td>Value:
   </td>
   <td><strong>&lt;param id></strong>
   </td>
   <td><strong>&lt;param value></strong>
   </td>
  </tr>
  <tr>
   <td>Description:
   </td>
   <td>Param ID
   </td>
   <td>The value of the param
   </td>
  </tr>
</table>


**Receive:**


<table>
  <tr>
   <td>Byte #
   </td>
   <td>2
   </td>
   <td>sizeof(&lt;param type>)
   </td>
  </tr>
  <tr>
   <td>Value:
   </td>
   <td><strong>&lt;param id></strong>
   </td>
   <td><strong>&lt;new param value></strong>
   </td>
  </tr>
  <tr>
   <td>Description:
   </td>
   <td>Param ID
   </td>
   <td>The new value of the param
   </td>
  </tr>
</table>



## Read Param Protocol Structure

**<span style="text-decoration:underline;">Read Param Value:</span>**

**Send:**


<table>
  <tr>
   <td>Byte #
   </td>
   <td>2
   </td>
  </tr>
  <tr>
   <td>Value:
   </td>
   <td><strong>&lt;param id></strong>
   </td>
  </tr>
  <tr>
   <td>Description:
   </td>
   <td>Param ID
   </td>
  </tr>
</table>


**Receive:**


<table>
  <tr>
   <td>Byte #
   </td>
   <td>2
   </td>
   <td>sizeof(&lt;param type>)
   </td>
  </tr>
  <tr>
   <td>Value:
   </td>
   <td><strong>&lt;param id></strong>
   </td>
   <td><strong>&lt;param value></strong>
   </td>
  </tr>
  <tr>
   <td>Description:
   </td>
   <td>Param ID
   </td>
   <td>The value of the param
   </td>
  </tr>
</table>



## TOC Protocol Structure

**<span style="text-decoration:underline;">Get Toc Item V2:</span>**

**Send:**


<table>
  <tr>
   <td>Byte #
   </td>
   <td>1
   </td>
   <td>2
   </td>
  </tr>
  <tr>
   <td>Value:
   </td>
   <td><strong>2</strong>
   </td>
   <td><strong>&lt;param id></strong>
   </td>
  </tr>
  <tr>
   <td>Description:
   </td>
   <td>Command  Number
   </td>
   <td>Param ID
   </td>
  </tr>
</table>


**Receive:**


<table>
  <tr>
   <td>Byte #
   </td>
   <td>1
   </td>
   <td>2
   </td>
   <td>1
   </td>
   <td>strlen
   </td>
   <td>strlen
   </td>
  </tr>
  <tr>
   <td>Value:
   </td>
   <td><strong>2</strong>
   </td>
   <td><strong>&lt;param id></strong>
   </td>
   <td><strong>&lt;type code></strong>
   </td>
   <td><strong>&lt;group name string></strong>
   </td>
   <td><strong>&lt;param name string></strong>
   </td>
  </tr>
  <tr>
   <td>Description:
   </td>
   <td>Command #
   </td>
   <td>Param ID
   </td>
   <td>Param Type
   </td>
   <td>Group Name
   </td>
   <td>Param Name
   </td>
  </tr>
</table>


**<span style="text-decoration:underline;">Get Toc Info V2:</span>**

**Send:**


<table>
  <tr>
   <td>Byte #
   </td>
   <td>1
   </td>
  </tr>
  <tr>
   <td>Value:
   </td>
   <td><strong>3</strong>
   </td>
  </tr>
  <tr>
   <td>Description:
   </td>
   <td>Command  Number
   </td>
  </tr>
</table>


**Receive:**


<table>
  <tr>
   <td>Byte #
   </td>
   <td>1
   </td>
   <td>2
   </td>
   <td>4
   </td>
  </tr>
  <tr>
   <td>Value:
   </td>
   <td><strong>3</strong>
   </td>
   <td><strong>&lt;size></strong>
   </td>
   <td><strong>&lt;crc></strong>
   </td>
  </tr>
  <tr>
   <td>Description:
   </td>
   <td>Command #
   </td>
   <td>Number of elements in the Toc
   </td>
   <td>Current <a href="https://en.wikipedia.org/wiki/Cyclic_redundancy_check">Cyclic Redundancy Check</a> value
   </td>
  </tr>
</table>



