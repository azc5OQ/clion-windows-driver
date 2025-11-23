This is project that builds .sys file
It was tested and works with llvm-mvsc (fork of llvm) and official mvsc toolchain from microsoft.
pure llvm (not llvm-mvsc) was tried too, but it produced wrong .sys file, something wrong with their header.

This project is made to be portable and requires minimal setup.
CMakeLists.txt automates cert creation and signing of sys file for smooth use.
That is achieved with create_ceritificate.ps1 script and included signtool.
The signtool.exe was copied from official sdk and renamed to signtool_amd64.exe.
Why signing of .sys file ? because windows requires .sys file to be signed even if testsign mode is enabled. Or it will refuse to load the driver.
If you use kdmapper, you dont need to sign the .sys file. In that case the driver.c also needs small editing.


What to do:
if you have MSVC and WDK installed, it will just work.
if you want to get llvm-mvsc working, download it from backengineering github.
Check llvm-mvsc-clion-settings.png if you want to use llvm-mvsc

These things must be set in cmd.exe

bcdedit /set nointegritychecks on
bcdedit /set testsigning on
bcdedit /set debug on  -> (if you want to see output of DbgPrint)

and restart
shutdown /r /t 0


how to test?

run DebugView as admin, ensure its connected to local pc
enable verbose kernel output in debug print, set filter in debug print

Drivers dont need any aditional files to acompant them like .inf or .cat


.sys files are started as services using the "sc" command line tool

run following commands if you are build the driver, exact location of binPath depends on your location
sc create testdriver binPath= "C:/users/user/Desktop/sample-driver.sys" type= kernel
sc start testdriver
sc stop testdriver

for checking the driver status
sc query testdriver


if this project helped you, please give it a star!

also thanks to 
This is project that builds .sys file
It was tested and works with llvm-mvsc (fork of llvm) and official mvsc toolchain from microsoft.
pure llvm (not llvm-mvsc) was tried too, but it produced wrong .sys file, something wrong with their header.

This project is made to be portable and requires minimal setup.
CMakeLists.txt automates cert creation and signing of sys file for smooth use.
That is achieved with create_ceritificate.ps1 script and included signtool.
The signtool.exe was copied from official sdk and renamed to signtool_amd64.exe.
Why signing of .sys file ? because windows requires .sys file to be signed even if testsign mode is enabled. Or it will refuse to load the driver.
If you use kdmapper, you dont need to sign the .sys file. In that case the driver.c also needs small editing.


What to do:
if you have MSVC and WDK installed, it will just work.
if you want to get llvm-mvsc working, download it from backengineering github.
Check llvm-mvsc-clion-settings.png if you want to use llvm-mvsc

These things must be set in cmd.exe

bcdedit /set nointegritychecks on
bcdedit /set testsigning on
bcdedit /set debug on  -> (if you want to see output of DbgPrint)

and restart
shutdown /r /t 0


how to test?

run DebugView as admin, ensure its connected to local pc
enable verbose kernel output in debug print, set filter in debug print

Drivers dont need any aditional files to acompant them like .inf or .cat


.sys files are started as services using the "sc" command line tool

run following commands if you are build the driver, exact location of binPath depends on your location
sc create testdriver binPath= "C:/users/user/Desktop/sample-driver.sys" type= kernel
sc start testdriver
sc stop testdriver

for checking the driver status
sc query testdriver

if this project helped you, please give it a star!

also thanks to 
https://github.com/SergiusTheBest/FindWDK
for making FindWDK script that this project uses
