#ifdef __cpp_lib_filesystem
#include <filesystem>
namespace fs = std::filesystem;
#elif __cpp_lib_experimental_filesystem
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1;
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif
////////// ^^^^ check if needed


#include "EthernetDriver.h"

namespace udp
{
	void EthernetDriver::closeSocket(SOCKET socket)
	{
		int error_code = closesocket(socket);
		if (error_code == SOCKET_ERROR)
		{
			std::cout << "Error - close socket function failed. Error:" << WSAGetLastError() << "\n";
			getchar();
			return;
		}
		WSACleanup();
	}
}