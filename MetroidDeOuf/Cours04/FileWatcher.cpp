#include "stdafx.hpp"
#include "FileWatcher.hpp"

FileWatcher::FileWatcher(const char* _filePath)
{
	this->filePath = _filePath;
	init = false;
}

FileWatcher::~FileWatcher()
{
}

bool FileWatcher::checkFileModification(float dt)
{
	checktimer -= dt;
	if (checktimer <= 0)
	{
		checktimer = checkCD;
		struct stat result;
		if (stat(filePath, &result) == 0)
		{
			if (!init)
			{
				init = true;
				lastChangedFile = result.st_mtime;
			}
			else if (lastChangedFile < result.st_mtime)
			{
				printf("The file has been changed, reloading \n");
				lastChangedFile = result.st_mtime;
				return true;
			}
		}
	}
		return false;
}