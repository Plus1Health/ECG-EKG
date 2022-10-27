#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


void main(int argc, char *argv[])
{
   
	if (argc < 2) {
		cout << "Invalid command. Command Example: ECGReader 00000564.ECG"  << endl;
		return;
	}

	string fileEcgDat(argv[1]);

	string fileEcgTxt = fileEcgDat;
	fileEcgTxt.append(".txt");
	
	fstream ecgDat,ecgTxt;

	int count = 0;

	ecgDat.open(fileEcgDat, fstream::in  | ios_base::binary);
	ecgTxt.open(fileEcgTxt, fstream::out);


	if (!ecgDat)
	{
		cout << "Failed to open the file: " << fileEcgDat.c_str() << endl;
		return;
	}

	uint8_t header_info[48] = { 0 };

	ecgDat.read((char *)&header_info, sizeof(header_info));

	uint8_t ecg_point[2];


	ecgTxt << "ECG Lead I Value" << "," << "Lead Off" << "," << "Pace Flag" << "," << "R Flag"<< endl;

	while (!ecgDat.eof())
	{
		ecgDat.read((char *)&ecg_point, 2);

		uint8_t byte0 = ecg_point[0];
		uint8_t byte1 = ecg_point[1];

		// ECG Lead Off. 1 - Yes | 0 - No
		uint8_t lead_off = (byte0 & 0x80);    // 0x80 10000000
		//ECG Pace Flag. 1 - Yes | 0 - No
		uint8_t is_pace = (byte0 & 0x40) ;    // 0x40 01000000 
		//Detected Noise flag. 1- Yes | 0 - No
		uint8_t is_Noise_flag = (byte0 & 0x10);   //  0x20 0001 0000

		//Parse ECG sample value
		short nVal = (short)(byte0 & 0x0F);
		nVal <<= 8;
		nVal += (byte1 & 0xFF);
		if (0x08 == (byte0 & 0x08)) {
			nVal -= 4096;
		}
	
	
		ecgTxt << static_cast<int32_t>(nVal) << "," << static_cast<int32_t>(lead_off) << "," << static_cast<int32_t>(is_pace) << "," << static_cast<int32_t>(is_R_flag) << "," << static_cast<int32_t>(is_Noise_flag) << endl;

	}
	

	cout << "Successfully exported ECG Txt File. " << fileEcgTxt.c_str() << endl;

	ecgDat.close();
	ecgTxt.close();
	
	return;
}
