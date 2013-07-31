cd c:\epics
call config_env
start cmd "/s /k cd c:\epics && config_env.bat && C:\EPICS\ISIS\StartupConfig\StartupConfigMonitor.py"
C:/EPICS/ISIS/StartupConfig/bin/windows-x64/StartupConfig.exe
cd c:\EPICS\support\procServControl\1-2\iocs\isis_example\iocBoot\iocisis_example
C:\EPICS\support\procServControl\1-2\iocs\isis_example\bin\windows-x64\isis_example.exe st.cmd
