!ifndef WELCOMEANDFINISHPAGE_LAYOUTUI
	!define WELCOMEANDFINISHPAGE_LAYOUTUI `��ӭ�������ɽ���UI����`

!verbose push
!verbose 3

!define HWND_TOP       0
!define SWP_NOSIZE     1
!define SWP_NOMOVE     2
!define SWP_SHOWWINDOW 64

; ԭ��title�ؼ�����������:180 15 473 57
!define ORIGIN_X    180 ; ����ԭ���x
!define ORIGIN_Y    10  ; ����ԭ���y
!define VSPACE      10  ; ��ֱ�����ϵļ��
!define WIDTH       300 ; ���пؼ��Ŀ�� 

!define WELPAGE_TITLE_X         ${ORIGIN_X}	; ��ӭ����title��x
!define WELPAGE_TITLE_Y         ${ORIGIN_Y}	; ��ӭ����title��y
!define WELPAGE_TITLE_HEIGHT    55          ; ��ӭ����title�ĸ߶�
!define /math WELPAGE_TITLE_BOTTOM  ${WELPAGE_TITLE_Y} + ${WELPAGE_TITLE_HEIGHT} ; ��ӭ����title bottomֵ

!define WELPAGE_TEXT_X        ${WELPAGE_TITLE_X}                   ; ��ӭ����text��x
!define /math WELPAGE_TEXT_Y  ${WELPAGE_TITLE_BOTTOM} + ${VSPACE}  ; ��ӭ����text��y
!define WELPAGE_TEXT_HEIGHT   150                                  ; ��ӭ����text�ĸ߶�


!define FINISHPAGE_TITLE_X       ${ORIGIN_X}              ; ��ɽ���title��x
!define FINISHPAGE_TITLE_Y       ${ORIGIN_Y}              ; ��ɽ���title��y
!define FINISHPAGE_TITLE_HEIGHT  ${WELPAGE_TITLE_HEIGHT}  ; ��ɽ���title�ĸ߶�
!define /math FINISHPAGE_TITLE_BOTTOM  ${FINISHPAGE_TITLE_Y} + ${FINISHPAGE_TITLE_HEIGHT} ; ��ɽ���title bottomֵ

!define FINISHPAGE_TEXT_X        ${FINISHPAGE_TITLE_X}                  ; ��ɽ���text��x
!define /math FINISHPAGE_TEXT_Y  ${FINISHPAGE_TITLE_BOTTOM} + ${VSPACE} ; ��ɽ���text��y
!define FINISHPAGE_TEXT_HEIGHT   45                                     ; ��ɽ���text�ĸ߶�
!define /math FINISHPAGE_TEXT_BOTTOM  ${FINISHPAGE_TEXT_Y} + ${FINISHPAGE_TEXT_HEIGHT} ; ��ɽ���text bottomֵ

!define FINISHPAGE_CHECKBOX_X        ${FINISHPAGE_TEXT_X}                   ; ��ɽ���checkbox��x
!define /math FINISHPAGE_CHECKBOX_Y  ${FINISHPAGE_TEXT_BOTTOM} + ${VSPACE}  ; ��ɽ���checkbox��y
!define FINISHPAGE_CHECKBOX_HEIGHT   40                                     ; ��ɽ���checkbox�ĸ߶�

!undef WELPAGE_TITLE_BOTTOM
!undef FINISHPAGE_TITLE_BOTTOM
!undef FINISHPAGE_TEXT_BOTTOM

!define WelcomePage_LayoutUI `!insertmacro WelcomePage_LayoutUI`
!macro WelcomePage_LayoutUI
	
	GetDlgItem $MUI_TEMP1 $MUI_HWND 1201 ; ����
	System::Call "user32::SetWindowPos(i $MUI_TEMP1, i ${HWND_TOP},i ${WELPAGE_TITLE_X}, i ${WELPAGE_TITLE_Y}, i ${WIDTH}, i ${WELPAGE_TITLE_HEIGHT}, i ${SWP_SHOWWINDOW})"

	GetDlgItem $MUI_TEMP1 $MUI_HWND 1202 ; ����
	System::Call "user32::SetWindowPos(i $MUI_TEMP1, i ${HWND_TOP},i ${WELPAGE_TEXT_X}, i ${WELPAGE_TEXT_Y}, i ${WIDTH}, i ${WELPAGE_TEXT_HEIGHT}, i ${SWP_SHOWWINDOW})"
!macroend

!define FinishPage_LayoutUI `!insertmacro FinishPage_LayoutUI`
!macro FinishPage_LayoutUI
	GetDlgItem $MUI_TEMP1 $MUI_HWND 1201 ; ����
	System::Call "user32::SetWindowPos(i $MUI_TEMP1, i ${HWND_TOP},i ${FINISHPAGE_TITLE_X}, i ${FINISHPAGE_TITLE_Y}, i ${WIDTH}, i ${FINISHPAGE_TITLE_HEIGHT}, i ${SWP_SHOWWINDOW})"

	GetDlgItem $MUI_TEMP1 $MUI_HWND 1202 ; ����
	System::Call "user32::SetWindowPos(i $MUI_TEMP1, i ${HWND_TOP},i ${FINISHPAGE_TEXT_X}, i ${FINISHPAGE_TEXT_Y}, i ${WIDTH}, i ${FINISHPAGE_TEXT_HEIGHT}, i ${SWP_SHOWWINDOW})"

	GetDlgItem $MUI_TEMP1 $MUI_HWND 1203 ; checkBox�ؼ�
	System::Call "user32::SetWindowPos(i $MUI_TEMP1, i ${HWND_TOP},i ${FINISHPAGE_CHECKBOX_X}, i ${FINISHPAGE_CHECKBOX_Y}, i ${WIDTH}, i ${FINISHPAGE_CHECKBOX_HEIGHT}, i ${SWP_SHOWWINDOW})"
!macroend

!verbose pop
!endif ;end of WELCOMEANDFINISHPAGE_LAYOUTUI define


