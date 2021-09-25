' Get command-line arguments.
Set objArgs = WScript.Arguments
Set FS = CreateObject("Scripting.FileSystemObject")
InputFolder = FS.GetAbsolutePathName(objArgs(0))
ZipFile = FS.GetAbsolutePathName(objArgs(1))

' Create an empty ZIP file.
CreateObject("Scripting.FileSystemObject").CreateTextFile(ZipFile, True).Write "PK" & Chr(5) & Chr(6) & String(18, vbNullChar)

Set objShell = CreateObject("Shell.Application")

Set source = objShell.NameSpace(InputFolder).Items

objShell.NameSpace(ZipFile).CopyHere(source)

' Required to let the ZIP command execute
' If this script randomly fails or the ZIP file is not complete,
' just increase to more than 2 seconds
wScript.Sleep 2000