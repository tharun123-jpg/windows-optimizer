# THARU OPTIMIZER Native (C++ / Win32)

This is the native Windows desktop shell for the THARU OPTIMIZER preview. It uses the Windows SDK and GDI only; there are no third-party runtime dependencies.

## Build on Windows

Install Visual Studio 2022 with **Desktop development with C++** and CMake support, then open `native/CMakeLists.txt` in Visual Studio, or build from a Developer PowerShell:

```powershell
cmake -S native -B native/build -G "Visual Studio 17 2022" -A x64
cmake --build native/build --config Release
.\native\build\Release\THARU-OPTIMIZER.exe
```

The same CMake project can be configured with a MinGW-w64 toolchain. For Visual Studio 2022, you can also run `powershell -ExecutionPolicy Bypass -File .\native\build.ps1` from the repository root. The source targets Windows 10 or later.

### GitHub download

The `Build Windows executable` workflow compiles this app on a Windows runner whenever native sources change on the Arena branch, then uploads `THARU-OPTIMIZER-windows-x64` as a downloadable Actions artifact. Artifacts are retained for 30 days. Open the workflow run under **Actions** and download the artifact. This preview build is unsigned and all optimizer actions remain preview-only.

## What the native shell reads

- CPU utilization, sampled locally using `GetSystemTimes`.
- Installed and available RAM using `GlobalMemoryStatusEx`.
- C: drive capacity and available space using `GetDiskFreeSpaceExW`.
- CPU model from the local Windows hardware-description registry key (read-only).
- Display adapter name from `EnumDisplayDevicesW`.

These values stay on the PC. The app does not send telemetry or collect an HWID.

## Preview-only actions

The Cleaner, gaming switches, Minecraft recommendations, Network, Startup, Services, Privacy, Debloat, Repair, and Restore views are UI demonstrations. They do **not** delete files, change registry keys or startup entries, disable services, edit network settings, uninstall apps, run PowerShell/SFC/DISM/CHKDSK, change process priority, or create a Windows restore point. Buttons state this in the UI or a confirmation message. Network tests are simulated and send no packets.

This separation is intentional: before adding any system-changing feature, implement a signed, narrowly scoped Windows integration with explicit consent, verified restore points/backups, measured before/after results, and a tested undo path. BIOS flashing and automatic overclocking are out of scope.
