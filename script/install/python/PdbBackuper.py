# -*- coding:utf-8 -*-

import Util
import sys
import os
import shutil
import os.path, time
import PackLog
import tarfile
from datetime import datetime
import traceback

class PdbBackuper:
    def __doBackupDir(self, src_dir):
        # ��������·��
        util = Util.Util()
        if not os.path.isdir(self.__tmp_dir):
            util.makeDir(self.__tmp_dir)
        # �����ļ�
        PackLog.pack_log.writeLog(
            '\n' + '*********************************************���� ' + src_dir + ' �µ�pdb��map�ļ�********************************************' + '\n')
        for parent, dirnames, filenames in os.walk(src_dir):
            for f in filenames:
                if f.lower().endswith('.pdb') or f.lower().endswith('.map'):
                    src_file = src_dir + '\\' + f
                    curTime = datetime.now()
                    fileCreateTime = time.ctime(os.path.getctime(src_file))
                    PackLog.pack_log.writeLog(str(curTime)[:-3] + ': ' + '����pdb��map�ļ�: ' + f + '(����ʱ��:' + str(
                        fileCreateTime) + ')' + ' �� ' + src_dir + ' �� ' + self.__tmp_dir + '\n')
                    shutil.copy(src_file, self.__tmp_dir)


    def tarPdbFile(self):
        print "tarpdbfilr"
        dst_dir = self.__tmp_dir
        pdbtarfilename = self.__tmp_dir + '\\' + self.__version + "_" + self.__platform + ".tar.gz"
        pdbtarfile = tarfile.open(pdbtarfilename, "w:gz")
        try:
            for parent, dirnames, filenames in os.walk(dst_dir):
                for f in filenames:
                    src_file = parent + '\\' + f
                    curTime = datetime.now()
                    fileCreateTime = time.ctime(os.path.getctime(src_file))
                    PackLog.pack_log.writeLog(str(curTime)[:-3] + ': ' + 'ѹ��pdb��map�ļ�: ' + f + '(����ʱ��:' + str(
                        fileCreateTime) + ')' + '��' + dst_dir + '��' + pdbtarfilename + '\n')
                    pdbtarfile.add(src_file, f)
            pdbtarfile.close()
            return True
        except Exception as e:
            pdbtarfile.close()
            traceback.print_exc(e)
            return False
    def copyPdbTarFile(self):
        print "copyPdbTarFile"
        pdbtarfilename = self.__tmp_dir + '\\' + self.__version + "_" + self.__platform + ".tar.gz"
        dst_dir = self.__pdb_dir + '\\' + self.__version + '\\' + self.__platform
        dst_file = self.__pdb_dir + '\\' + self.__version + '\\' + self.__platform + '\\' + self.__version + "_" + self.__platform + ".tar.gz"
        util = Util.Util()
        if not os.path.isdir(dst_dir):
            util.makeDir(dst_dir)
        try:
            curTime = datetime.now()
            fileCreateTime = time.ctime(os.path.getctime(pdbtarfilename))
            PackLog.pack_log.writeLog(str(curTime)[:-3] + ': ' + '����pdb��mapѹ���ļ�: ' + '(����ʱ��:' + str(
                fileCreateTime) + ')' + '��' + pdbtarfilename+ '��' + dst_file + '\n')
            shutil.copy(pdbtarfilename, dst_file)
            return True
        except Exception as e:
            traceback.print_exc(e)
            return False
    def rmTempDir(self):
        print "rmTempDir"
        temp_dir = r"E:\pdb" + '\\' + self.__version + "\\"
        try:
            #shutil.rmtree(temp_dir)
            pass
            return True
        except Exception as e:
            traceback.print_exc(e)
            return False
            
    # ����pdb
    def backupPdb(self):
        for src_dir in self.__src_dir_list:
            print 'Backup pdb : ' + src_dir
            self.__doBackupDir(src_dir)
        if self.tarPdbFile():
            if self.copyPdbTarFile():
                if not self.rmTempDir():
                    raise Exception('ɾ����ʱ�����ļ�����')
            else:
                raise Exception("����ѹ��pdb�ļ���ftp����")
        else:
            raise Exception("ѹ��pdb�ļ�����")

    # ���캯��
    def __init__(self, version, src_dir_list, pdb_dir, platform):
        self.__version = version
        self.__pdb_dir = pdb_dir
        self.__src_dir_list = src_dir_list
        self.__platform = platform
        self.__tmp_dir = r"E:\pdb" + '\\' + self.__version + '\\' + self.__platform

# if __name__ == "__main__":
#     pdbbacker = PdbBackuper("0.0.0.0",[r"I:\sourcecode\workspace\oa_test_client_changanjijin_20150720\XtItsmClient\tags\changanjijin_20150720\_runtime\Win32.Release", r"I:\sourcecode\workspace\oa_test_client_changanjijin_20150720\server5\quoter\branches\multiconn_20141105\_runtime\Win32.Release"] , r"\\192.168.1.250\khd\pdb\XtAmpTradeClient", "W32")
#     pdbbacker.backupPdb()