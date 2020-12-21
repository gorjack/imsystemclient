# -*- coding:gbk -*-

import sys
import os
import shutil

sys.path.append('../../../_xtPlatform/script/python/')
import Util
import PackLog

# �����
class Packer:

    def __binPath(self):
        return self.__conf.root_dir + '\\_runtime\\bin.pack\\' + self.__xtClientPlatform + '.' + self.__configuration

    def __confPath(self):
        return self.__conf.root_dir + '\\_runtime\\config.pack\\' + self.__xtClientPlatform + '.' +  self.__configuration
    
    # ����NSIS���ɰ�װ��
    def __makeNSIS(self):
        print '\n���ɰ�װ�ļ���'
        nsi_script_path = self.__conf.root_dir + '\\script\\install'
        PackLog.pack_log.writeLog('\n���е�NSI�ļ���' + nsi_script_path + 'xtInstaller.nsi\n')
        print 'path %s hello' %(nsi_script_path)

        
        print 'nsi script is %s' % (self.__conf.nsi_script)

        cmd_line = 'makensis /DPRODUCT_VERSION=\"' + self.__conf.version + '\" \"' + self.__conf.nsi_script + '\"'
        print 'jiaoben=:' + cmd_line + '\n'
        if 0 != os.system(cmd_line):
            raise Exception('���ɰ�װ�ļ�ʧ�ܡ�')

    # ��ʼ��bin�ļ�Ŀ¼
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

    # ��� 
    def packInstaller(self):
        self.__makeNSIS()
    
    # ��ʼ������
    def __init__(self, conf):
        self.__conf = conf
        self.__sign_cmd_line = self.__conf.root_dir + '\\script\\install\\\sign\\signtool.exe sign /f "' +  self.__conf.root_dir +  '\\script\\install\\\sign\\mycert.pfx" /p "rzrk.verisign" /t "http://timestamp.verisign.com/scripts/timstamp.dll" '

