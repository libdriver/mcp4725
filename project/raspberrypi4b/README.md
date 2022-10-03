### 1. Chip

#### 1.1 Chip Info

chip name : Raspberry Pi 4B.

iic pin: SCL/SDA GPIO3/GPIO2.

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

​          mcp4725 is a basic command which can test all mcp4725 driver function:

​           -i        show mcp4725 chip and driver information.

​           -h       show mcp4725 help.

​           -p       show mcp4725 pin connections of the current board.

​           -t (reg -a (VCC | GND) | write <dac> -a (VCC | GND))

​           -t reg -a (VCC | GND)        run mcp4725 register test.

​           -t write <dac> -a (VCC | GND)         run mcp4725 write test. dac means dac value.

​           -c write <dac> -a  (VCC | GND)         run mcp4725 write function. dac means dac value.

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
./mcp4725 -t reg -a GND

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
mcp4725: check reference voltage ok.
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
./mcp4725 -t write 3 -a GND

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
mcp4725: dac read check ok write 0.3581v
mcp4725: dac read check ok write 1.0248v
mcp4725: dac read check ok write 1.4834v
mcp4725: set eeprom mode.
mcp4725: eeprom read check ok write 2.2657v
mcp4725: eeprom read check ok write 0.2117v
mcp4725: eeprom read check ok write 0.9174v
mcp4725: finish write test.
```

```shell
./mcp4725 -c write 1.2 -a GND

mcp4725: write 1.200.
```

```shell
./mcp4725 -h

mcp4725 -i
	show mcp4725 chip and driver information.
mcp4725 -h
	show mcp4725 help.
mcp4725 -p
	show mcp4725 pin connections of the current board.
mcp4725 -t reg -a (VCC | GND)
	run mcp4725 register test.
mcp4725 -t write <dac> -a (VCC | GND)
	run mcp4725 write test.dac means dac value.
mcp4725 -c write <dac> -a (VCC | GND)
	run mcp4725 write function.dac means dac value.
```

