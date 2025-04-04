This project was used to create an alternate GUI for the MeadowLark 1920x1152 XY phase series spatial light modulator, using the SDK they provided. 

To get this to control your SLM make sure you include the files that came with the download for your SLM.
the header files: Blink_C_wrapper.h, stdafx.h targetver.h
the static libraries: ImageGen.lib, Blink_C_wrapper.lib
the dynamic libraries: sfml-windows-2.dll, sfml-system-2.dll, sfml-graphics-2.dll
                      python38.dll (yes), ImageGen.dll, HdmiDisplay.dll, Blink_C_wrapper.lib

This was originaly created for a course in SP23 and was later used during my phase-based attacks research.
