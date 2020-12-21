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
        # 创建输入路径
        util = Util.Util()
        if not os.path.isdir(self.__tmp_dir):
            util.makeDir(self.__tmp_dir)
        # 复制文件
        PackLog.pack_log.writeLog(
            '\n' + '*********************************************备份 ' + src_dir + ' 下的pdb及map文件********************************************' + '\n')
        for parent, dirnames, filenames in os.walk(src_dir):
            for f in filenames:
                if f.lower().endswith('.pdb') or f.lower().endswith('.map'):
                    src_file = src_dir + '\\' + f
                    curTime = datetime.now()
                    fileCreateTime = time.ctime(os.path.getctime(src_file))
                    PackLog.pack_log.writeLog(str(curTime)[:-3] + ': ' + '复制pdb或map文件: ' + f + '(生成时间:' + str(
                        fileCreateTime) + ')' + ' 从 ' + src_dir + ' 到 ' + self.__tmp_dir + '\n')
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
                    PackLog.pack_log.writeLog(str(curTime)[:-3] + ': ' + '压缩pdb或map文件: ' + f + '(生成时间:' + str(
                        fileCreateTime) + ')' + '从' + dst_dir + '到' + pdbtarfilename + '\n')
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
            PackLog.pack_log.writeLog(str(curTime)[:-3] + ': ' + '复制pdb或map压缩文件: ' + '(生成时间:' + str(
                fileCreateTime) + ')' + '从' + pdbtarfilename+ '到' + dst_file + '\n')
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
            
    # 备份pdb
    def backupPdb(self):
        for src_dir in self.__src_dir_list:
            print 'Backup pdb : ' + src_dir
            self.__doBackupDir(src_dir)
        if self.tarPdbFile():
            if self.copyPdbTarFile():
                if not self.rmTempDir():
                    raise Exception('删除临时备份文件出错。')
            else:
                raise Exception("复制压缩pdb文件至ftp出错")
        else:
            raise Exception("压缩pdb文件出错")

    # 构造函数
    def __init__(self, version, src_dir_list, pdb_dir, platform):
        self.__version = version
        self.__pdb_dir = pdb_dir
        self.__src_dir_list = src_dir_list
        self.__platform = platform
        self.__tmp_dir = r"E:\pdb" + '\\' + self.__version + '\\' + self.__platform

# if __name__ == "__main__":
#     pdbbacker = PdbBackuper("0.0.0.0",[r"I:\sourcecode\workspace\oa_test_client_changanjijin_20150720\XtItsmClient\tags\changanjijin_20150720\_runtime\Win32.Release", r"I:\sourcecode\workspace\oa_test_client_changanjijin_20150720\server5\quoter\branches\multiconn_20141105\_runtime\Win32.Release"] , r"\\192.168.1.250\khd\pdb\XtAmpTradeClient", "W32")
#     pdbbacker.backupPdb()