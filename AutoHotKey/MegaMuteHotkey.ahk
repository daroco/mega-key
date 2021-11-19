#SingleInstance, force
#NoEnv 

^+!;::

SendMode Input 
SetWorkingDir %A_ScriptDir%  

device_id := 2 ; This was my device ID for input

Soundset, +1, MASTER, Mute, %device_id%
SoundGet, master_mute, , mute, %device_id%

ToolTip, Mute %master_mute%
SetTimer, RemoveToolTip, 2000
return

RemoveToolTip:
SetTimer, RemoveToolTip, Off
ToolTip
return