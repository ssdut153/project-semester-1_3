@ehco off
git add *
set INPUT=
set /P INPUT=ÇëÊäÈëcommitÄÚÈİ: %=%
if "%INPUT%"=="" goto emptyinput
goto validinput
:emptyinput
git commit -m "default"
:validinput
git commit -m "%INPUT%"
git push
pause
