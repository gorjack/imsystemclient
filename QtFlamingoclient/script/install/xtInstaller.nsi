;--------------------------------
; xtclient Setup NSIS Script
; @author zoubailiu
; @date   2012-5-7
;
; 用法：
; makensis.exe [/DPLATFORM_NAME=x64] [/DCONFIGURATION_NAME=Release] [/DPRODUCT_NAME_CN=迅投交易终端] [/DPRODUCT_NAME_EN=XtTradeClient] [/DPRODUCT_VERSION=x.x.x.xxxx] [/DORIGINAL_FILENAME=xxx.exe] [/DOUTFILE=c:\xxx.exe] xxx.nsi
;

!include "LogicLib.nsh"
!include "xtWelAndFinishPageLayoutUI.nsh"

; 安装程序初始定义常量

!ifndef PRODUCT_NAME_CN
    !define PRODUCT_NAME_CN "PBConfigTools管理工具"
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
!define PRODUCT_PUBLISHER "北京睿智融科控股有限公司"
!define PRODUCT_COPYRIGHT "Copyright (C) 2012 Beijing RaiseTech Holding Ltd Company"
!define PRODUCT_WEB_SITE "http://www.thinktrader.net"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\${PRODUCT_MAIN_EXE}\${PRODUCT_NAME_CN}"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME_CN}\${PLATFORM_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_REASOURCE_DIR "installerResource"
!define PRODUCT_INSTALLER_NAME "${PRODUCT_NAME_CN} 安装程序"
!define BIN_DIR_WIN32 "bin.win32"
!define BIN_DIR_APP "bin.${PLATFORM_NAME}"

SetCompressor lzma

; ------ MUI 现代界面定义 (1.67 版本以上兼容) ------
!include "MUI.nsh"

; MUI 预定义常量
!define MUI_ABORTWARNING
!define MUI_ICON "${PRODUCT_REASOURCE_DIR}\Setup.ico"
!define MUI_UNICON "${PRODUCT_REASOURCE_DIR}\uninst.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "${PRODUCT_REASOURCE_DIR}\welcome.bmp"

; 欢迎页面
!define MUI_PAGE_CUSTOMFUNCTION_SHOW  WelcomePageShow
!insertmacro MUI_PAGE_WELCOME
; 许可协议页面
!define MUI_LICENSEPAGE_CHECKBOX
!insertmacro MUI_PAGE_LICENSE "${PRODUCT_REASOURCE_DIR}\license.txt"
; 安装目录选择页面
!insertmacro MUI_PAGE_DIRECTORY
; 安装过程页面
!insertmacro MUI_PAGE_INSTFILES
; 安装完成页面
Page custom PageOtherTask
!define MUI_FINISHPAGE_RUN "$INSTDIR\${BIN_DIR_APP}\${PRODUCT_MAIN_EXE}"
!define MUI_FINISHPAGE_RUN_TEXT "运行 ${PRODUCT_NAME_CN}"
!define MUI_PAGE_CUSTOMFUNCTION_SHOW  FinishPageShow
!insertmacro MUI_PAGE_FINISH

; 安装卸载过程页面
!insertmacro MUI_UNPAGE_INSTFILES

; 安装界面包含的语言设置
!insertmacro MUI_LANGUAGE "SimpChinese"

; 安装预释放文件
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI 现代界面定义结束 ------

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
; VIAddVersionKey ProductName "${PRODUCT_NAME_CN} ${PRODUCT_VERSION}" ;产品名称
VIAddVersionKey ProductName "${PRODUCT_NAME_CN}"
VIAddVersionKey ProductVersion "${PRODUCT_VERSION}"
VIAddVersionKey Comments "${PRODUCT_INSTALLER_NAME}"
VIAddVersionKey CompanyName "${PRODUCT_PUBLISHER}"
VIAddVersionKey LegalCopyright "${PRODUCT_COPYRIGHT}"
VIAddVersionKey InternalName "${PRODUCT_INSTALLER_NAME}"
; VIAddVersionKey LegalTrademarks "${PRODUCT_PUBLISHER}" ;合法商标 ;
VIAddVersionKey OriginalFilename "${ORIGINAL_FILENAME}"
; VIAddVersionKey PrivateBuild "XX" ;个人内部版本说明
; VIAddVersionKey SpecialBuild "XX" ;特殊内部本本说明 


RequestExecutionLevel admin

; 把"un."作为参数传入，勉强实现安装和卸载共用函数代码
; 实际上是用一个宏定义两个函数

!macro DefFunc_CheckProcess un
Function ${un}CheckProcess
    Pop $0  ; module name
    Pop $1  ; exe name
    Push "$INSTDIR\${BIN_DIR_APP}\$1"
    FindProcDLL::FindProc "$INSTDIR\${BIN_DIR_APP}\$1"
    Pop $R0
    IntCmp $R0 0 not_found  ; 如果FindProc结果为0，表示未找到程序，否则继续
    MessageBox MB_ICONSTOP "安装程序检测到 ${PRODUCT_NAME_CN} $0 正在运行，请退出此程序后重试。" IDYES +2
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
    IntCmp $R0 0 no_more  ; 如果FindProc结果为0，表示未找到程序，否则继续
    MessageBox MB_ICONQUESTION|MB_YESNO "安装程序检测到 ${PRODUCT_NAME_CN} $0 正在运行，是否终止此程序？" IDYES try_kill
    MessageBox MB_ICONSTOP "${PRODUCT_NAME_CN} $0 正在运行，请退出此程序后重试"
    Quit
try_kill:
    Push $1
    Push $0
    call ${un}ForceKillProcess  ; 函数调用
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
    IntCmp $R0 0 try_kill_one       ; 返回0表示杀进程成功，则应继续杀此进程名的其它进程
    IntCmp $R0 602 check_no_more    ; 返回602表示因为其它原因杀进程失败，但实际上发现有时候其实是杀成功了的（如C盘根目录先跑着资管的daemon再安装单机），故需要进一步检查
    IntCmp $R0 603 check_no_more    ; 返回603表示没找到此进程，有两种情况：a) 确实没有此进程 b) 因权限等原因无法访问此进程，如果第2种，应认为杀进程失败，所以需要进一步检查
    MessageBox MB_ICONSTOP "无法终止 $0 ($1) (code=$R0)，请手动终止此程序后重试"   ; KillProc返回值非0非603
    Quit
check_no_more:
    FindProcDLL::FindProc "$1"
    Pop $R0
    IntCmp $R0 1 try_kill_one  ; 如果FindProc结果为1，表示找到了程序，说明还有进程存在，继续杀
FunctionEnd
!macroend

!macro DefFunc_StartupCheck un
Function ${un}StartupCheck
    IfSilent force_kill

        Push "${PRODUCT_MAIN_EXE}"
        Push "交易主程序"
        call ${un}CheckProcess

    goto cont

    force_kill:

        ;未改由XtUpdate.exe杀进程
        Push "${PRODUCT_MAIN_EXE}"
        Push "交易主程序"
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

	
    ;设置权限
    AccessControl::GrantOnFile \
    "$INSTDIR\config" "(BU)" "FullAccess"
	
    AccessControl::GrantOnFile \
    "$INSTDIR\config_local" "(BU)" "FullAccess"
    Pop $0

    CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME_CN}"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME_CN}\启动${PRODUCT_NAME_CN}.lnk" "$INSTDIR\${BIN_DIR_APP}\${PRODUCT_MAIN_EXE}"


SectionEnd

Section -AdditionalIcons
    SetOutPath $INSTDIR\${BIN_DIR_APP}
    SetOverwrite on
    WriteIniStr "$INSTDIR\${PRODUCT_NAME_CN}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME_CN}\官方首页.lnk" "$INSTDIR\${PRODUCT_NAME_CN}.url"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME_CN}\卸载${PRODUCT_NAME_CN}.lnk" "$INSTDIR\uninst.exe"
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
 *  以下是安装程序的卸载部分  *
 ******************************/

Section Uninstall
    Delete "$DESKTOP\${PRODUCT_NAME_CN}.lnk"
    Delete "$INSTDIR\${PRODUCT_NAME_CN}.url"
    Delete "$SMSTARTUP\${PRODUCT_NAME_CN}.lnk"
!ifndef SERVER_BINS
    ;Delete "$DESKTOP\迅投资产管理平台门户.lnk"
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

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

; 插入定义好的宏，定义进程检查相关函数

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
        ;对于静默安装 如果桌面上存在快捷方式 则删除该快捷方式 并且创建新快捷方式(解决32位升级到64位下快捷方式失效问题)
        IfFileExists "$DESKTOP\${PRODUCT_NAME_CN}.lnk" 0 +3
        Delete "$DESKTOP\${PRODUCT_NAME_CN}.lnk"
        CreateShortCut "$DESKTOP\${PRODUCT_NAME_CN}.lnk" "$INSTDIR\${BIN_DIR_APP}\${PRODUCT_MAIN_EXE}"

        MessageBox MB_ICONQUESTION|MB_YESNO "安装完毕，是否立即运行 ${PRODUCT_NAME_CN}？" IDYES +2
        goto cont
        ExecShell "" "$INSTDIR\${BIN_DIR_APP}\${PRODUCT_MAIN_EXE}"
        
    cont:
FunctionEnd

Function un.onInit
    call un.StartupCheck
    MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "你确实要完全移除 $(^Name) ，及其所有的组件？" IDYES +2
    Abort
FunctionEnd

Function un.onUninstSuccess
    HideWindow
    MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地从你的计算机移除。"
FunctionEnd

Function WelcomePageShow
    ${WelcomePage_LayoutUI}
FunctionEnd

Function FinishPageShow
    ${FinishPage_LayoutUI}
FunctionEnd
