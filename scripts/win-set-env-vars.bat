:: Check privileges
net file 1>NUL 2>NUL
if not '%errorlevel%' == '0' (
    powershell Start-Process -FilePath "%0" -ArgumentList "%cd%" -verb runas >NUL 2>&1
    exit /b
)

:: Change directory with passed argument. Processes started with
:: "runas" start with forced C:\Windows\System32 workdir
cd /d %1

cd ..\external\emsdk\
cmd /c emsdk.bat install latest
timeout 3

cmd /c emsdk.bat activate latest --system
echo "restarting"
timeout 10

shutdown /r