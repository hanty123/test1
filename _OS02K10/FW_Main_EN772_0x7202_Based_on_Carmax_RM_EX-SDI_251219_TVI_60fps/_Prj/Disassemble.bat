@echo off
path = C:\eyenix\cygwin\bin;%PATH%
make dis
echo.
WordDetection "output\EN779.dis" ".ispm_text" 0
pause