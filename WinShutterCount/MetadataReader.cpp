#include "stdafx.h"
#include "MetadataReader.h"


CMetadataReader::CMetadataReader()
{
}


CMetadataReader::~CMetadataReader()
{
}

// Execute function for exiftool.exe
// Private Function
CString CMetadataReader::ExecuteCmd(CString strCommand)
{
	CString strOutput;
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

	// 1. Create the Pipe
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
		return _T("Error: CreatePipe failed");

	// Ensure the read handle is NOT inherited by the child process
	SetHandleInformation(hRead, HANDLE_FLAG_INHERIT, 0);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags |= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	si.hStdOutput = hWrite;     // Redirect stdout to pipe
	si.hStdError = hWrite;      // Redirect stderr to pipe
	si.wShowWindow = SW_HIDE;   // Hide the console window

	ZeroMemory(&pi, sizeof(pi));

	// 2. Create the Child Process
	// Note: CreateProcess requires a mutable string for the command line
	TCHAR* cmdLine = strCommand.GetBuffer(strCommand.GetLength() + 1);

	BOOL bSuccess = CreateProcess(NULL, cmdLine, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	strCommand.ReleaseBuffer();

	// Close the write end of the pipe in the parent, otherwise ReadFile will hang
	CloseHandle(hWrite);

	if (bSuccess)
	{
		// 3. Read from the Pipe
		DWORD bytesRead;
		const int BUFSIZE = 4096;
		char buffer[BUFSIZE]; // Commands output ANSI/UTF-8, not wchar_t

		while (ReadFile(hRead, buffer, BUFSIZE - 1, &bytesRead, NULL) && bytesRead > 0)
		{
			buffer[bytesRead] = '\0'; // Null terminate
			strOutput += CString(buffer); // Implicit conversion from char* to CString (wchar_t)
		}

		// Cleanup
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else
	{
		strOutput.Format(_T("Error: CreateProcess failed (Code: %d)"), GetLastError());
	}

	CloseHandle(hRead);
	return strOutput;
}

// You can see more details in MetadataReader.h file...
CString CMetadataReader::GetShutterCount(CString path) {
	CString result = NULL;
	CString command;
	CString fullCommand;

	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);

	CString strAppPath(szPath);
	int nSlash = strAppPath.ReverseFind(_T('\\'));
	CString strDir = strAppPath.Left(nSlash + 1);

	CString strExifTool = strDir + _T("exiftool\\exiftool.exe");

	//LPWSTR exePath = NULL;
	//GetModuleFileName(NULL, exePath, 256);
	command.Format(L" -t -shuttercount \"%s\"", path);
	fullCommand = strExifTool + command;

	result = this->ExecuteCmd(fullCommand);

	return result;
}

CString CMetadataReader::GetCameraModel(CString path) {
	CString result = NULL;
	CString command;
	CString fullCommand;

	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);

	CString strAppPath(szPath);
	int nSlash = strAppPath.ReverseFind(_T('\\'));
	CString strDir = strAppPath.Left(nSlash + 1);

	CString strExifTool = strDir + _T("exiftool\\exiftool.exe");

	//LPWSTR exePath = NULL;
	//GetModuleFileName(NULL, exePath, 256);
	command.Format(L" -model \"%s\"", path);
	fullCommand = strExifTool + command;

	result = this->ExecuteCmd(fullCommand);

	return result;
}

CString CMetadataReader::GetCameraModelWithoutLabel(CString path) {
	CString result = NULL;
	CString command;
	CString fullCommand;

	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);

	CString strAppPath(szPath);
	int nSlash = strAppPath.ReverseFind(_T('\\'));
	CString strDir = strAppPath.Left(nSlash + 1);

	CString strExifTool = strDir + _T("exiftool\\exiftool.exe");

	//LPWSTR exePath = NULL;
	//GetModuleFileName(NULL, exePath, 256);
	command.Format(L" -s -t -model \"%s\"", path);
	fullCommand = strExifTool + command;

	result = this->ExecuteCmd(fullCommand);

	return result;
}

CString CMetadataReader::GetAperture(CString path) {
	CString result = NULL;
	CString command;
	CString fullCommand;

	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);

	CString strAppPath(szPath);
	int nSlash = strAppPath.ReverseFind(_T('\\'));
	CString strDir = strAppPath.Left(nSlash + 1);

	CString strExifTool = strDir + _T("exiftool\\exiftool.exe");

	//LPWSTR exePath = NULL;
	//GetModuleFileName(NULL, exePath, 256);
	command.Format(L" -aperture \"%s\"", path);
	fullCommand = strExifTool + command;

	result = this->ExecuteCmd(fullCommand);

	return result;
}

CString CMetadataReader::GetShutterSpeed(CString path) {
	CString result = NULL;
	CString command;
	CString fullCommand;

	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);

	CString strAppPath(szPath);
	int nSlash = strAppPath.ReverseFind(_T('\\'));
	CString strDir = strAppPath.Left(nSlash + 1);

	CString strExifTool = strDir + _T("exiftool\\exiftool.exe");

	//LPWSTR exePath = NULL;
	//GetModuleFileName(NULL, exePath, 256);
	command.Format(L" -shutterspeed \"%s\"", path);
	fullCommand = strExifTool + command;

	result = this->ExecuteCmd(fullCommand);

	return result;
}

CString CMetadataReader::GetISO(CString path) {
	CString result = NULL;
	CString command;
	CString fullCommand;

	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);

	CString strAppPath(szPath);
	int nSlash = strAppPath.ReverseFind(_T('\\'));
	CString strDir = strAppPath.Left(nSlash + 1);

	CString strExifTool = strDir + _T("exiftool\\exiftool.exe");

	//LPWSTR exePath = NULL;
	//GetModuleFileName(NULL, exePath, 256);
	command.Format(L" -iso \"%s\"", path);
	fullCommand = strExifTool + command;

	result = this->ExecuteCmd(fullCommand);

	return result;
}

CString CMetadataReader::GetFocalLength(CString path) {
	CString result = NULL;
	CString command;
	CString fullCommand;

	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);

	CString strAppPath(szPath);
	int nSlash = strAppPath.ReverseFind(_T('\\'));
	CString strDir = strAppPath.Left(nSlash + 1);

	CString strExifTool = strDir + _T("exiftool\\exiftool.exe");

	//LPWSTR exePath = NULL;
	//GetModuleFileName(NULL, exePath, 256);
	command.Format(L" -focallength \"%s\"", path);
	fullCommand = strExifTool + command;

	result = this->ExecuteCmd(fullCommand);

	return result;
}

CString CMetadataReader::GetSize(CString path) {
	CString result = NULL;
	CString command;
	CString fullCommand;

	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);

	CString strAppPath(szPath);
	int nSlash = strAppPath.ReverseFind(_T('\\'));
	CString strDir = strAppPath.Left(nSlash + 1);

	CString strExifTool = strDir + _T("exiftool\\exiftool.exe");

	//LPWSTR exePath = NULL;
	//GetModuleFileName(NULL, exePath, 256);
	command.Format(L" -imagesize \"%s\"", path);
	fullCommand = strExifTool + command;

	result = this->ExecuteCmd(fullCommand);

	return result;
}


CString CMetadataReader::GetDate(CString path) {
	CString result = NULL;
	CString command;
	CString fullCommand;

	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);

	CString strAppPath(szPath);
	int nSlash = strAppPath.ReverseFind(_T('\\'));
	CString strDir = strAppPath.Left(nSlash + 1);

	CString strExifTool = strDir + _T("exiftool\\exiftool.exe");

	//LPWSTR exePath = NULL;
	//GetModuleFileName(NULL, exePath, 256);
	command.Format(L" -createdate \"%s\"", path);
	fullCommand = strExifTool + command;

	result = this->ExecuteCmd(fullCommand);

	return result;
}

