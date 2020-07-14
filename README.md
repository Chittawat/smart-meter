# Smart Meter Project
This project is part of University of Southampton Electronic and Electrical Engineering design project module which had been implemented within the team of 6 people. The project’s goal is to gain a better understanding of the design and prototyping process, through which every product must go, along with testing at regular intervals.  Over the course of this 7-week exercise several design challenge had to be overcomed to produce a reliable smart meter capable of controlling a micro grid. To keep a meter cost-effective and to improve reliability , the design is made as simple as possible without infringing on its energy efficiency.

## Interface Circuitry
### Analogue Input
(1) The amplification circuit with gain 3.03 initially has a low pass filter at frequency 500 Hz.  Theoretically, VOUT=3.03VIN(03.3V-010V).
(2) After several tests on a breadboard, the circuit was soldered and tested thoroughly using an oscilloscope, and a signal generator to produce input DC voltage from 0-3.3V. When tested with the given Test Bed, the controlled main current shown on LabView was varying with input voltage in linearity.VOUT3.13VIN(03.2V-010V).    Imain0.9VIN(03.3V-03A).
  
(3) Upon testing with the completed system, the 22kHz PWM square wave signal could not be fully rectified to smooth DC voltage, therefore, a new design was generated with gain 3.3 at a cutoff frequency of 33Hz. VOUT3.33VIN(03V-010V).ImainVIN(03V-03A).

Figure?: DAC design  Figure?: simulation of DAC design
 Figure?&?: 1.35V expanded to 4.2V , 2.64V expanded to 9.4V
### Analogue output:
#### AC source
(1)    Two circuits were both applied with an envelope detector consisting of a diode, R1 and C1.
(2)    However, when tested on a circuit board, the diode took up more voltage than expected which reduced the output voltage. To minimise this effect, another 300 resistor was added in the design of Busbar Voltage in series with R2. Although the actual values of the components were lower than expected, based on the outcomes of the tests, both systems operated well.
(3)    When testing through the Testbed, the output signals were not a perfect AC shape. In addition, the actual voltage value did not match the Busbar voltage/current value shown on LabView window. (2.4V on LabView but output 2.32V). Therefore, instead to find the relationship between the value display on LabView and final voltage output from conversion circuits which directly enters in II-Matto. Shown in Figure they are still in linear which meant no changes were needed to handle inaccurate signals.
Ibusbar=3.125Vout(04A-01.18V). Vbusbar=1.5Vout(2.4V -1.6V).
 
#### DC source
Based on the final scenario and tests through the Testbed, the signal output is found to have a maximum voltage of 2V and 3V for solar and wind respectively. Therefore, the potential divider circuits were removed to save power and space. 
Then,  after several tests with the completed system, the source current was:Iwind1.05*Vsignal from TestBed(02.85V-03A), Isolar1.1*Vsignal from TestBed(01.82V-02A).
### Digital input
0/3.3V signals output from II-Matto which respond to actual demands can directly active different loads and battery modes in the TestBed which indicates no need for amplification circuits.
### Digital output
Three identical potential divider circuits were generated to receive demand signals and transfer to the II-Matto.(05V-03.3V).However, when implemented on the circuit board, resistor R2 in one of the circuits  has much lower value 2.9k than expected and also due to connection issues, the output voltage was 2.55V much lower than 3.3V.(5V 2.55V).
When combined with software, this issue did not affect the final reading of  Il-Matto. Hence, all the circuits were testified to operate well. VOUT=1.96VIN(5V -2.55V).   
### Completed System operation
Load 3(1.4A) is on, meanwhile, the total regenerated energy is 0.9A which is not enough to support demand. Thus,required main current is 0.5A. Since the battery already has 2A inside, no extra current is needed to charge battery.

## Control Software and Display
### Il-matto
The smart meter design used an Il-matto microcontroller as the main control. The voltage needed to power up the board is between 3.6-6V with a minimum current of 0.04A. The Il-matto board consists of 4 ports which have been initialised as shown in figure?. The reason behind this is that Port A has ADC input pins while Port D has PWM output pins which were both important for the software. Port B and C were used to control the display on the TFT screen.
### Software Structure
The program has been written in the C programming language. With the use of pointers and memory allocation techniques, the program was able to display the unlimited values with 0.5 seconds for each cycle. Decimal values were displayed using calculations and separate integers for string conversion between integer and decimal values. The analogue input for busbar voltage and current, solar and wind were received on Port A. Due to the AC input signal in the busbar voltage and current, a for loop has been implemented to enable reading of the maximum value for a time range of 10ms as shown in Figure??. For solar and wind, the ADC had converted the initial value into a current reading value by using certain equations. Channels for ADC can be selected by calling the pins, which will cause a change in the ADC multiplexer for the Il-matto.
For the analogue output, the voltage is able to output according to the PWM duty cycle of timer counter 2. No prescaler was initialised to cut off the frequency. The value will be adjusted in accordance to the control system.
For digital input and output, the load will switch on when voltage was received. The value is then delivered from the output pin to the testbed. Depending on the load, control system will decide either to charge or discharge the battery.
### Interface
The interface design is filled with essential information that needs to be read from the TFT screen. Each values were labelled accurately with the proper units. Interesting animation was developed for each of the displayed logo in order to engage with the users. For example, when the battery is charging, the cell turns yellow while discharging the battery displayed a green cell. Lastly, the “SMART METER G” has an increased font size, which was done by using an external library (pictor.h).
