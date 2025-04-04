#pragma once
#include<string>
#include<filesystem>
#include<iostream>
#include"stdafx.h"
#include"Blink_C_wrapper.h"
#include"ImageGen.h"

#define BytesPerImage 4;

//Provides function for the SLM pattern window and for tramissting the 
//	look up table (LUT) file for voltage applicatiion vs pixel value to the SLM
class SLM_Setup{

public:
	static void SDK_Creation();
	static void Lut_Choose(int height, int depth);

private:
	SLM_Setup();

};