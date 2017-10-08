
#2010_10_26_ add by greshem
Dim lbl As String, sPath As String, boot As String, sTime As String, _
FName As String, UseLong As String, ByteCmp As String, isUCase As String, _
Trans As String
        lbl = " -l" & T(1)
        sPath = " " & Chr(34) & T(2) & Chr(34)
        FName = " " & T(5)
        If T(3) <> "" Then boot = " -b" & T(3): FileCopy T(3), T(2) Else boot = ""
        If Check1.Value = 1 Then sTime = " -t" & T(4) Else sTime = ""
        If Check2.Value = 1 Then UseLong = " -n" Else UseLong = ""
        If Check3.Value = 1 Then Trans = " -oc" Else Trans = "-o"
        If Check4.Value = 1 Then isUCase = " -d" Else UseLong = ""
    Shell App.path & "\cdimage.exe -m" & lbl & boot & sTime & UseLong & Trans & _
        isUCase & sPath & FName
End Sub
cdimage.exe 核心用法注意了
