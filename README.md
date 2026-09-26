# THARU OPTIMIZER — Windows + Minecraft prototype

A safety-first optimizer concept for older gaming PCs (example target: Core i5-7500, GeForce GTX 1050 Ti, 16 GB RAM). This repository now includes a responsive browser preview and a native C++ Win32 desktop shell.

## Native Windows app (C++)

Open `native/CMakeLists.txt` in Visual Studio 2022, or build from a Developer PowerShell with the **Desktop development with C++** workload and CMake support:

```powershell
cmake -S native -B native/build -G "Visual Studio 17 2022" -A x64
cmake --build native/build --config Release
.\native\build\Release\THARU-OPTIMIZER.exe
```

The native shell targets Windows 10+ and uses built-in Win32 / GDI APIs. It reads CPU utilization, RAM usage, C: drive space, CPU model, and display-adapter name locally. On Windows, `native/build.ps1` builds the Release `.exe`; the GitHub Actions workflow also uploads a Windows x64 build artifact when native files change. See [`native/README.md`](native/README.md) for details.

## Browser preview

Requires Node.js 18 or newer; no npm install is required.

```bash
npm run dev
```

Open `http://localhost:4173`. To use another port, set `PORT`, for example `PORT=5000 npm run dev`.

The browser preview includes the dashboard, Cleaner categories, gaming profiles, Minecraft Java/RAM recommendations, Network, CPU/GPU/BIOS Advisor, Startup, Services, Privacy, Debloat, Repair, Restore Center, and Settings. Its device values are sample data.

## Safety and current limits

This is a prototype, **not yet a functioning Windows optimizer**. Native CPU/memory/disk/device-name readings are local and read-only. Cleaner estimates, launcher detection, network tests, startup/service states, privacy and debloat controls, repair progress, and restore flows are demonstrations. The app does **not** delete files, edit the registry or startup entries, disable services, change network settings, uninstall apps, run PowerShell/SFC/DISM/CHKDSK, change process priority, or create a Windows System Restore point. Network tests in the C++ preview send no packets. A preview snapshot is not a backup or a real restore point.

The interface intentionally excludes automatic BIOS flashing, overclocking, bulk app removal, and blind TCP registry tuning. Before adding system-changing features, build a signed, narrowly scoped Windows integration with explicit consent, clear UAC prompts, verified restore points and backups, measured before/after results, and a tested undo path. Licensing, secure updates, crash reporting, and HWID binding are not implemented; avoid unnecessary device fingerprinting in any future service.

The browser app does not call a backend or collect telemetry. Its optional **Search** button in Startup Manager opens Google only after the user clicks it. Browser-exported JSON contains preview preferences only, not registry data or a system backup.
