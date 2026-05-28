#pragma once

class CMetadataReader
{
public:
	CMetadataReader();
	~CMetadataReader();
private:
	CString ExecuteCmd(CString strCommand);
public:
	/*

	exiftool.exe commands will use here one CString function at a time...
	-shuttercount
	-model
	-aperture
	-shutterspeed 
	-iso 
	-focallength 
	-imagesize
	-createdate 

	*/

	CString GetShutterCount(CString path); // -shuttercount
	CString GetCameraModel(CString path); // -model
	CString GetAperture(CString path); // -aperture
	CString GetShutterSpeed(CString path); // -shutterspeed
	CString GetISO(CString path); // -iso
	CString GetFocalLength(CString path); // -focallength
	CString GetSize(CString path); // -imagesize
	CString GetDate(CString path); // -createdate
	CString GetCameraModelWithoutLabel(CString path);
};

