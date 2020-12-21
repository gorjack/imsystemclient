# -*- coding:gbk -*-

# ��׼��
import sys
import traceback
import os
import shutil
import time
import win32api

# �Զ����
sys.path.append('../../../_xtPlatform/script/python/')
sys.path.append('../../../libs/_xtPlatform/runtime/script/python/')
import BuildModule
import Solution
import Timer

import xtCommon
import Config
import Packer
import Mail
import Util
import PackLog


pack_log = PackLog.pack_log

# ����ʼ�����
def mailSubject(conf):
    tag_name = 'Module' + str(3)
    try:
        platform = conf.conf_parser.get(tag_name, 'platform')
    except:
        platform = 'win32'
    subject = conf.product_name_cn + ' ' + conf.version + ' ' + '[' + platform + ']'
    return subject

# ��֤�����
def checkLock(lock_file_name):
    lock_file = 'd:\\' + lock_file_name
    if os.path.isfile(lock_file):
        print '��һ������ű��������У���ȴ���������ٴ����'
        os.system('pause')
        exit()
    f = file(lock_file, 'w')
    f.close()
    return lock_file


# ��ӡexception���ҷ�ʧ���ʼ����û��������˳���
def exceptQuit(lock_file, conf, build_log = ''):
    os.remove(lock_file)
    traceback.print_exc()
    subject = mailSubject(conf)   
    mail = Mail.BuildMail()
    mail.sendBuildFailMail(subject, build_log, conf.fail_dst_addr)
    print ''
    os.system('pause')
    exit()


def curFilePath():
    path = sys.path[0]
    if os.path.isdir(path):
        return path
    elif os.path.isfile(path):
        return os.path.dirname

def waitThreads(threads):
    allDone = False
    while not allDone:
        time.sleep(0.1)
        allDone = True
        for t in threads:
            if Solution.SOLUTION_STATUS_ERROR == t.status():
                for t1 in threads:
                    t1.stop()
                return [False, t.log()]
            elif Solution.SOLUTION_STATUS_FINISHED != t.status():
                allDone = False
                #print t.solutionName() + ' has not finished,' + ' status:' + str(t.status())
                pack_log.writeLog('\n' + t.solutionName() + ' has not finished,' + ' status:' + str(t.status()))
    return [True, '']

def waitThreads_splitsthread(splitsthread):
    allDone = False
    while not allDone:
        time.sleep(0.1)
        allDone = True
        for st in splitsthread:
            if Solution.SOLUTION_STATUS_ERROR == st.status():
                for st1 in splitsthread:
                    st1.stop()
                return [False, st.log()]
            elif Solution.SOLUTION_STATUS_FINISHED != st.status():
                allDone = False
                #print t.solutionName() + ' has not finished,' + ' status:' + str(st.status())
                pack_log.writeLog('\n' + st.solutionName() + ' has not finished,' + ' status:' + str(st.status()))
    return [True, '']


def showBuildTime(the_timer):
    pack_log.writeLog('\n' + the_timer.name() + '�����ʱ' + str(the_timer.mins) + '��' + str(the_timer.secs) + '�롣')
    print the_timer.name() + '�����ʱ' + str(the_timer.mins) + '��' + str(the_timer.secs) + '�롣'


def showTime(the_timer):
    pack_log.writeLog('\n' + the_timer.name() + '��ʱ' + str(the_timer.mins) + '��' + str(the_timer.secs) + '�롣')
    print the_timer.name() + '��ʱ' + str(the_timer.mins) + '��' + str(the_timer.secs) + '�롣'


# ������
def mainProc(config_file_name, lock_file_name):
    # ��ȡ����
    conf = Config.Config(config_file_name)
    conf.parseConfig()

    total_timer = Timer.Timer(1, conf.product_name_cn + '�����������')
    
    
    if True:
        print '***********************��ʼ���***************************'
        print '*********************************************************'
        try:
            win32api.SetConsoleTitle(conf.product_name_cn + ' ' + ' �������ɡ���')

            # ����NSIS���ɰ�װ��
            print '���ɰ�װ�ļ�'
            packer = Packer.Packer(conf)
            packer.packInstaller()
            


            print '�ͻ���pack�ű��ƺ������'
        except:
            print 'error'
    else:
        print '***********************packʧ��**************************'
        print '*********************************************************'
        print '***********************�˳�����**************************'
        print '*********************************************************'
        exceptQuit(lock_file, conf, all_log)

# �ű����
if '__main__' == __name__:
    if len(sys.argv) <= 2:
        print '\nUsage : Build.py [config_ini] [lock_file]'
        os.system('pause')
        print ''
    else:
        mainProc(sys.argv[1], sys.argv[2])
        f = file("%s\\packagestatus.txt" %(os.path.abspath('.')[0:2]), 'w')
        f.close()
