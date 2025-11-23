# .sys File Builder Project

This project is designed to build `.sys` files. It has been tested and works with:

- **llvm-mvsc** (a fork of LLVM)
- The official **MSVC** toolchain from Microsoft

While **pure LLVM** (not llvm-mvsc) was also tested, it produced incorrect `.sys` files due to issues with the header.

## Features

- **Portability**: This project is made to be portable and requires minimal setup.
- **Automated Certificate Creation & Signing**: The `CMakeLists.txt` automates certificate creation and signing for smooth use.
  - Signing is handled by the `create_certificate.ps1` script and an included `signtool`.
  - The `signtool.exe` is copied from the official SDK and renamed to `signtool_amd64.exe`.
  
### Why Sign the .sys File?

Windows requires `.sys` files to be signed even if **test-signing** mode is enabled. Without signing, Windows will refuse to load the driver. However, if you are using **kdmapper**, you do not need to sign the `.sys` file. In that case, the `driver.c` file may require a small edit.

## Setup Instructions

### 1. With MSVC & WDK Installed

If you have **MSVC** and the **WDK** installed, this project should just work.

### 2. With llvm-mvsc

If you want to use **llvm-mvsc**, download it from [backengineering's GitHub](https://github.com/backengineering/llvm-mvsc). You can check the `llvm-mvsc-clion-settings.png` for configuration guidance.

## CMD Configuration

Before building the driver, set the following in `cmd.exe`:

```bash
bcdedit /set nointegritychecks on
bcdedit /set testsigning on
bcdedit /set debug on  # (if you want to see DbgPrint output)
shutdown /r /t 0  # Restart the system
