Set-Railroad
This repository contais the files needed to operate My Railroad using DCC++ and JMRI
1) CMRI_Turn_Sens.ino --> Arduino sketch to control Turnouts and Sensors via JMRI Interface by using Arduino Mega I/O shield to drive servos
2) CMRI_Turn_Sens-PCA9685.ino --> Arduino sketch to control Turnouts and Sensors via JMRI Interface by using multiple PCA9685 to drive servos
3) Init_Turnou.py --> Python script to set to close state all the turnouts before starting operations in JMRI. It will be executed from the JMRI PanelPro
4) JMRI_config\MyJMRI_ext-2023.xml --> is the JMRI panel used to control and manage turnouts and sensors

For more information, please check my website http://szweb.eu
