#include"Setup_SLM.h"


//Default Constructor, which is private as functions are static
SLM_Setup::SLM_Setup()
{

}

//Hides console from user and creates pattern transmission window
void SLM_Setup::SDK_Creation() {
	//hides the console from the user
	FreeConsole();

	//Creates the window that will communicate with the SLM via HDMI
	Create_SDK();

}

//loads appropriate LUT file based on SLM resolution and pixel depth
void SLM_Setup::Lut_Choose(int height, int depth)
{

	std::string model_path;

	//Get the current directory of the executable
	std::filesystem::path currentDirectory = std::filesystem::current_path();
	
	//Create a string that is a path to the correct Model of SLM's look-up-table
	if(height == 1152)
		model_path = (currentDirectory.string() + "\\LUT Files\\1920x1152_linearVoltage.lut");
	else
	{
		if (depth == 8)
			model_path = (currentDirectory.string() + "\\LUT Files\\19x12_8bit_linearVoltage.lut");
		else if (depth == 10)
			model_path = (currentDirectory.string() + "\\LUT Files\\19x12_10bit_linearVoltage.lut");
		else
		{	//create a new console and redirect cout to it
			AllocConsole();
			freopen("CONOUT$", "w", stdout);
			
			//output error message and closes program
			std::cout << "Invalid SLM dimensions detected";
			exit(1);
		}
	}

	//Create a constant char* which is Null Terminated
	const char* modelCchar = model_path.c_str();

	//Using the size of the constant char* to create a correctly sized char*
	char* modelCharPtr = new char[model_path.length() + 1];

	//safely copy the const char* to the char* for the Meadowlark SDK Load_lut function
	strcpy_s(modelCharPtr, model_path.length() + 1, modelCchar);

	//Use the correct file path via char* to load the LUT into the SLM via USB
	Load_lut(modelCharPtr);

	//Comment the above line and uncomment below code block to have the 
	//code not run if the Lut file cannot be correctly uploaded to the SLM
	//	The current configuration is good for testing the software without the SLM present
	/*
	if (!Load_lut(modelCharPtr))
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);

		std::cout << "LUT could not be opened cout";
		exit(1);
	}
	*/

	//Releasing the data allocated for the model path
	delete[] modelCharPtr;
}
