;--------------------------------
; xtclient Setup NSIS Script
; @author zoubailiu
; @date   2012-5-7
;
; �÷���
; makensis.exe [/DPLATFORM_NAME=x64] [/DCONFIGURATION_NAME=Release] [/DPRODUCT_NAME_CN=ѸͶ�����ն�] [/DPRODUCT_NAME_EN=XtTradeClient] [/DPRODUCT_VERSION=x.x.x.xxxx] [/DORIGINAL_FILENAME=xxx.exe] [/DOUTFILE=c:\xxx.exe] xxx.nsi
;

!include "LogicLib.nsh"
!include "xtWelAndFinishPageLayoutUI.nsh"

; ��װ�����ʼ���峣��

!ifndef PRODUCT_NAME_CN
    !define PRODUCT_NAME_CN "PBConfigTools������"
!endif

!ifndef PLATFORM_NAME
    !define PLATFORM_NAME "Win32"
!endif

!ifndef CONFIGURATION_NAME
    !define CONFIGURATION_NAME "Debug"
!endif

!ifndef PRODUCT_NAME_EN
    !define PRODUCT_NAME_EN "PBConfigTools"
!endif

!ifndef PRODUCT_VERSION
    !define PRODUCT_VERSION "1.0.0.0000"
!endif

!ifndef OUTFILE
    !define OUTFILE "D:\\pack\\QtFlamingo_${PRODUCT_VERSION}.exe"
!endif

!ifndef ORIGINAL_FILENAME
    !define ORIGINAL_FILENAME "${OUTFILE}"
!endif

!ifndef PACKER_PYTHON
    !define PACKER_PYTHON "True"
!endif

!ifndef INCREMENT_XTUPDATER
    !define INCREMENT_XTUPDATER "True"
!endif

!define PRODUCT_MAIN_EXE "${PRODUCT_NAME_EN}.exe"
!define PRODUCT_PUBLISHER "��������ڿƿع����޹�˾"
!define PRODUCT_COPYRIGHT "Copyright (C) 2012 Beijing RaiseTech Holding Ltd Company"
!define PRODUCT_WEB_SITE "http://www.thinktrader.net"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\${PRODUCT_MAIN_EXE}\${PRODUCT_NAME_CN}"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME_CN}\${PLATFORM_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_REASOURCE_DIR "installerResource"
!define PRODUCT_INSTALLER_NAME "${PRODUCT_NAME_CN} ��װ����"
!define BIN_DIR_WIN32 "bin.win32"
!define BIN_DIR_APP "bin.${PLATFORM_NAME}"

SetCompressor lzma

; ------ MUI �ִ����涨�� (1.67 �汾���ϼ���) ------
!include "MUI.nsh"

; MUI Ԥ���峣��
!define MUI_ABORTWARNING
!define MUI_ICON "${PRODUCT_REASOURCE_DIR}\Setup.ico"
!define MUI_UNICON "${PRODUCT_REASOURCE_DIR}\uninst.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "${PRODUCT_REASOURCE_DIR}\welcome.bmp"

; ��ӭҳ��
!define MUI_PAGE_CUSTOMFUNCTION_SHOW  WelcomePageShow
!insertmacro MUI_PAGE_WELCOME
; ���Э��ҳ��
!define MUI_LICENSEPAGE_CHECKBOX
!insertmacro MUI_PAGE_LICENSE "${PRODUCT_REASOURCE_DIR}\license.txt"
; ��װĿ¼ѡ��ҳ��
!insertmacro MUI_PAGE_DIRECTORY
; ��װ����ҳ��
!insertmacro MUI_PAGE_INSTFILES
; ��װ���ҳ��
Page custom PageOtherTask
!define MUI_FINISHPAGE_RUN "$INSTDIR\${BIN_DIR_APP}\${PRODUCT_MAIN_EXE}"
!define MUI_FINISHPAGE_RUN_TEXT "���� ${PRODUCT_NAME_CN}"
!define MUI_PAGE_CUSTOMFUNCTION_SHOW  FinishPageShow
!insertmacro MUI_PAGE_FINISH

; ��װж�ع���ҳ��
!insertmacro MUI_UNPAGE_INSTFILES

; ��װ�����������������
!insertmacro MUI_LANGUAGE "SimpChinese"

; ��װԤ�ͷ��ļ�
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI �ִ����涨����� ------

Name "${PRODUCT_NAME_CN} ${PRODUCT_VERSION}"
OutFile "${OUTFILE}"

; InstallDir "$PROGRAMFILES\${PRODUCT_NAME_CN}"
InstallDir "D:\${PRODUCT_NAME_CN}"

InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
ShowUnInstDetails show
BrandingText "${PRODUCT_NAME_CN}"


VIProductVersion "${PRODUCT_VERSION}"
VIAddVersionKey FileDescription "${PRODUCT_INSTALLER_NAME}"
VIAddVersionKey FileVersion "${PRODUCT_VERSION}"
; VIAddVersionKey ProductName "${PRODUCT_NAME_CN} ${PRODUCT_VERSION}" ;��Ʒ����
VIAddVersionKey ProductName "${PRODUCT_NAME_CN}"
VIAddVersionKey ProductVersion "${PRODUCT_VERSION}"
VIAddVersionKey Comments "${PRODUCT_INSTALLER_NAME}"
VIAddVersionKey CompanyName "${PRODUCT_PUBLISHER}"
VIAddVersionKey LegalCopyright "${PRODUCT_COPYRIGHT}"
VIAddVersionKey InternalName "${PRODUCT_INSTALLER_NAME}"
; VIAddVersionKey LegalTrademarks "${PRODUCT_PUBLISHER}" ;�Ϸ��̱� ;
VIAddVersionKey OriginalFilename "${ORIGINAL_FILENAME}"
; VIAddVersionKey PrivateBuild "XX" ;�����ڲ��汾˵��
; VIAddVersionKey SpecialBuild "XX" ;�����ڲ�����˵�� 


RequestExecutionLevel admin

; ��"un."��Ϊ�������룬��ǿʵ�ְ�װ��ж�ع��ú�������
; ʵ��������һ���궨����������

!macro DefFunc_CheckProcess un
Function ${un}CheckProcess
    Pop $0  ; module name
    Pop $1  ; exe name
    Push "$INSTDIR\${BIN_DIR_APP}\$1"
    FindProcDLL::FindProc "$INSTDIR\${BIN_DIR_APP}\$1"
    Pop $R0
    IntCmp $R0 0 not_found  ; ���FindProc���Ϊ0����ʾδ�ҵ����򣬷������
    MessageBox MB_ICONSTOP "��װ�����⵽ ${PRODUCT_NAME_CN} $0 �������У����˳��˳�������ԡ�" IDYES +2
    Quit
not_found:
FunctionEnd
!macroend

!macro DefFunc_KillProcess un
Function ${un}KillProcess
    Pop $0  ; module name
    Pop $1  ; exe name
    Push "$INSTDIR\${BIN_DIR_WIN32}\$1"
    ProcessWork::existsprocess
    Pop $R0
    IntCmp $R0 0 no_more  ; ���FindProc���Ϊ0����ʾδ�ҵ����򣬷������
    MessageBox MB_ICONQUESTION|MB_YESNO "��װ�����⵽ ${PRODUCT_NAME_CN} $0 �������У��Ƿ���ֹ�˳���" IDYES try_kill
    MessageBox MB_ICONSTOP "${PRODUCT_NAME_CN} $0 �������У����˳��˳��������"
    Quit
try_kill:
    Push $1
    Push $0
    call ${un}ForceKillProcess  ; ��������
no_more:
FunctionEnd
!macroend

!macro DefFunc_ForceKillProcess un
Function ${un}ForceKillProcess
    Pop $0  ; module name
    Pop $1  ; exe name
try_kill_one:
    KillProcDLL::KillProc "$1"
    Pop $R0
    IntCmp $R0 0 try_kill_one       ; ����0��ʾɱ���̳ɹ�����Ӧ����ɱ�˽���������������
    IntCmp $R0 602 check_no_more    ; ����602��ʾ��Ϊ����ԭ��ɱ����ʧ�ܣ���ʵ���Ϸ�����ʱ����ʵ��ɱ�ɹ��˵ģ���C�̸�Ŀ¼�������ʹܵ�daemon�ٰ�װ������������Ҫ��һ�����
    IntCmp $R0 603 check_no_more    ; ����603��ʾû�ҵ��˽��̣������������a) ȷʵû�д˽��� b) ��Ȩ�޵�ԭ���޷����ʴ˽��̣������2�֣�Ӧ��Ϊɱ����ʧ�ܣ�������Ҫ��һ�����
    MessageBox MB_ICONSTOP "�޷���ֹ $0 ($1) (code=$R0)�����ֶ���ֹ�˳��������"   ; KillProc����ֵ��0��603
    Quit
check_no_more:
    FindProcDLL::FindProc "$1"
    Pop $R0
    IntCmp $R0 1 try_kill_one  ; ���FindProc���Ϊ1����ʾ�ҵ��˳���˵�����н��̴��ڣ�����ɱ
FunctionEnd
!macroend

!macro DefFunc_StartupCheck un
Function ${un}StartupCheck
    IfSilent force_kill

        Push "${PRODUCT_MAIN_EXE}"
        Push "����������"
        call ${un}CheckProcess

    goto cont

    force_kill:

        ;δ����XtUpdate.exeɱ����
        Push "${PRODUCT_MAIN_EXE}"
        Push "����������"
        call ${un}ForceKillProcess

    cont:
FunctionEnd
!macroend

Section "MainSection" SEC01

    call StartupCheck
    IfSilent update
        Delete "$DESKTOP\${PRODUCT_NAME_CN}.lnk"
    update:
    Delete "$INSTDIR\${PRODUCT_NAME_CN}.url"
    RMDir /r "$SMPROGRAMS\${PRODUCT_NAME_CN}"

    ;------------------------------------------------------------
    ; Win32
    ;------------------------------------------------------------

    RMDir /r "$INSTDIR\${BIN_DIR_WIN32}"
    RMDir /r "$INSTDIR\${BIN_DIR_APP}"
    RMDir /r "$INSTDIR\plugins"
    

    ;------------------------------------------------------------
    ; Win32 or x64 dll
    ;------------------------------------------------------------

    SetOutPath "$INSTDIR\${BIN_DIR_APP}"
    SetOverwrite on
    File "..\..\${PLATFORM_NAME}\${CONFIGURATION_NAME}\jsoncpp.dll"
    File "..\..\${PLATFORM_NAME}\${CONFIGURATION_NAME}\NetLib.dll"
	File "..\..\${PLATFORM_NAME}\${CONFIGURATION_NAME}\PanelLoginDialog.dll"
	File "..\..\${PLATFORM_NAME}\${CONFIGURATION_NAME}\PanelMainWindow.dll"
	File "..\..\${PLATFORM_NAME}\${CONFIGURATION_NAME}\ProtocolData.dll"
	File "..\..\${PLATFORM_NAME}\${CONFIGURATION_NAME}\Qt5Cored.dll"
	File "..\..\${PLATFORM_NAME}\${CONFIGURATION_NAME}\Qt5Guid.dll"
	File "..\..\${PLATFORM_NAME}\${CONFIGURATION_NAME}\Qt5Widgetsd.dll"
	File "..\..\${PLATFORM_NAME}\${CONFIGURATION_NAME}\QtFlamingo.exe"
	File "..\..\${PLATFORM_NAME}\${CONFIGURATION_NAME}\User.dll"
	File "..\..\${PLATFORM_NAME}\${CONFIGURATION_NAME}\utils.dll"
    File "..\..\${PLATFORM_NAME}\${CONFIGURATION_NAME}\winlog.dll"
    File "..\..\${PLATFORM_NAME}\${CONFIGURATION_NAME}\zlib.dll"
	
	
    ;platforms
    SetOutPath "$INSTDIR\${BIN_DIR_APP}\platforms"
    SetOverwrite on
    File "..\..\${PLATFORM_NAME}\${CONFIGURATION_NAME}\platforms\qminimald.dll"
    File "..\..\${PLATFORM_NAME}\${CONFIGURATION_NAME}\platforms\qoffscreend.dll"
    File "..\..\${PLATFORM_NAME}\${CONFIGURATION_NAME}\platforms\qwindowsd.dll"

	
    ;����Ȩ��
    AccessControl::GrantOnFile \
    "$INSTDIR\config" "(BU)" "FullAccess"
	
    AccessControl::GrantOnFile \
    "$INSTDIR\config_local" "(BU)" "FullAccess"
    Pop $0

    CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME_CN}"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME_CN}\����${PRODUCT_NAME_CN}.lnk" "$INSTDIR\${BIN_DIR_APP}\${PRODUCT_MAIN_EXE}"


SectionEnd

Section -AdditionalIcons
    SetOutPath $INSTDIR\${BIN_DIR_APP}
    SetOverwrite on
    WriteIniStr "$INSTDIR\${PRODUCT_NAME_CN}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME_CN}\�ٷ���ҳ.lnk" "$INSTDIR\${PRODUCT_NAME_CN}.url"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME_CN}\ж��${PRODUCT_NAME_CN}.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
    WriteUninstaller "$INSTDIR\uninst.exe"
    WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}\${PLATFORM_NAME}" "$INSTDIR" "$INSTDIR\${BIN_DIR_APP}\${PRODUCT_MAIN_EXE}"
    WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
    WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
    WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\${BIN_DIR_APP}\${PRODUCT_MAIN_EXE}"
    WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
    WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
    WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

/******************************
 *  �����ǰ�װ�����ж�ز���  *
 ******************************/

Section Uninstall
    Delete "$DESKTOP\${PRODUCT_NAME_CN}.lnk"
    Delete "$INSTDIR\${PRODUCT_NAME_CN}.url"
    Delete "$SMSTARTUP\${PRODUCT_NAME_CN}.lnk"
!ifndef SERVER_BINS
    ;Delete "$DESKTOP\ѸͶ�ʲ�����ƽ̨�Ż�.lnk"
!endif
    RMDir /r "$SMPROGRAMS\${PRODUCT_NAME_CN}"

    DeleteRegKey /ifempty ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
    DeleteRegValue HKLM "${PRODUCT_DIR_REGKEY}\${PLATFORM_NAME}" "$INSTDIR"

    DeleteRegValue HKCU "Software\Microsoft\Windows\CurrentVersion\Run" "${PRODUCT_NAME_EN}"

    RMDir /r "$INSTDIR\${BIN_DIR_APP}"
    RMDir /r "$INSTDIR\${BIN_DIR_WIN32}"
    RMDir /r "$INSTDIR\config"
	RMDir /r "$INSTDIR"

    SetAutoClose true
SectionEnd

#-- ���� NSIS �ű��༭�������� Function ���α�������� Section ����֮���д���Ա��ⰲװ�������δ��Ԥ֪�����⡣--#

; ���붨��õĺ꣬������̼����غ���

!insertmacro DefFunc_CheckProcess ""
!insertmacro DefFunc_CheckProcess "un."

!insertmacro DefFunc_KillProcess ""
!insertmacro DefFunc_KillProcess "un."

!insertmacro DefFunc_ForceKillProcess ""
!insertmacro DefFunc_ForceKillProcess "un."

!insertmacro DefFunc_StartupCheck ""
!insertmacro DefFunc_StartupCheck "un."

Function .onInit
    !insertmacro INSTALLOPTIONS_EXTRACT "othertask.ini"
FunctionEnd

Function PageOtherTask
    InstallOptions::dialog "$PLUGINSDIR\othertask.ini"
FunctionEnd

Function .onInstSuccess
    ReadINIStr $R0 "$PLUGINSDIR\othertask.ini" "Field 3" "State"
    ReadINIStr $R1 "$PLUGINSDIR\othertask.ini" "Field 4" "State"

    IfSilent update
        IntCmp $R0 1 0 +2 +2
        CreateShortCut "$DESKTOP\${PRODUCT_NAME_CN}.lnk" "$INSTDIR\${BIN_DIR_APP}\${PRODUCT_MAIN_EXE}"

        IntCmp $R1 1 0 +2 +2
        WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Run" "${PRODUCT_NAME_EN}" '"$INSTDIR\${BIN_DIR_APP}\${PRODUCT_MAIN_EXE}" -w 600'
        
        goto cont
        
    update:
        ;���ھ�Ĭ��װ ��������ϴ��ڿ�ݷ�ʽ ��ɾ���ÿ�ݷ�ʽ ���Ҵ����¿�ݷ�ʽ(���32λ������64λ�¿�ݷ�ʽʧЧ����)
        IfFileExists "$DESKTOP\${PRODUCT_NAME_CN}.lnk" 0 +3
        Delete "$DESKTOP\${PRODUCT_NAME_CN}.lnk"
        CreateShortCut "$DESKTOP\${PRODUCT_NAME_CN}.lnk" "$INSTDIR\${BIN_DIR_APP}\${PRODUCT_MAIN_EXE}"

        MessageBox MB_ICONQUESTION|MB_YESNO "��װ��ϣ��Ƿ��������� ${PRODUCT_NAME_CN}��" IDYES +2
        goto cont
        ExecShell "" "$INSTDIR\${BIN_DIR_APP}\${PRODUCT_MAIN_EXE}"
        
    cont:
FunctionEnd

Function un.onInit
    call un.StartupCheck
    MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "��ȷʵҪ��ȫ�Ƴ� $(^Name) ���������е������" IDYES +2
    Abort
FunctionEnd

Function un.onUninstSuccess
    HideWindow
    MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) �ѳɹ��ش���ļ�����Ƴ���"
FunctionEnd

Function WelcomePageShow
    ${WelcomePage_LayoutUI}
FunctionEnd

Function FinishPageShow
    ${FinishPage_LayoutUI}
FunctionEnd
