EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 9650 5200 0    50   Italic 10
A0
Text Label 9650 5100 0    50   Italic 10
A1
Text Label 9650 5000 0    50   Italic 10
A2
Text Label 9700 3550 0    50   Italic 10
A4
Text Label 9700 3450 0    50   Italic 10
A5
Text Label 5750 2900 2    50   Italic 10
D0'
Text Label 5750 3000 2    50   Italic 10
D1'
Text Label 5750 3200 2    50   Italic 10
D2'
Text Label 5750 3300 2    50   Italic 10
D3'
Text Label 5750 3400 2    50   Italic 10
D4'
Text Label 7150 3500 0    50   Italic 10
OUT_0
Text Label 7150 3400 0    50   Italic 10
OUT_1
Text Label 7150 3300 0    50   Italic 10
OUT_2
Text Label 7150 3200 0    50   Italic 10
OUT_3
Text Label 7150 2700 0    50   Italic 10
AXIS_Y
Text Label 8650 5000 2    50   Italic 10
A2'
Text Label 8650 4900 2    50   Italic 10
A3'
Text Label 8650 5200 2    50   Italic 10
A0'
Text Label 8650 5100 2    50   Italic 10
A1'
Text Label 5050 4400 0    50   Italic 10
MEMR_EN
Text Notes 3100 2050 0    63   Italic 13
Conversão de nível do DataBus\n
Text Label 3600 2500 2    50   Italic 10
D0'
Text Label 3600 2600 2    50   Italic 10
D1'
Text Label 3600 2900 2    50   Italic 10
D4'
Text Label 3600 3100 2    50   Italic 10
D6'
Text Label 3600 3200 2    50   Italic 10
D7'
Text Label 3600 3000 2    50   Italic 10
D5'
$Comp
L GERAL:TXS0108E U1
U 1 1 6AC1B95B
P 3900 2450
F 0 "U1" H 3900 2765 50  0000 C CNN
F 1 "TXS0108E" H 3900 2674 50  0000 C CNN
F 2 "GERAL:standard_DIP_10pins_doubleBody" H 3900 2700 50  0001 C CNN
F 3 "" H 3900 2700 50  0001 C CNN
	1    3900 2450
	1    0    0    -1  
$EndComp
Text Label 3600 3300 2    50   Italic 10
VCC_3.3v
Text Label 4200 3300 0    50   Italic 10
VCC_5v
Text Label 4200 2500 0    50   Italic 10
D0
Text Label 4200 2600 0    50   Italic 10
D1
Text Label 4200 2700 0    50   Italic 10
D2
Text Label 4200 2800 0    50   Italic 10
D3
Text Label 4200 2900 0    50   Italic 10
D4
Text Label 4200 3100 0    50   Italic 10
D6
Text Label 4200 3200 0    50   Italic 10
D7
Text Label 4200 3000 0    50   Italic 10
D5
Text Label 3600 2400 2    50   Italic 10
DATABUS_OE
Text Label 5750 2800 2    50   Italic 10
DATABUS_OE
Text Notes 8000 3413 2    63   Italic 13
Écrã+SD\n
Text Notes 7513 3200 3    63   Italic 13
--^---
Text Notes 11150 2450 0    63   Italic 13
Conversão de nível do AddressBus\n
$Comp
L power:GNDREF #PWR014
U 1 1 6AC3DD21
P 9200 3950
F 0 "#PWR014" H 9200 3700 50  0001 C CNN
F 1 "GNDREF" H 9205 3777 50  0001 C CNN
F 2 "" H 9200 3950 50  0001 C CNN
F 3 "" H 9200 3950 50  0001 C CNN
	1    9200 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR03
U 1 1 6AC426C3
P 4450 2400
F 0 "#PWR03" H 4450 2150 50  0001 C CNN
F 1 "GNDREF" H 4455 2227 50  0001 C CNN
F 2 "" H 4450 2400 50  0001 C CNN
F 3 "" H 4450 2400 50  0001 C CNN
	1    4450 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR02
U 1 1 6AC43368
P 3900 5300
F 0 "#PWR02" H 3900 5050 50  0001 C CNN
F 1 "GNDREF" H 3905 5127 50  0001 C CNN
F 2 "" H 3900 5300 50  0001 C CNN
F 3 "" H 3900 5300 50  0001 C CNN
	1    3900 5300
	1    0    0    -1  
$EndComp
Text Label 9150 5500 0    50   Italic 10
VCC_5v
$Comp
L power:GNDREF #PWR07
U 1 1 6AC459A1
P 6350 2600
F 0 "#PWR07" H 6350 2350 50  0001 C CNN
F 1 "GNDREF" H 6355 2427 50  0001 C CNN
F 2 "" H 6350 2600 50  0001 C CNN
F 3 "" H 6350 2600 50  0001 C CNN
	1    6350 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 2100 6250 2100
Wire Wire Line
	6250 2100 6250 2600
Wire Wire Line
	5750 2600 6250 2600
Wire Wire Line
	6250 2600 6250 3100
Wire Wire Line
	6250 3100 5750 3100
Connection ~ 6250 2600
Wire Wire Line
	6250 3100 6250 3600
Wire Wire Line
	6250 3600 5750 3600
Connection ~ 6250 3100
Wire Wire Line
	6250 3600 7150 3600
Connection ~ 6250 3600
Wire Wire Line
	6250 3100 7150 3100
Wire Wire Line
	7150 2600 6350 2600
Wire Wire Line
	6250 2100 7150 2100
Connection ~ 6250 2100
Text Label 5750 3800 2    50   Italic 10
D7'
Text Notes 5550 3800 1    63   Italic 13
-----^------
Text Label 5750 3500 2    50   Italic 10
D5'
Text Label 5750 3700 2    50   Italic 10
D6'
Text Notes 5000 3400 0    63   Italic 13
DataBus
Connection ~ 6350 2600
Wire Wire Line
	6350 2600 6250 2600
$Comp
L MCU_RaspberryPi_and_Boards:Pico U3
U 1 1 6AB96C0E
P 6450 2850
F 0 "U3" H 6450 4065 50  0000 C CNN
F 1 "Pico" H 6450 3974 50  0000 C CNN
F 2 "pico:RPi_Pico_SMD_THT" V 6450 2850 50  0001 C CNN
F 3 "" H 6450 2850 50  0001 C CNN
	1    6450 2850
	1    0    0    -1  
$EndComp
Text Label 7150 3800 0    50   Italic 10
MEMW_EN'
Text Label 7150 2300 0    50   Italic 10
VCC_3.3v
Text Notes 7100 6350 0    63   Italic 13
Mutiplexagem do SD/ECRÃ\n
Text Label 8550 6550 2    50   Italic 10
OUT_0
Text Label 8550 6750 2    50   Italic 10
OUT_2
Text Label 8550 6950 2    50   Italic 10
OUT_0
Text Label 8550 7050 2    50   Italic 10
OUT_1
Text Label 8550 7150 2    50   Italic 10
OUT_2
Text Label 8550 7250 2    50   Italic 10
OUT_3
Text Label 8550 7450 2    50   Italic 10
ENABLE_SD
Text Label 8550 7550 2    50   Italic 10
~ENABLE_SD
$Comp
L 74xx:74HCT04 U7
U 1 1 6AC06B61
P 8850 8300
F 0 "U7" H 9000 8550 50  0000 C CNN
F 1 "74HCT04" H 9100 8450 50  0000 C CNN
F 2 "GERAL:standard_DIP_14OvalPins" H 8850 8300 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT04.pdf" H 8850 8300 50  0001 C CNN
	1    8850 8300
	1    0    0    -1  
$EndComp
Text Label 8550 8300 2    50   Italic 10
ENABLE_SD
Text Label 9300 8600 0    50   Italic 10
~ENABLE_SD
Text Label 9050 6250 2    50   Italic 10
VCC_3.3v
$Comp
L power:GNDREF #PWR04
U 1 1 6AC16785
P 4600 5200
F 0 "#PWR04" H 4600 4950 50  0001 C CNN
F 1 "GNDREF" H 4605 5027 50  0001 C CNN
F 2 "" H 4600 5200 50  0001 C CNN
F 3 "" H 4600 5200 50  0001 C CNN
	1    4600 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR05
U 1 1 6AC1E4F0
P 5050 5200
F 0 "#PWR05" H 5050 4950 50  0001 C CNN
F 1 "GNDREF" H 5055 5027 50  0001 C CNN
F 2 "" H 5050 5200 50  0001 C CNN
F 3 "" H 5050 5200 50  0001 C CNN
	1    5050 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR013
U 1 1 6AC23FAF
P 9050 7850
F 0 "#PWR013" H 9050 7600 50  0001 C CNN
F 1 "GNDREF" H 9055 7677 50  0001 C CNN
F 2 "" H 9050 7850 50  0001 C CNN
F 3 "" H 9050 7850 50  0001 C CNN
	1    9050 7850
	1    0    0    -1  
$EndComp
Text Label 5000 6900 2    50   Italic 10
DISP_OUT
Text Label 5000 6800 2    50   Italic 10
DISP_CLK
Wire Wire Line
	5000 7000 4500 7000
Wire Wire Line
	5000 7300 4750 7300
$Comp
L Device:R R3
U 1 1 6AC5FFEE
P 4750 7450
F 0 "R3" V 4850 7450 50  0000 C CNN
F 1 "1K" V 4634 7450 50  0000 C CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 4680 7450 50  0001 C CNN
F 3 "~" H 4750 7450 50  0001 C CNN
	1    4750 7450
	1    0    0    -1  
$EndComp
Text Label 4750 7650 2    50   Italic 10
VCC_3.3v
Text Label 5000 6700 2    50   Italic 10
VCC_3.3v
$Comp
L power:GNDREF #PWR06
U 1 1 6AC62830
P 4500 6600
F 0 "#PWR06" H 4500 6350 50  0001 C CNN
F 1 "GNDREF" H 4505 6427 50  0001 C CNN
F 2 "" H 4500 6600 50  0001 C CNN
F 3 "" H 4500 6600 50  0001 C CNN
	1    4500 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 6600 4500 6600
Text Label 8550 6850 2    50   Italic 10
SD_IN
$Comp
L 74xx:74HCT244 U6
U 1 1 6AC66826
P 9200 3050
F 0 "U6" H 9300 3800 50  0000 C CNN
F 1 "74HCT244" H 9450 3700 50  0000 C CNN
F 2 "GERAL:standard_DIP_20pins_thin_body" H 9200 3050 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT244.pdf" H 9200 3050 50  0001 C CNN
	1    9200 3050
	-1   0    0    1   
$EndComp
Text Label 7150 2000 0    50   Italic 10
VCC_5v
Text Label 9200 3850 2    50   Italic 10
VCC_5v
Text Label 9700 2650 0    50   Italic 10
~ENABLE_ADDR_LOW
Text Label 9700 2550 0    50   Italic 10
ENABLE_ADDR_LOW
$Comp
L power:GNDREF #PWR08
U 1 1 6AC989E2
P 6200 6450
F 0 "#PWR08" H 6200 6200 50  0001 C CNN
F 1 "GNDREF" H 6205 6277 50  0001 C CNN
F 2 "" H 6200 6450 50  0001 C CNN
F 3 "" H 6200 6450 50  0001 C CNN
	1    6200 6450
	1    0    0    -1  
$EndComp
Text Label 6350 6700 2    50   Italic 10
VCC_3.3v
Wire Wire Line
	6200 6450 6350 6450
Wire Wire Line
	6350 6450 6350 6600
NoConn ~ 6350 6800
NoConn ~ 6350 7300
Text Label 6350 7000 2    50   Italic 10
SD_OUT
Text Label 6350 6900 2    50   Italic 10
SD_CS
Text Label 6350 7200 2    50   Italic 10
SD_IN
Text Label 6350 7100 2    50   Italic 10
SD_CLK
Text Notes 3300 3250 1    63   Italic 13
-----v-----
Text Notes 4450 6250 0    63   Italic 13
Écrã
Text Notes 5950 6250 0    63   Italic 13
Cartão SD
Text Notes 7600 6800 0    63   Italic 13
Écrã+SD\n
Connection ~ 4750 7300
Wire Wire Line
	4750 7300 4500 7300
Wire Wire Line
	4500 7000 4500 7300
Wire Wire Line
	4750 7600 4750 7650
Wire Wire Line
	4500 7650 4450 7650
Wire Wire Line
	4400 4500 4600 4500
Wire Wire Line
	5050 4550 5050 4400
Wire Wire Line
	4600 4550 4600 4500
Connection ~ 4600 4500
Wire Wire Line
	4600 4500 5100 4500
Text Notes 10500 2963 2    63   Italic 13
desde\nCPU
Text Notes 10550 4613 2    63   Italic 13
desde\nCPU
Text Notes 10263 4400 3    63   Italic 13
----^------
$Comp
L 74xx:74HCT244 U8
U 1 1 6ABFB18E
P 9150 4700
F 0 "U8" H 9250 5450 50  0000 C CNN
F 1 "74HCT244" H 9400 5350 50  0000 C CNN
F 2 "GERAL:standard_DIP_20pins_thin_body" H 9150 4700 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT244.pdf" H 9150 4700 50  0001 C CNN
	1    9150 4700
	-1   0    0    1   
$EndComp
Text Label 9650 4900 0    50   Italic 10
A3
Text Label 9650 4700 0    50   Italic 10
A7
Text Label 8650 4600 2    50   Italic 10
A2'
Text Label 8650 4500 2    50   Italic 10
A3'
Text Label 8650 4800 2    50   Italic 10
A0'
Text Label 8650 4700 2    50   Italic 10
A1'
Text Label 9650 4600 0    50   Italic 10
A8
Text Label 9650 4500 0    50   Italic 10
A9
Text Label 9700 3150 0    50   Italic 10
A10
Wire Wire Line
	9150 3900 9200 3900
Wire Wire Line
	9200 3900 9200 3950
$Comp
L power:GNDREF #PWR010
U 1 1 6AD1E3D1
P 4950 1350
F 0 "#PWR010" H 4950 1100 50  0001 C CNN
F 1 "GNDREF" H 4955 1177 50  0001 C CNN
F 2 "" H 4950 1350 50  0001 C CNN
F 3 "" H 4950 1350 50  0001 C CNN
	1    4950 1350
	1    0    0    -1  
$EndComp
Text Notes 8400 4850 0    63   Italic 13
---
Text Notes 8450 3400 0    63   Italic 13
---
Text Notes 9700 3400 0    63   Italic 13
-----
Text Notes 9750 4850 0    63   Italic 13
-----
NoConn ~ 8700 3250
NoConn ~ 9700 3250
Text Notes 10213 2750 3    63   Italic 13
----^------
Text Label 8700 3550 2    50   Italic 10
A4'
Text Label 8700 3450 2    50   Italic 10
A5'
Text Label 8700 3150 2    50   Italic 10
A4'
Text Label 8700 3050 2    50   Italic 10
A5'
$Comp
L power:GNDREF #PWR09
U 1 1 6AD49CD5
P 5250 8500
F 0 "#PWR09" H 5250 8250 50  0001 C CNN
F 1 "GNDREF" H 5255 8327 50  0001 C CNN
F 2 "" H 5250 8500 50  0001 C CNN
F 3 "" H 5250 8500 50  0001 C CNN
	1    5250 8500
	1    0    0    -1  
$EndComp
Text Label 7150 2900 0    50   Italic 10
RASP_PICO_RESET
Text Label 5350 8200 2    50   Italic 10
RASP_PICO_RESET
Text Notes 4700 8000 0    63   Italic 13
Botão de RESET
$Comp
L GERAL:SD_CARD U5
U 1 1 6AD83DFA
P 6800 6500
F 0 "U5" H 7378 6096 50  0000 L CNN
F 1 "SD_CARD" H 7378 6005 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 6800 6700 50  0001 C CNN
F 3 "" H 6800 6700 50  0001 C CNN
	1    6800 6500
	1    0    0    -1  
$EndComp
Text Notes 3650 6250 0    63   Italic 13
Joypad
Text Label 3800 6550 2    50   Italic 10
AXIS_SW
Text Label 3800 6750 2    50   Italic 10
AXIS_X
$Comp
L GERAL:TFT_st7735 U4
U 1 1 6AE432D6
P 5450 6750
F 0 "U4" H 5050 7150 50  0000 L CNN
F 1 "TFT_st7735" H 5050 7050 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 5450 7200 50  0001 C CNN
F 3 "" H 5450 7200 50  0001 C CNN
	1    5450 6750
	1    0    0    -1  
$EndComp
Text Label 9550 6750 0    50   Italic 10
SD_CLK
Text Label 9550 7150 0    50   Italic 10
DISP_DC
Text Label 9550 7250 0    50   Italic 10
DISP_CS
Text Label 9550 7050 0    50   Italic 10
DISP_OUT
Text Label 9550 6950 0    50   Italic 10
DISP_CLK
Text Label 9550 6650 0    50   Italic 10
SD_OUT
Text Label 9550 6850 0    50   Italic 10
OUT_3
$Comp
L 74xx:74HCT244 U9
U 1 1 6AC04AA0
P 9050 7050
F 0 "U9" H 9150 7800 50  0000 C CNN
F 1 "74HC244" H 9300 7700 50  0000 C CNN
F 2 "GERAL:standard_DIP_20pins_thin_body" H 9050 7050 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT244.pdf" H 9050 7050 50  0001 C CNN
	1    9050 7050
	1    0    0    -1  
$EndComp
Text Label 8550 6650 2    50   Italic 10
OUT_1
Text Notes 8150 7250 1    63   Italic 13
------^---
Text Label 9550 6550 0    50   Italic 10
SD_CS
Text Label 5000 7100 2    50   Italic 10
DISP_DC
Text Label 5000 7200 2    50   Italic 10
DISP_CS
Text Notes 5750 2350 2    63   Italic 13
--------
Text Label 5750 2500 2    50   Italic 10
A5''
Text Label 5750 2400 2    50   Italic 10
A4''
Text Label 5750 2300 2    50   Italic 10
A3''
Text Label 5750 2200 2    50   Italic 10
A2''
Text Label 5750 2000 2    50   Italic 10
A1''
Text Label 5750 1900 2    50   Italic 10
A0''
Text Label 7150 2500 0    50   Italic 10
ENABLE_SD
Text Label 7150 3700 0    50   Italic 10
MEMR_EN'
NoConn ~ 5750 2600
NoConn ~ 5750 3100
NoConn ~ 7150 3100
NoConn ~ 7150 2600
NoConn ~ 7150 3600
NoConn ~ 7150 2400
NoConn ~ 7150 2200
NoConn ~ 7150 1900
$Comp
L Device:C C2
U 1 1 6AEE5683
P 2000 5500
F 0 "C2" H 2115 5546 50  0000 L CNN
F 1 "C" H 2115 5455 50  0000 L CNN
F 2 "GERAL:standard_2pins_half" H 2038 5350 50  0001 C CNN
F 3 "~" H 2000 5500 50  0001 C CNN
	1    2000 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR0101
U 1 1 6AEEBF55
P 2000 5650
F 0 "#PWR0101" H 2000 5400 50  0001 C CNN
F 1 "GNDREF" H 2005 5477 50  0001 C CNN
F 2 "" H 2000 5650 50  0001 C CNN
F 3 "" H 2000 5650 50  0001 C CNN
	1    2000 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 6AEED2C6
P 2350 5500
F 0 "C3" H 2465 5546 50  0000 L CNN
F 1 "C" H 2465 5455 50  0000 L CNN
F 2 "GERAL:standard_2pins_half" H 2388 5350 50  0001 C CNN
F 3 "~" H 2350 5500 50  0001 C CNN
	1    2350 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR0102
U 1 1 6AEED2CD
P 2350 5650
F 0 "#PWR0102" H 2350 5400 50  0001 C CNN
F 1 "GNDREF" H 2355 5477 50  0001 C CNN
F 2 "" H 2350 5650 50  0001 C CNN
F 3 "" H 2350 5650 50  0001 C CNN
	1    2350 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 6AEEE152
P 2700 5500
F 0 "C4" H 2815 5546 50  0000 L CNN
F 1 "C" H 2815 5455 50  0000 L CNN
F 2 "GERAL:standard_2pins_half" H 2738 5350 50  0001 C CNN
F 3 "~" H 2700 5500 50  0001 C CNN
	1    2700 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR0103
U 1 1 6AEEE159
P 2700 5650
F 0 "#PWR0103" H 2700 5400 50  0001 C CNN
F 1 "GNDREF" H 2705 5477 50  0001 C CNN
F 2 "" H 2700 5650 50  0001 C CNN
F 3 "" H 2700 5650 50  0001 C CNN
	1    2700 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 6AEEF4AB
P 1600 5450
F 0 "C1" H 1715 5496 50  0000 L CNN
F 1 "C" H 1715 5405 50  0000 L CNN
F 2 "GERAL:standard_2pins_half" H 1638 5300 50  0001 C CNN
F 3 "~" H 1600 5450 50  0001 C CNN
	1    1600 5450
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR0104
U 1 1 6AEEF4B2
P 1600 5600
F 0 "#PWR0104" H 1600 5350 50  0001 C CNN
F 1 "GNDREF" H 1605 5427 50  0001 C CNN
F 2 "" H 1600 5600 50  0001 C CNN
F 3 "" H 1600 5600 50  0001 C CNN
	1    1600 5600
	1    0    0    -1  
$EndComp
Text Label 7150 3000 0    50   Italic 10
~ENABLE_ADDR_LOW
NoConn ~ 5750 3600
NoConn ~ 8700 3350
NoConn ~ 9700 3350
NoConn ~ 8700 2950
NoConn ~ 8700 2850
NoConn ~ 9700 2850
NoConn ~ 9700 2950
Text Label 9650 4800 0    50   Italic 10
A6
Text Notes 5450 1900 2    51   Italic 10
A0\n
Text Notes 5450 2000 2    51   Italic 10
A1\n
Text Notes 5450 2200 2    51   Italic 10
A2\n
Text Notes 5450 2300 2    51   Italic 10
A3\n
Text Notes 5450 2400 2    51   Italic 10
A4\n
Text Notes 5450 2500 2    51   Italic 10
A5\n
Text Notes 5300 1900 2    51   Italic 10
A6\n
Text Notes 5300 2000 2    51   Italic 10
A1\n
Text Notes 5300 2200 2    51   Italic 10
A7\n
Text Notes 5300 2300 2    51   Italic 10
A8\n
Text Notes 5300 2400 2    51   Italic 10
A10\n
Text Notes 5300 2500 2    51   Italic 10
A11
Text Notes 5450 1750 2    51   Italic 10
LOW\n
Text Notes 5300 1750 2    51   Italic 10
HI
Text Notes 4737 1750 3    63   Italic 13
---------
Text Notes 5137 2600 1    63   Italic 13
---------
Text Notes 5000 2137 0    63   Italic 13
A
Text Notes 5000 2437 0    63   Italic 13
B
Text Notes 9200 4463 2    63   Italic 13
A
Text Notes 9250 2813 2    63   Italic 13
B
Text Label 9700 3050 0    50   Italic 10
A11
Wire Wire Line
	9200 2250 9300 2250
Text Notes 8350 4800 1    87   Italic 17
-----------
$Comp
L GERAL:button_4PIN U11
U 1 1 6B3D334B
P 5550 8050
F 0 "U11" H 5778 7801 50  0000 L CNN
F 1 "button_4PIN" H 5778 7710 50  0000 L CNN
F 2 "GERAL:BUTTON_4PIN" H 5550 8050 50  0001 C CNN
F 3 "" H 5550 8050 50  0001 C CNN
	1    5550 8050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 8500 5350 8500
$Comp
L 74xx:74HCT04 U7
U 7 1 6B48906C
P 8900 9400
F 0 "U7" H 9050 9650 50  0000 C CNN
F 1 "74HCT04" H 9150 9550 50  0000 C CNN
F 2 "GERAL:standard_DIP_14OvalPins" H 8900 9400 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT04.pdf" H 8900 9400 50  0001 C CNN
	7    8900 9400
	0    -1   -1   0   
$EndComp
Text Label 8400 9700 2    50   Italic 10
VCC_3.3v
$Comp
L power:GNDREF #PWR0106
U 1 1 6B48BD8C
P 9400 9400
F 0 "#PWR0106" H 9400 9150 50  0001 C CNN
F 1 "GNDREF" H 9405 9227 50  0001 C CNN
F 2 "" H 9400 9400 50  0001 C CNN
F 3 "" H 9400 9400 50  0001 C CNN
	1    9400 9400
	1    0    0    -1  
$EndComp
$Comp
L GERAL:Joypad U10
U 1 1 6B6E0D27
P 4000 6450
F 0 "U10" H 4150 6500 50  0000 L CNN
F 1 "Joypad" H 3950 6600 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 4000 6550 50  0001 C CNN
F 3 "" H 4000 6550 50  0001 C CNN
	1    4000 6450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 6B6E5513
P 3650 6850
F 0 "R10" V 3650 6850 50  0000 C CNN
F 1 "1K" V 3600 7150 50  0000 C CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 3580 6850 50  0001 C CNN
F 3 "~" H 3650 6850 50  0001 C CNN
	1    3650 6850
	0    -1   -1   0   
$EndComp
Text Label 3500 6850 2    50   Italic 10
VCC_3.3v
$Comp
L power:GNDREF #PWR0107
U 1 1 6B6EBE28
P 3800 6950
F 0 "#PWR0107" H 3800 6700 50  0001 C CNN
F 1 "GNDREF" H 3805 6777 50  0001 C CNN
F 2 "" H 3800 6950 50  0001 C CNN
F 3 "" H 3800 6950 50  0001 C CNN
	1    3800 6950
	1    0    0    -1  
$EndComp
Text Label 3800 6650 2    50   Italic 10
AXIS_Y
Text Label 9650 4300 0    50   Italic 10
~ENABLE_ADDR_LOW
Text Label 9650 4200 0    50   Italic 10
ENABLE_ADDR_LOW
Wire Wire Line
	12800 3500 12800 3700
Text Label 12400 2750 1    50   Italic 10
A3'
Text Notes 8100 1650 0    63   Italic 13
2^13 = indexáveis 8K
Text Notes 8100 1550 0    63   Italic 13
Mutiplexagem do AddressBus
Text Label 9050 1900 2    50   Italic 10
~ENABLE_ADDR_LOW
Text Label 9650 1900 0    50   Italic 10
ENABLE_ADDR_LOW
$Comp
L 74xx:74HCT04 U7
U 2 1 6AC90C51
P 9350 1900
F 0 "U7" H 9500 2150 50  0000 C CNN
F 1 "74HCT04" H 9600 2050 50  0000 C CNN
F 2 "GERAL:standard_DIP_14OvalPins" H 9350 1900 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT04.pdf" H 9350 1900 50  0001 C CNN
	2    9350 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR011
U 1 1 6AC452E6
P 12800 3700
F 0 "#PWR011" H 12800 3450 50  0001 C CNN
F 1 "GNDREF" H 12805 3527 50  0001 C CNN
F 2 "" H 12800 3700 50  0001 C CNN
F 3 "" H 12800 3700 50  0001 C CNN
	1    12800 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 6AC0796B
P 12550 3350
F 0 "R9" V 12500 3500 50  0000 C CNN
F 1 "R" V 12550 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 12480 3350 50  0001 C CNN
F 3 "~" H 12550 3350 50  0001 C CNN
	1    12550 3350
	-1   0    0    1   
$EndComp
$Comp
L Device:R R8
U 1 1 6AC078C8
P 12650 3350
F 0 "R8" V 12600 3500 50  0000 C CNN
F 1 "R" V 12650 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 12580 3350 50  0001 C CNN
F 3 "~" H 12650 3350 50  0001 C CNN
	1    12650 3350
	-1   0    0    1   
$EndComp
$Comp
L Device:R R7
U 1 1 6AC07784
P 12100 3350
F 0 "R7" V 12050 3500 50  0000 C CNN
F 1 "R" V 12100 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 12030 3350 50  0001 C CNN
F 3 "~" H 12100 3350 50  0001 C CNN
	1    12100 3350
	-1   0    0    1   
$EndComp
$Comp
L Device:R R6
U 1 1 6AC0766E
P 12200 3350
F 0 "R6" V 12150 3500 50  0000 C CNN
F 1 "R" V 12200 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 12130 3350 50  0001 C CNN
F 3 "~" H 12200 3350 50  0001 C CNN
	1    12200 3350
	-1   0    0    1   
$EndComp
$Comp
L Device:R R5
U 1 1 6AC07525
P 12300 3350
F 0 "R5" V 12250 3500 50  0000 C CNN
F 1 "R" V 12300 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 12230 3350 50  0001 C CNN
F 3 "~" H 12300 3350 50  0001 C CNN
	1    12300 3350
	-1   0    0    1   
$EndComp
$Comp
L Device:R R4
U 1 1 6AC0737A
P 12400 3350
F 0 "R4" V 12350 3500 50  0000 C CNN
F 1 "R" V 12400 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 12330 3350 50  0001 C CNN
F 3 "~" H 12400 3350 50  0001 C CNN
	1    12400 3350
	-1   0    0    1   
$EndComp
$Comp
L Device:R R12
U 1 1 6ACAFACA
P 12200 2900
F 0 "R12" V 12150 3050 50  0000 C CNN
F 1 "R" V 12200 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 12130 2900 50  0001 C CNN
F 3 "~" H 12200 2900 50  0001 C CNN
	1    12200 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 6ACAFAD0
P 12100 2900
F 0 "R11" V 12050 3050 50  0000 C CNN
F 1 "R" V 12100 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 12030 2900 50  0001 C CNN
F 3 "~" H 12100 2900 50  0001 C CNN
	1    12100 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R16
U 1 1 6ACAFAD6
P 12650 2900
F 0 "R16" V 12600 3050 50  0000 C CNN
F 1 "R" V 12650 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 12580 2900 50  0001 C CNN
F 3 "~" H 12650 2900 50  0001 C CNN
	1    12650 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R15
U 1 1 6ACAFADC
P 12550 2900
F 0 "R15" V 12500 3050 50  0000 C CNN
F 1 "R" V 12550 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 12480 2900 50  0001 C CNN
F 3 "~" H 12550 2900 50  0001 C CNN
	1    12550 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R14
U 1 1 6ACAFAE2
P 12400 2900
F 0 "R14" V 12350 3050 50  0000 C CNN
F 1 "R" V 12400 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 12330 2900 50  0001 C CNN
F 3 "~" H 12400 2900 50  0001 C CNN
	1    12400 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R13
U 1 1 6ACAFAE8
P 12300 2900
F 0 "R13" V 12250 3050 50  0000 C CNN
F 1 "R" V 12300 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 12230 2900 50  0001 C CNN
F 3 "~" H 12300 2900 50  0001 C CNN
	1    12300 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	12650 3200 12650 3050
Wire Wire Line
	12550 2600 12550 2750
Wire Wire Line
	12300 3050 12300 3200
Wire Wire Line
	12200 2750 12200 2600
Wire Wire Line
	12400 3200 12400 3050
Text Label 12300 2750 1    50   Italic 10
A2'
Text Label 12650 2750 1    50   Italic 10
A5'
Text Label 12550 2750 1    50   Italic 10
A4'
Wire Wire Line
	12100 3050 12100 3200
Text Label 12200 2750 1    50   Italic 10
A1'
Text Label 12100 2750 1    50   Italic 10
A0'
Text Label 12200 3200 1    50   Italic 10
A1''
Text Label 12100 3200 1    50   Italic 10
A0''
Wire Wire Line
	12200 3200 12200 3050
Text Label 12550 3200 1    50   Italic 10
A4''
Text Label 12650 3200 1    50   Italic 10
A5''
Wire Wire Line
	12550 3050 12550 3200
Wire Wire Line
	12550 3500 12650 3500
Wire Wire Line
	12550 3500 12400 3500
Connection ~ 12550 3500
Wire Wire Line
	12300 3500 12400 3500
Connection ~ 12400 3500
Wire Wire Line
	12200 3500 12300 3500
Connection ~ 12300 3500
Wire Wire Line
	12100 3500 12200 3500
Connection ~ 12200 3500
Wire Wire Line
	12650 3500 12800 3500
Connection ~ 12650 3500
Text Label 5100 4500 0    50   Italic 10
MEMW_EN
$Comp
L Device:R R1
U 1 1 6ACAE370
P 4600 4700
F 0 "R1" H 4670 4746 50  0000 L CNN
F 1 "R" H 4670 4655 50  0000 L CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 4530 4700 50  0001 C CNN
F 3 "~" H 4600 4700 50  0001 C CNN
	1    4600 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 6ACAEA5C
P 4600 5050
F 0 "R2" H 4670 5096 50  0000 L CNN
F 1 "R" H 4670 5005 50  0000 L CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 4530 5050 50  0001 C CNN
F 3 "~" H 4600 5050 50  0001 C CNN
	1    4600 5050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R17
U 1 1 6ACAF821
P 5050 4700
F 0 "R17" H 5120 4746 50  0000 L CNN
F 1 "R" H 5120 4655 50  0000 L CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 4980 4700 50  0001 C CNN
F 3 "~" H 5050 4700 50  0001 C CNN
	1    5050 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R18
U 1 1 6ACB06C4
P 5050 5050
F 0 "R18" H 5120 5096 50  0000 L CNN
F 1 "R" H 5120 5005 50  0000 L CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 4980 5050 50  0001 C CNN
F 3 "~" H 5050 5050 50  0001 C CNN
	1    5050 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 4850 4600 4900
Wire Wire Line
	5050 4900 5050 4850
Wire Wire Line
	5050 4900 5200 4900
Connection ~ 5050 4900
Wire Wire Line
	4600 4900 4700 4900
Connection ~ 4600 4900
Text Label 4700 4900 0    50   Italic 10
MEMW_EN'
Wire Wire Line
	4400 4400 5050 4400
Text Label 5200 4900 0    50   Italic 10
MEMR_EN'
Text Label 12300 3200 1    50   Italic 10
A2''
Text Label 12400 3200 1    50   Italic 10
A3''
Text Label 3600 2800 2    50   Italic 10
D3'
Text Label 3600 2700 2    50   Italic 10
D2'
Wire Wire Line
	4200 2400 4450 2400
$Comp
L Connector:Bus_ISA_8bit J2
U 1 1 6ACE4668
P 1850 8600
F 0 "J2" H 1850 10367 50  0000 C CNN
F 1 "Bus_ISA_8bit" H 1850 10276 50  0000 C CNN
F 2 "GERAL:ISA_8bit_edge" H 1850 8600 50  0001 C CNN
F 3 "https://en.wikipedia.org/wiki/Industry_Standard_Architecture" H 1850 8600 50  0001 C CNN
	1    1850 8600
	1    0    0    -1  
$EndComp
Text Label 1150 7200 2    50   Italic 10
RESET
Text Label 1150 8200 2    50   Italic 10
~MEMR
$Comp
L power:GNDREF #PWR0108
U 1 1 6ACF3955
P 750 7100
F 0 "#PWR0108" H 750 6850 50  0001 C CNN
F 1 "GNDREF" H 755 6927 50  0001 C CNN
F 2 "" H 750 7100 50  0001 C CNN
F 3 "" H 750 7100 50  0001 C CNN
	1    750  7100
	1    0    0    -1  
$EndComp
Text Label 1150 7300 2    50   Italic 10
VCC_5v
Wire Wire Line
	1150 7100 750  7100
Text Label 1150 8100 2    50   Italic 10
~MEMW
$Comp
L power:GNDREF #PWR0109
U 1 1 6ACF395E
P 750 10100
F 0 "#PWR0109" H 750 9850 50  0001 C CNN
F 1 "GNDREF" H 755 9927 50  0001 C CNN
F 2 "" H 750 10100 50  0001 C CNN
F 3 "" H 750 10100 50  0001 C CNN
	1    750  10100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 10100 750  10100
Text Label 1150 9900 2    50   Italic 10
VCC_5v
Text Label 2550 10100 0    50   Italic 10
A0
Text Label 2550 10000 0    50   Italic 10
A1
Text Label 2550 9900 0    50   Italic 10
A2
Text Label 2550 9800 0    50   Italic 10
A3
Text Label 2550 9700 0    50   Italic 10
A4
Text Label 2550 9600 0    50   Italic 10
A5
Text Label 2550 9500 0    50   Italic 10
A6
Text Label 2550 9400 0    50   Italic 10
A7
Text Label 2550 9300 0    50   Italic 10
A8
Text Label 2550 9200 0    50   Italic 10
A9
Text Label 2550 9100 0    50   Italic 10
A10
Text Label 2550 9000 0    50   Italic 10
A11
Text Label 2550 8900 0    50   Italic 10
A12
Text Label 2550 8800 0    50   Italic 10
A13
Text Label 2550 8700 0    50   Italic 10
A14
Text Label 2550 8600 0    50   Italic 10
A15
Text Label 2550 8500 0    50   Italic 10
A16
Text Label 2550 8400 0    50   Italic 10
A17
Text Label 2550 8300 0    50   Italic 10
A18
Text Label 2550 8200 0    50   Italic 10
A19
Text Label 2550 7900 0    50   Italic 10
D0
Text Label 2550 7800 0    50   Italic 10
D1
Text Label 2550 7700 0    50   Italic 10
D2
Text Label 2550 7600 0    50   Italic 10
D3
Text Label 2550 7500 0    50   Italic 10
D4
Text Label 2550 7300 0    50   Italic 10
D6
Text Label 2550 7200 0    50   Italic 10
D7
Text Label 2550 7400 0    50   Italic 10
D5
Text Notes 5800 1500 0    75   Italic 15
RASPBERRY PI PICO
Text Label 7150 2800 0    50   Italic 10
AXIS_X
Text Label 1600 5300 1    50   Italic 10
VCC_3.3v
Text Label 2700 5350 1    50   Italic 10
VCC_5v
Text Label 2350 5350 1    50   Italic 10
VCC_5v
Text Label 2000 5350 1    50   Italic 10
VCC_5v
$Comp
L Logic_Programmable:PAL16L8 U2
U 1 1 6ABF456C
P 3900 4700
F 0 "U2" H 4100 5450 50  0000 C CNN
F 1 "MEM_PAL16L8" H 4300 5350 50  0000 C CNN
F 2 "GERAL:standard_DIP_20pins_thin_body" H 3900 4700 50  0001 C CNN
F 3 "" H 3900 4700 50  0001 C CNN
	1    3900 4700
	1    0    0    -1  
$EndComp
Text Label 3900 4000 2    50   Italic 10
VCC_5v
Text Label 3400 5000 2    50   Italic 10
~MEMW
Text Notes 3100 3800 0    63   Italic 13
Validação de endereço ROM\n(Programmable Array Logic)\n
Text Label 3400 4900 2    50   Italic 10
~MEMR
Text Label 3400 4800 2    50   Italic 10
A19
Text Label 3400 4600 2    50   Italic 10
A17
Text Label 3400 4500 2    50   Italic 10
A16
Text Label 3400 4400 2    50   Italic 10
A15
Text Notes 2900 2900 0    63   Italic 13
desde\nCPU
$Comp
L Transistor_BJT:2N3904 Q1
U 1 1 6ACF1665
P 4850 1150
F 0 "Q1" H 5040 1196 50  0000 L CNN
F 1 "2N3904" H 5040 1105 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 5050 1075 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/2N3903-D.PDF" H 4850 1150 50  0001 L CNN
	1    4850 1150
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR0110
U 1 1 6AD04CE2
P 9300 2250
F 0 "#PWR0110" H 9300 2000 50  0001 C CNN
F 1 "GNDREF" H 9305 2077 50  0001 C CNN
F 2 "" H 9300 2250 50  0001 C CNN
F 3 "" H 9300 2250 50  0001 C CNN
	1    9300 2250
	1    0    0    -1  
$EndComp
Text Label 2550 8000 0    50   Italic 10
IO_READY
Text Label 4950 950  0    50   Italic 10
IO_READY
$Comp
L Device:R R19
U 1 1 6AD09745
P 4650 1300
F 0 "R19" H 4500 1300 50  0000 L CNN
F 1 "4.7K" H 4400 1200 50  0000 L CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 4580 1300 50  0001 C CNN
F 3 "~" H 4650 1300 50  0001 C CNN
	1    4650 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 1450 4650 1450
Text Notes 10000 5050 0    51   Italic 10
LOW\n
Text Notes 9950 3500 0    51   Italic 10
LOW\n
Text Notes 10050 4650 0    51   Italic 10
HI\n
Text Notes 9950 3100 0    51   Italic 10
HI\n
Text Notes 9800 4600 0    51   Italic 10
*\n
Text Notes 9800 4500 0    51   Italic 10
*\n
Text Notes 9850 3150 0    51   Italic 10
*\n
Text Notes 9850 3050 0    51   Italic 10
*\n
$Comp
L Device:R R20
U 1 1 6AD57A27
P 9150 8450
F 0 "R20" H 9220 8496 50  0000 L CNN
F 1 "1K" H 9220 8405 50  0000 L CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 9080 8450 50  0001 C CNN
F 3 "~" H 9150 8450 50  0001 C CNN
	1    9150 8450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 8600 9300 8600
$Comp
L Device:R R21
U 1 1 6AD5C693
P 9150 8750
F 0 "R21" H 9220 8796 50  0000 L CNN
F 1 "2K" H 9220 8705 50  0000 L CNN
F 2 "Resistor_SMD:R_0201_0603Metric" V 9080 8750 50  0001 C CNN
F 3 "~" H 9150 8750 50  0001 C CNN
	1    9150 8750
	1    0    0    -1  
$EndComp
Connection ~ 9150 8600
$Comp
L power:GNDREF #PWR0105
U 1 1 6AD5FCAF
P 9150 8900
F 0 "#PWR0105" H 9150 8650 50  0001 C CNN
F 1 "GNDREF" H 9155 8727 50  0001 C CNN
F 2 "" H 9150 8900 50  0001 C CNN
F 3 "" H 9150 8900 50  0001 C CNN
	1    9150 8900
	1    0    0    -1  
$EndComp
Text Label 3400 4700 2    50   Italic 10
A18
Text Label 5750 2700 2    50   Italic 10
IO_WAIT
Text Label 3700 1450 2    50   Italic 10
IO_WAIT
Text Label 1150 9100 2    50   Italic 10
IRQ7
Text Label 1150 9500 2    50   Italic 10
IRQ3
Text Label 1150 9300 2    50   Italic 10
IRQ5
Text Label 3850 9350 2    50   Italic 10
IRQ7
Text Label 3850 10050 2    50   Italic 10
IRQ3
Text Label 3850 9700 2    50   Italic 10
IRQ5
$Comp
L Switch:SW_DIP_x01 SW1
U 1 1 6B1E4A19
P 4150 9350
F 0 "SW1" H 4150 9617 50  0000 C CNN
F 1 "SW_DIP_x01" H 4150 9526 50  0000 C CNN
F 2 "GERAL:jumper_set_1" H 4150 9350 50  0001 C CNN
F 3 "~" H 4150 9350 50  0001 C CNN
	1    4150 9350
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DIP_x01 SW2
U 1 1 6B1E7B6B
P 4150 9700
F 0 "SW2" H 4150 9967 50  0000 C CNN
F 1 "SW_DIP_x01" H 4150 9876 50  0000 C CNN
F 2 "GERAL:jumper_set_1" H 4150 9700 50  0001 C CNN
F 3 "~" H 4150 9700 50  0001 C CNN
	1    4150 9700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 9700 4450 9350
Connection ~ 4450 9700
Wire Wire Line
	4450 10050 4450 9700
$Comp
L Switch:SW_DIP_x01 SW3
U 1 1 6B1E8D06
P 4150 10050
F 0 "SW3" H 4150 10317 50  0000 C CNN
F 1 "SW_DIP_x01" H 4150 10226 50  0000 C CNN
F 2 "GERAL:jumper_set_1" H 4150 10050 50  0001 C CNN
F 3 "~" H 4150 10050 50  0001 C CNN
	1    4150 10050
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR0111
U 1 1 6B1F1D8F
P 4700 10450
F 0 "#PWR0111" H 4700 10200 50  0001 C CNN
F 1 "GNDREF" H 4705 10277 50  0001 C CNN
F 2 "" H 4700 10450 50  0001 C CNN
F 3 "" H 4700 10450 50  0001 C CNN
	1    4700 10450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 9700 4450 9700
Wire Wire Line
	4700 10300 4700 10450
$Comp
L Switch:SW_DIP_x01 SW4
U 1 1 6B28AAB6
P 4700 10000
F 0 "SW4" H 4700 10267 50  0000 C CNN
F 1 "SW_DIP_x01" H 4700 10176 50  0000 C CNN
F 2 "GERAL:jumper_set_1" H 4700 10000 50  0001 C CNN
F 3 "~" H 4700 10000 50  0001 C CNN
	1    4700 10000
	0    1    1    0   
$EndComp
Text Label 5000 7300 2    50   Italic 10
DISP_BLIGHT
Text Label 5000 7000 2    50   Italic 10
DISP_RES
Text Label 8400 9400 2    50   Italic 10
VCC_5v
$EndSCHEMATC
