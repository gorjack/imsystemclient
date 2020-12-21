# -*- coding:gbk -*-

# ��׼��
import sys
import os

# �Զ����
sys.path.append('../../../_xtPlatform/script/python/')
import Util

import xtCommon
import Config
import Mail


# ������
def mainProc(config_file_name):
    
    print '���ڶ�ȡ���á���'
    conf = Config.Config(config_file_name)
    conf.parseConfig()

    print '���ڸ����ļ�����'
    util = Util.Util()
    version = conf.getVersion(conf.rc_conf.ver_major, conf.rc_conf.ver_minor, conf.rc_conf.ver_revision)
    out_file = conf.outputFile(version)
    print '�ļ� ' + out_file + ' �� ' + conf.output_dir + ' �� ' + conf.publish_dir
    util.copyFile(conf.output_dir, conf.publish_dir, out_file)

    print '���ڷ��ͷ����ɹ��ʼ�����'
    mail = Mail.BuildMail()
    mail.sendBuildSuccessMail(conf.publish_download_url + out_file, conf.product_name_cn, '', conf.publish_dst_addr)

    print '\n\n�������̳ɹ���\n--------------------------------------------------'
    os.system('pause')


# �ű����
if '__main__' == __name__:
    if len(sys.argv) <= 1:
        print '\nUsage : Publish.py [config.ini]'
        os.system('pause')
        print ''
    else:
        mainProc(sys.argv[1])

