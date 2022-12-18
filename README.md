# TailViewerUDP
Windows service of UDP server that receives messages and puts them in file.

## Before start using the app:
### Create log file for the server. Contains the server's ip in the first row, and the server's port in the secod.
1. Create new folder named "logs" in C:\\.
2. Create new folder named "config" in C:\\logs.
3. Create new file named "config.cfg" in C:\\logs\config.
4. Write the server ip in the first line of the file "config.cfg".
5. Write the server port in the second line of the file "config.cfg".
6. Save changes.

## Using the app:
### You can run it as a regular process, or as a Windows service:
## Install as Windows service:
##### Part A:
1. Compile files in release.
2. Open cmd as administrator.
3. Write cd -> folder (C:\Users\USERNAME\source\repos\TailVeiwerUDP\x64\Release).
4. Write tailviewer-service.exe install.
5. Click Enter.

#### NOTE: After installation the service **is not running**. We have to start it manually. See part B:
##### Part B:
Starting the service:

1. Click on Windows, write Services -> open as administrator.
2. Search on the list for the service name "TailViewer Server service".
3. Double click -> Log On -> choose "Local System account" + "Allow service to interact with desktop".
4. Click OK.
5. Start the service by clicking on it and click Start on the left.


## Run as regular process (non-service):
1. Open cmd as administrator.
2. Write cd -> folder (C:\Users\USERNAME\source\repos\TailVeiwerUDP\x64\Release).
3. Write tailviewer-service.exe run.
4. Click Enter.

## Remove installed service:
1. Open cmd as administrator.
2. Write cd -> folder (C:\Users\USERNAME\source\repos\TailVeiwerUDP\x64\Release).
3. Write tailviewer-service.exe uninstall.
4. Click Enter.

## Debug in Visual Studio:
In case you want to debug the code in Visual Studio, you can add the arguments (install/uninstall/run...)
in the properties:
1. Right-click the project tailviewer-service.
2. Choose Properties.
3. Go to the Debugging section. 
4. There is a box for "Command Arguments", add requested argument (install/uninstall/run...).

### In case of error:
* In case of LNK2001 error, you might need to go to project properties -> Linker -> Input -> Additional Dependencies -> add: <Ws2_32.lib>.
* In case of error "filesystem is not in library std", go to project properties -> C/C++ -> Language -> C++ Language Standard -> change to "C++ 17 Strandard" or higher version. 
