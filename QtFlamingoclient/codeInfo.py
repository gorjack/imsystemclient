# -*- coding: utf-8 -*-
"""
Created on Tue Apr  2 13:52:19 2019

@author: Yepeng
"""

import sys
import os
import subprocess

def codeInfo(source_path):
    tools = "F:\\ForHood\\flamingo\\flamingoclient\\cloc-1.64.exe" #
    source_root = source_path ## "E:\CodeReview\XtItClient_201709_sp2"
    exclude_dir= ""
    output_file = "{0}\\report_cline_qmt_sdk.txt".format(source_root)
    output_source_file = "{0}\\report_cline_qmt_sdk_source.txt".format(source_root)
    
    filter_includes_file = "{0}\\report_cline_filter_includes.txt".format(source_root)
    filter_excludes_file = "{0}\\report_cline_filter_excludes.txt".format(source_root)
    options = "--skip-win-hidden"
    langs="\"C++,C,C/C++ Header,XML,HTML,Lua,SQL,Python,Visual Basic,DOS Batch,Protocol Buffers,Windows Resource File,make\""
    source_dir = ""
    
    source_dirs = []    
    source_dirs.append("{0}\\Source".format(source_root))
    #source_dirs.append("{0}\\_runtime".format(source_root))
    #source_dirs.append("{0}\\script".format(source_root))
    #source_dirs.append("{0}\\xtPlatform\\src".format(source_root))
    #source_dirs.append("{0}\\libs\\xtquoter".format(source_root))
    #source_dirs.append("{0}\\libs\\base".format(source_root))
    #source_dirs.append("{0}\\libs\\model".format(source_root))
    #source_dirs.append("{0}\\libs\\structbase".format(source_root))
   # source_dirs.append("{0}\\libs\\traderbase".format(source_root))
    
    source_string = ""
    fs = open(filter_includes_file, "w")
    for item in source_dirs:
        source_dir += item + " "
        source_string += "{0}\n".format(item)
    source_dir.rstrip(" ")
    fs.writelines(source_string)
    fs.close()
    
    
    exclude_dirs= []
    #exclude_dirs.append("{0}\\_runtime\\customer_resources".format(source_root))
    #exclude_dirs.append("{0}\\src\\Ui".format(source_root))
   # exclude_dirs.append("{0}\\src\\UiComponent\\QScintilla".format(source_root))
   # exclude_dirs.append("{0}\\src\\UiComponent\\PythonSymbol\\CTags".format(source_root))
   # exclude_dirs.append("{0}\\libs\\sdk".format(source_root))
   # exclude_dirs.append("{0}\\libs\\xtPlatform\\libs".format(source_root))
    #exclude_dirs.append("_builder,Debug,Release,GeneratedFiles,test,Test")
    
    excludes_string = ""
    fs = open(filter_excludes_file, "w")
    for item in exclude_dirs:
        exclude_dir += item + ","
        excludes_string += "{0}\n".format(item)
    exclude_dir.rstrip(",")
    fs.writelines(excludes_string)
    fs.close()
    
    exclude_dir = "_builder,Debug,Release,GeneratedFiles,test,Test,x64.Release,x64.Debug,Win32.Release,Win32.Debug"
    
    
    
    command_string = "{0} {1} --exclude-dir={2}  --list-file={3} --exclude-list-file={4} --report-file={5} --counted={6} --include-lang={7}".format(tools, options, exclude_dir, filter_includes_file, filter_excludes_file, output_file, output_source_file, langs)
    #command_string = "{0} {1} --exclude-dir={2}  --report-file={3} {4}".format(tools, options, exclude_dir, output_file, source_dir)
    #command_string = "{0} {1} --exclude-dir={2} --include-lang={5} --counted={6} --report-file={3} {4}".format(tools, options, exclude_dir, output_file, source_dir, langs, output_source_file)
    print("Execute Command :[{0}]".format(command_string))
    retcode = subprocess.call(args = command_string,shell=True)
    if 0 != retcode:
        raise Exception(unicode('获取代码行统计信息遇到问题。', 'utf-8'))
    fs = open(output_file, "a")
    fs.write("\nExecute Command :\n{0}\n".format(command_string))    
    fs.write("\nSource Files[{0}] :\n".format(filter_includes_file))
    fs.writelines(source_string)    
    fs.write("\nExclude Files [{0}]:\n".format(filter_excludes_file))
    fs.writelines(excludes_string)
    fs.close()
    
    
# 脚本入口
if '__main__' == __name__:
    current_dir = os.path.dirname(os.path.abspath(__file__))
    print(current_dir)
    source_root = os.path.dirname(os.path.abspath("{0}\\..".format(current_dir)))
    print(source_root)
    #codeInfo("E:\CodeReview\XtItClient_201709_sp2")
    codeInfo(current_dir)
    os.system("pause")
    