# -*- coding:gbk -*-

import sys
import os
import shutil

sys.path.append('../../../_xtPlatform/script/python/')
import Util
import PackLog

# 打包类
class Packer:

    def __binPath(self):
        return self.__conf.root_dir + '\\_runtime\\bin.pack\\' + self.__xtClientPlatform + '.' + self.__configuration

    def __confPath(self):
        return self.__conf.root_dir + '\\_runtime\\config.pack\\' + self.__xtClientPlatform + '.' +  self.__configuration
    
    # 运行NSIS生成安装包
    def __makeNSIS(self):
        print '\n生成安装文件。'
        nsi_script_path = self.__conf.root_dir + '\\script\\install'
        PackLog.pack_log.writeLog('\n运行的NSI文件：' + nsi_script_path + 'xtInstaller.nsi\n')
        print 'path %s hello' %(nsi_script_path)

        
        print 'nsi script is %s' % (self.__conf.nsi_script)

        cmd_line = 'makensis /DPRODUCT_VERSION=\"' + self.__conf.version + '\" \"' + self.__conf.nsi_script + '\"'
        print 'jiaoben=:' + cmd_line + '\n'
        if 0 != os.system(cmd_line):
            raise Exception('生成安装文件失败。')

    # 初始化bin文件目录
    def iniBinDir(self):
        util = Util.Util()
        bin_path = self.__binPath()
        if not os.path.isdir(bin_path):
            os.mkdir(bin_path)
        util.clearDir(bin_path)
        conf_path = self.__confPath()
        if not os.path.isdir(conf_path):
            os.mkdir(conf_path)
        util.clearDir(conf_path)
        return bin_path, conf_path

    # 打包 
    def packInstaller(self):
        self.__makeNSIS()
    
    # 初始化函数
    def __init__(self, conf):
        self.__conf = conf
        self.__sign_cmd_line = self.__conf.root_dir + '\\script\\install\\\sign\\signtool.exe sign /f "' +  self.__conf.root_dir +  '\\script\\install\\\sign\\mycert.pfx" /p "rzrk.verisign" /t "http://timestamp.verisign.com/scripts/timstamp.dll" '

