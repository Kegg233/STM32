VERSION 5.00
Begin VB.Form SPWM 
   Caption         =   "SPWM数据生成软件(Howe.Chen)"
   ClientHeight    =   4560
   ClientLeft      =   120
   ClientTop       =   450
   ClientWidth     =   8310
   Icon            =   "SPWM.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   4560
   ScaleWidth      =   8310
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton Command1 
      Caption         =   "清空结果"
      Height          =   615
      Left            =   7320
      TabIndex        =   18
      Top             =   3600
      Width           =   855
   End
   Begin VB.TextBox Text7 
      Height          =   1695
      Left            =   240
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   17
      Top             =   2520
      Width           =   6855
   End
   Begin VB.TextBox Text4 
      Height          =   375
      Left            =   6720
      TabIndex        =   9
      Top             =   1560
      Width           =   975
   End
   Begin VB.Frame Frame1 
      Caption         =   "参数设置"
      Height          =   2055
      Left            =   360
      TabIndex        =   1
      Top             =   120
      Width           =   6015
      Begin VB.TextBox Text6 
         Height          =   390
         Left            =   1560
         TabIndex        =   16
         Top             =   1440
         Width           =   1455
      End
      Begin VB.TextBox Text5 
         Height          =   375
         Left            =   4320
         TabIndex        =   13
         Top             =   840
         Width           =   1335
      End
      Begin VB.TextBox Text3 
         Height          =   375
         Left            =   1560
         TabIndex        =   7
         Top             =   840
         Width           =   735
      End
      Begin VB.TextBox Text2 
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   12
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   4800
         TabIndex        =   6
         Top             =   240
         Width           =   855
      End
      Begin VB.TextBox Text1 
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   12
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   1080
         TabIndex        =   3
         Top             =   240
         Width           =   735
      End
      Begin VB.Label Label9 
         Caption         =   "调制度（M)"
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   12
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   15
         Top             =   1560
         Width           =   1335
      End
      Begin VB.Label Label8 
         Caption         =   "V"
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   12
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   5760
         TabIndex        =   14
         Top             =   960
         Width           =   255
      End
      Begin VB.Label Label7 
         Caption         =   "交流峰值电压(Vsin)"
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   12
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   2760
         TabIndex        =   12
         Top             =   840
         Width           =   1575
      End
      Begin VB.Label Label6 
         Caption         =   "V"
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   12
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   2400
         TabIndex        =   11
         Top             =   960
         Width           =   375
      End
      Begin VB.Label Label5 
         Caption         =   "直流BUS电压(Vbus)"
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   12
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   120
         TabIndex        =   10
         Top             =   840
         Width           =   1335
      End
      Begin VB.Label Label3 
         Caption         =   "半周期取样点数（N）"
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   12
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   2640
         TabIndex        =   5
         Top             =   360
         Width           =   2295
      End
      Begin VB.Label Label1 
         Caption         =   "频率(F)"
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   12
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   120
         TabIndex        =   4
         Top             =   360
         Width           =   855
      End
      Begin VB.Label Label2 
         Caption         =   "Hz"
         BeginProperty Font 
            Name            =   "宋体"
            Size            =   12
            Charset         =   134
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   1920
         TabIndex        =   2
         Top             =   360
         Width           =   375
      End
   End
   Begin VB.CommandButton CmdOutPut 
      Caption         =   "生成(CREATE)"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   12
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   6600
      TabIndex        =   0
      Top             =   240
      Width           =   1575
   End
   Begin VB.Label Label4 
      Caption         =   "PWM幅值"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   12
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   6720
      TabIndex        =   8
      Top             =   1200
      Width           =   1095
   End
End
Attribute VB_Name = "SPWM"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Freq As Double
Dim Vbus As Double
Dim Vsin As Double
Dim M As Double
Dim N As Double
Dim PwmPeriod As Double
Dim K As Double
Const PI As Double = 3.1415926
Dim Out() As Double
Dim SpwmOut() As Integer


Private Sub CmdOutPut_Click()
    On Error GoTo endsub
    Dim i As Double
    Dim w As Double
    Dim temp1 As Double
    Dim temp2 As Double
    w = Freq * 2 * PI
    
    temp1 = Cos(((1 - 1) * PI) / N)
    temp2 = Cos((1 * PI) / N)
    Out(1) = (M / w * (temp1 - temp2)) * 1000000
    
    For i = 2 To N Step 1
        temp1 = Cos(((i - 1) * PI) / N)
        temp2 = Cos((i * PI) / N)
        Out(i) = (M / w * (temp1 - temp2)) * 1000000 - Out(1)
    Next i
    Out(1) = 0
    
    For i = 1 To N Step 1
        SpwmOut(i) = CInt(PwmPeriod / (Out(N / 2 + 1)) * Out(i))
    Next i
    
    Text7.Text = ""
    For i = 1 To N / 2 Step 1
        Text7.Text = Text7.Text & "0x" & CStr(Hex(SpwmOut(i))) & ","
    Next i
    Text7.Text = Text7.Text & vbCrLf
    
    For i = N / 2 + 1 To N - 1 Step 1
        Text7.Text = Text7.Text & "0x" & CStr(Hex(SpwmOut(i))) & ","
    Next i
    Text7.Text = Text7.Text & "0x" & CStr(Hex(SpwmOut(N)))
Exit Sub
endsub:
    MsgBox "Error", vbOKOnly, Error
End Sub

Private Sub Command1_Click()
    Text7.Text = ""
End Sub

Private Sub Form_Load()
    Text1.Text = 50
    Text2.Text = 66
    Text3.Text = 380
    Text4.Text = 255
    Text5.Text = 311
End Sub

Private Sub Text1_Change()
    Freq = Val(Text1.Text)
End Sub

Private Sub Text2_Change()
    N = Val(Text2.Text)
    ReDim Out(N)
    ReDim SpwmOut(N)
End Sub

Private Sub Text3_Change()
    On Error Resume Next
    Vbus = Val(Text3.Text)
    M = Vsin / Vbus
    Text6.Text = CStr(M)
End Sub

Private Sub Text4_Change()
    PwmPeriod = Val(Text4.Text)
End Sub

Private Sub Text5_Change()
    On Error GoTo endsub
    If (Val(Text5.Text) > Vbus) Then
        MsgBox "Vsin must be below Vbus", vbOKOnly, "Error"
        Text5.Text = CStr(311)
    Else
        Vsin = Val(Text5.Text)
        M = Vsin / Vbus
        Text6.Text = CStr(CSng(M))
    End If
endsub:
End Sub

Private Sub Text6_Change()
    On Error GoTo endsub
    If (Val(Text6.Text) > 1) Then
        MsgBox "M must be Between 0 to 1", vbOKOnly, "Error"
        Text6.Text = CStr(0.818421052631579)
    Else
        M = Val(Text6.Text)
        Vsin = Vbus * M
        Text5.Text = CStr(CSng(Vsin))
    End If
endsub:
End Sub
