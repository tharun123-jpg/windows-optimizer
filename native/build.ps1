$ErrorActionPreference = 'Stop'

$sourceDir = $PSScriptRoot
$buildDir = Join-Path $sourceDir 'build'
$exePath = Join-Path $buildDir 'Release\THARU-OPTIMIZER.exe'

if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    Write-Error 'CMake was not found. Install Visual Studio 2022 with Desktop development with C++ and CMake support.'
    exit 1
}

Write-Host 'Configuring THARU OPTIMIZER (x64)...' -ForegroundColor Cyan
& cmake -S $sourceDir -B $buildDir -G 'Visual Studio 17 2022' -A x64
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Write-Host 'Building Release executable...' -ForegroundColor Cyan
& cmake --build $buildDir --config Release
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

if (-not (Test-Path $exePath)) {
    Write-Error "Build completed but executable was not found at $exePath"
    exit 1
}

Write-Host "Built: $exePath" -ForegroundColor Green
