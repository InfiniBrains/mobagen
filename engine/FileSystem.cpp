#include "FileSystem.hpp"
#include "FileCustom.hpp"
#include "Logger.hpp"

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

namespace mobagen
{
  auto FileSystem::Exists(const char* path) -> bool
  {
    struct stat s {};
	if (stat(path, &s) == 0)
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

  auto FileSystem::Exists(std::string path) -> bool
  {
	return Exists(path.c_str());
  }

  auto FileSystem::ComparePaths(const char* one, const char* second) -> bool
  {
	return strcmp(one, second) == 0;
  }

  auto FileSystem::ComparePaths(const std::string& one, const std::string& second) -> bool
  {
	  return one == second;
  }

  auto FileSystem::GetPathSeparator() -> char
  {
#if defined(_WIN32) || defined(_WIN64)
	  return '\\';
#else
	  return '/';
#endif
  }

  auto FileSystem::ListDirectory(const std::string& path) -> std::vector<std::string>
  {
	  return ListDirectory(path.c_str());
  }

  auto FileSystem::ListDirectory(const char* path) -> std::vector<std::string>
  {
	std::vector<std::string> contents;

    if(!IsDirectory(path))
    {
	  log_err("Path is not a directory: %s", path);
	  return contents;
    }

	const auto dir = opendir(path);
	struct dirent * dp;
	while ((dp = readdir(dir)) != nullptr)
	  contents.emplace_back(dp->d_name);
	closedir(dir);

	return contents;
  }

  auto FileSystem::IsFile(const char* path) -> bool
  {
	struct stat s {};
	if (stat(path, &s) == 0)
	  return (s.st_mode & S_IFREG) != 0;
	return false;
  }

  auto FileSystem::IsFile(const std::string& path) -> bool
  {
    return IsFile(path.c_str());
  }

  auto FileSystem::IsDirectory(const char* path) -> bool
  {
	struct stat s{};
	if (stat(path, &s) == 0)
	  return (s.st_mode & S_IFDIR) != 0;	
	return false;
  }

  auto FileSystem::IsDirectory(const std::string& path) -> bool
  {
	return IsDirectory(path.c_str());
  }

  auto FileSystem::Open(const char* path, const char* mode) -> Assimp::IOStream*
  {
    if(IsFile(path))
	  return new mobagen::FileCustom(path, mode);
	return nullptr;
  }

  auto FileSystem::Open(const std::string& path, const char* pMode) -> Assimp::IOStream*
  {
	return Open(path.c_str(), pMode);
  }
}
