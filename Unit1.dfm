object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 441
  ClientWidth = 548
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  PixelsPerInch = 96
  TextHeight = 15
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 3
    Height = 15
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 8
    Top = 56
    Width = 297
    Height = 321
    Header.AutoSizeIndex = -1
    TabOrder = 0
    OnAddToSelection = VirtualStringTree1AddToSelection
    OnGetText = VirtualStringTree1GetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = 'Id'
      end
      item
        Position = 1
        Text = 'Sign'
      end>
  end
  object Memo1: TMemo
    Left = 355
    Top = 208
    Width = 185
    Height = 169
    Lines.Strings = (
      '')
    ReadOnly = True
    TabOrder = 1
  end
  object Edit1: TEdit
    Left = 352
    Top = 57
    Width = 75
    Height = 23
    TabOrder = 2
    Text = '//./C:'
  end
  object Button1: TButton
    Left = 462
    Top = 56
    Width = 75
    Height = 25
    Caption = 'Search'
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button3: TButton
    Left = 352
    Top = 97
    Width = 185
    Height = 25
    Caption = 'Stop Search'
    Enabled = False
    TabOrder = 4
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 24
    Top = 29
    Width = 75
    Height = 25
    Caption = 'Delete'
    Enabled = False
    TabOrder = 5
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 216
    Top = 29
    Width = 75
    Height = 25
    Caption = 'Clear'
    Enabled = False
    TabOrder = 6
    OnClick = Button5Click
  end
  object CheckBox1: TCheckBox
    Left = 352
    Top = 152
    Width = 97
    Height = 17
    Caption = 'Ignore empty'
    TabOrder = 7
  end
end
