### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(mcp4725 REQUIRED)
```

### 3. MCP4725

#### 3.1 Command Instruction

1. Show mcp4725 chip and driver information.

   ```shell
   mcp4725 (-i | --information)
   ```

2. Show mcp4725 help.

   ```shell
   mcp4725 (-h | --help)
   ```

3. Show mcp4725 pin connections of the current board.

   ```shell
   mcp4725 (-p | --port)
   ```

4. Run mcp4725 register test.

   ```shell
   mcp4725 (-t reg | --test=reg) [--addr=<0 | 1>]
   ```

5. Run mcp4725 write test, num means the test times.

   ```shell
   mcp4725 (-t write | --test=write) [--addr=<0 | 1>] [--times=<num>]
   ```

6. Run mcp4725 write function, voltage means the dac value.

   ```shell
   mcp4725 (-e write | --example=write) [--addr=<0 | 1>] --dac=<voltage>
   ```

#### 3.2 Command Example

```shell
./mcp4725 -i

mcp4725: chip is Microchip MCP4725.
mcp4725: manufacturer is Microchip.
mcp4725: interface is IIC.
mcp4725: driver version is 2.0.
mcp4725: min supply voltage is 2.7V.
mcp4725: max supply voltage is 5.5V.
mcp4725: max current is 0.40mA.
mcp4725: max temperature is 125.0C.
mcp4725: min temperature is -40.0C.
```

```shell
./mcp4725 -p

mcp4725: SCL connected to GPIO3(BCM).
mcp4725: SDA connected to GPIO2(BCM).
```

```shell
./mcp4725 -t reg --addr=0

mcp4725: chip is Microchip MCP4725.
mcp4725: manufacturer is Microchip.
mcp4725: interface is IIC.
mcp4725: driver version is 2.0.
mcp4725: min supply voltage is 2.7V.
mcp4725: max supply voltage is 5.5V.
mcp4725: max current is 0.40mA.
mcp4725: max temperature is 125.0C.
mcp4725: min temperature is -40.0C.
mcp4725: start register test.
mcp4725: mcp4725_set_addr_pin/mcp4725_get_addr_pin test.
mcp4725: set addr pin A0_GND.
mcp4725: check addr pin ok.
mcp4725: set addr pin A0_VCC.
mcp4725: check addr pin ok.
mcp4725: mcp4725_set_reference_voltage/mcp4725_get_reference_voltage test.
mcp4725: set reference voltage 3.3v.
mcp4725: check reference voltage ok .
mcp4725: mcp4725_set_mode/mcp4725_get_mode test.
mcp4725: set dac mode.
mcp4725: check mode ok.
mcp4725: set eeprom mode.
mcp4725: check mode ok.
mcp4725: mcp4725_set_power_mode/mcp4725_get_power_mode test.
mcp4725: set normal power down.
mcp4725: check power mode ok.
mcp4725: set 1K power down.
mcp4725: check power mode ok.
mcp4725: set 100K power down.
mcp4725: check power mode ok.
mcp4725: set 500K power down.
mcp4725: check power mode ok.
mcp4725: finish register test.
```

```shell
./mcp4725 -t write --addr=0 --times=3

mcp4725: chip is Microchip MCP4725.
mcp4725: manufacturer is Microchip.
mcp4725: interface is IIC.
mcp4725: driver version is 2.0.
mcp4725: min supply voltage is 2.7V.
mcp4725: max supply voltage is 5.5V.
mcp4725: max current is 0.40mA.
mcp4725: max temperature is 125.0C.
mcp4725: min temperature is -40.0C.
mcp4725: start write test.
mcp4725: set dac mode.
mcp4725: dac read check ok write 0.8946v
mcp4725: dac read check ok write 0.4611v
mcp4725: dac read check ok write 1.9647v
mcp4725: set eeprom mode.
mcp4725: eeprom read check ok write 0.9339v
mcp4725: eeprom read check ok write 2.8400v
mcp4725: eeprom read check ok write 1.1988v
mcp4725: finish write test.
```

```shell
./mcp4725 -e write --addr=0 --dac=1.2

mcp4725: write 1.200.
```

```shell
./mcp4725 -h

Usage:
  mcp4725 (-i | --information)
  mcp4725 (-h | --help)
  mcp4725 (-p | --port)
  mcp4725 (-t reg | --test=reg) [--addr=<0 | 1>]
  mcp4725 (-t write | --test=write) [--addr=<0 | 1>] [--times=<num>]
  mcp4725 (-e write | --example=write) [--addr=<0 | 1>] --dac=<voltage>

Options:
      --addr=<0 | 1>               Set the addr pin.([default: 0])
      --dac=<voltage>              Set the dac output in voltage.
  -e <write>, --example=<write>    Run the driver example.
  -h, --help                       Show the help.
  -i, --information                Show the chip information.
  -p, --port                       Display the pin connections of the current board.
  -t <reg | write>, --test=<reg | write>
                                   Run the driver test.
      --times=<num>                Set the running times.([default: 3])
```

