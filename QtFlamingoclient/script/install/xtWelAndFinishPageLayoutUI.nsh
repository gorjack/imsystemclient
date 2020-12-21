!ifndef WELCOMEANDFINISHPAGE_LAYOUTUI
	!define WELCOMEANDFINISHPAGE_LAYOUTUI `欢迎界面和完成界面UI布局`

!verbose push
!verbose 3

!define HWND_TOP       0
!define SWP_NOSIZE     1
!define SWP_NOMOVE     2
!define SWP_SHOWWINDOW 64

; 原来title控件的左上右下:180 15 473 57
!define ORIGIN_X    180 ; 坐标原点的x
!define ORIGIN_Y    10  ; 坐标原点的y
!define VSPACE      10  ; 垂直方向上的间距
!define WIDTH       300 ; 所有控件的宽度 

!define WELPAGE_TITLE_X         ${ORIGIN_X}	; 欢迎界面title的x
!define WELPAGE_TITLE_Y         ${ORIGIN_Y}	; 欢迎界面title的y
!define WELPAGE_TITLE_HEIGHT    55          ; 欢迎界面title的高度
!define /math WELPAGE_TITLE_BOTTOM  ${WELPAGE_TITLE_Y} + ${WELPAGE_TITLE_HEIGHT} ; 欢迎界面title bottom值

!define WELPAGE_TEXT_X        ${WELPAGE_TITLE_X}                   ; 欢迎界面text的x
!define /math WELPAGE_TEXT_Y  ${WELPAGE_TITLE_BOTTOM} + ${VSPACE}  ; 欢迎界面text的y
!define WELPAGE_TEXT_HEIGHT   150                                  ; 欢迎界面text的高度


!define FINISHPAGE_TITLE_X       ${ORIGIN_X}              ; 完成界面title的x
!define FINISHPAGE_TITLE_Y       ${ORIGIN_Y}              ; 完成界面title的y
!define FINISHPAGE_TITLE_HEIGHT  ${WELPAGE_TITLE_HEIGHT}  ; 完成界面title的高度
!define /math FINISHPAGE_TITLE_BOTTOM  ${FINISHPAGE_TITLE_Y} + ${FINISHPAGE_TITLE_HEIGHT} ; 完成界面title bottom值

!define FINISHPAGE_TEXT_X        ${FINISHPAGE_TITLE_X}                  ; 完成界面text的x
!define /math FINISHPAGE_TEXT_Y  ${FINISHPAGE_TITLE_BOTTOM} + ${VSPACE} ; 完成界面text的y
!define FINISHPAGE_TEXT_HEIGHT   45                                     ; 完成界面text的高度
!define /math FINISHPAGE_TEXT_BOTTOM  ${FINISHPAGE_TEXT_Y} + ${FINISHPAGE_TEXT_HEIGHT} ; 完成界面text bottom值

!define FINISHPAGE_CHECKBOX_X        ${FINISHPAGE_TEXT_X}                   ; 完成界面checkbox的x
!define /math FINISHPAGE_CHECKBOX_Y  ${FINISHPAGE_TEXT_BOTTOM} + ${VSPACE}  ; 完成界面checkbox的y
!define FINISHPAGE_CHECKBOX_HEIGHT   40                                     ; 完成界面checkbox的高度

!undef WELPAGE_TITLE_BOTTOM
!undef FINISHPAGE_TITLE_BOTTOM
!undef FINISHPAGE_TEXT_BOTTOM

!define WelcomePage_LayoutUI `!insertmacro WelcomePage_LayoutUI`
!macro WelcomePage_LayoutUI
	
	GetDlgItem $MUI_TEMP1 $MUI_HWND 1201 ; 标题
	System::Call "user32::SetWindowPos(i $MUI_TEMP1, i ${HWND_TOP},i ${WELPAGE_TITLE_X}, i ${WELPAGE_TITLE_Y}, i ${WIDTH}, i ${WELPAGE_TITLE_HEIGHT}, i ${SWP_SHOWWINDOW})"

	GetDlgItem $MUI_TEMP1 $MUI_HWND 1202 ; 文字
	System::Call "user32::SetWindowPos(i $MUI_TEMP1, i ${HWND_TOP},i ${WELPAGE_TEXT_X}, i ${WELPAGE_TEXT_Y}, i ${WIDTH}, i ${WELPAGE_TEXT_HEIGHT}, i ${SWP_SHOWWINDOW})"
!macroend

!define FinishPage_LayoutUI `!insertmacro FinishPage_LayoutUI`
!macro FinishPage_LayoutUI
	GetDlgItem $MUI_TEMP1 $MUI_HWND 1201 ; 标题
	System::Call "user32::SetWindowPos(i $MUI_TEMP1, i ${HWND_TOP},i ${FINISHPAGE_TITLE_X}, i ${FINISHPAGE_TITLE_Y}, i ${WIDTH}, i ${FINISHPAGE_TITLE_HEIGHT}, i ${SWP_SHOWWINDOW})"

	GetDlgItem $MUI_TEMP1 $MUI_HWND 1202 ; 文字
	System::Call "user32::SetWindowPos(i $MUI_TEMP1, i ${HWND_TOP},i ${FINISHPAGE_TEXT_X}, i ${FINISHPAGE_TEXT_Y}, i ${WIDTH}, i ${FINISHPAGE_TEXT_HEIGHT}, i ${SWP_SHOWWINDOW})"

	GetDlgItem $MUI_TEMP1 $MUI_HWND 1203 ; checkBox控件
	System::Call "user32::SetWindowPos(i $MUI_TEMP1, i ${HWND_TOP},i ${FINISHPAGE_CHECKBOX_X}, i ${FINISHPAGE_CHECKBOX_Y}, i ${WIDTH}, i ${FINISHPAGE_CHECKBOX_HEIGHT}, i ${SWP_SHOWWINDOW})"
!macroend

!verbose pop
!endif ;end of WELCOMEANDFINISHPAGE_LAYOUTUI define


