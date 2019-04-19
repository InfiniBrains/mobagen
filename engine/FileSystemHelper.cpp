#include "FileSystemHelper.hpp"
#include "FileCustom.hpp"


#if !defined(_WIN32) && !defined(_WIN64) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
/* UNIX-style OS. ------------------------------------------- */
#include <unistd.h>
#if defined(_POSIX_VERSION)
/* POSIX compliant */
#include <sys/types.h>
#include <sys/dir.h>
#endif
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#include "direntwin.h"
#endif

namespace mobagen {
  FileSystemHelper::FileSystemHelper(void) {}

  FileSystemHelper::~FileSystemHelper(void) {}

  bool FileSystemHelper::Exists(const char* pFile) const
  {
	struct stat s {};
	if (stat(pFile, &s) == 0)
	{
	  if (s.st_mode & S_IFDIR)
		return true; // dir
	  else if (s.st_mode & S_IFREG)
	    return true; // file
	  else
		return false; //something else
	}
	else
	  return false;
  }

  // TODO: check if compare of path with "../" are the same 
  bool FileSystemHelper::ComparePaths(const char *one, const char *second) const {
    return strcmp(one, second) == 0;
  }

  char FileSystemHelper::getOsSeparator() const
  {
#if defined(_WIN32) || defined(_WIN64)
	return '\\';
#else
	return '/';
#endif
  }

  std::vector<std::string> FileSystemHelper::ListDirectory(std::string path)
  {
	  std::vector<std::string> contents;

	  const auto dir = opendir(path.c_str());
	  struct dirent * dp;
	  while ((dp = readdir(dir)) != nullptr)
		  contents.emplace_back(dp->d_name);
	  closedir(dir);

	  return contents;
  }


  Assimp::IOStream *FileSystemHelper::Open(const char *pFile, const char *pMode) {
    return new FileCustom(pFile, pMode);
  }

  void FileSystemHelper::Close(Assimp::IOStream *pFile) {
    delete pFile;
  }

  bool FileSystemHelper::IsDirectory(std::string path) {
    struct stat s;
    if( stat(path.c_str(),&s) == 0 )
    {
      if( s.st_mode & S_IFDIR )
        return true; // dir
//      else if( s.st_mode & S_IFREG )
//        return false; // file
      else
        return false; //something else
    }
    else
      return false;
  }
}