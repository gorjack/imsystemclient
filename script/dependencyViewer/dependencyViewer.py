# encoding=gbk

import os
import sys
import traceback

header_to_project = {}
project_to_cpp = {}
cpp_to_object = {}
object_to_header = {}

cpp_keywords = {}

def get_file_name(line):
    seg_index = line.rfind('\\')
    seg_index2 = line.rfind('/')
    if seg_index2 > seg_index:
        seg_index = seg_index2
    quota_index = line.rfind('"')
    if seg_index >= 0:
        if quota_index >= 0 and quota_index > seg_index:
            return line[seg_index + 1 : quota_index]
        else:
            return line[seg_index + 1 : ]
    return ''


def is_match(s, patterns):
    for p in patterns:
        if s == p:
            return True
    return False


def get_first_index(s, patterns, start_index):
    first_index = -1
    first_pattern = ''
    for p in patterns:
        i = s.find(p, start_index)
        if i >= 0 and (first_index < 0 or i < first_index):
            first_index = i
            first_pattern = p
    return [first_pattern, first_index]


def is_valid_object(object_name):
    if len(object_name) == 0:
        return False
    if object_name[0] == 'Q':
        return False
    if cpp_keywords.has_key(object_name):
        return False
    for t in object_name:
        is_valid = (t >= 'a' and t <= 'z') or (t >= 'A' and t <= 'Z') or (t >= '0' and t <= '9')
        if not is_valid:
            return False
    return True


def process_proj_file(file_name):
    # print 'processing file \"' + file_name + '\" :'
    f = open(file_name)
    proj_name = get_file_name(file_name)
    dot_index = proj_name.rfind('.')
    if dot_index >= 0:
        proj_name = proj_name[0 : dot_index]
    project_to_cpp[proj_name] = {}
    try:
        lines = f.readlines()
        for line in lines:
            rel_path_index = line.find('RelativePath=')
            cpp_index = line.find('.cpp\"')
            h_index = line.find('.h\"')
            moc_index = line.find('moc_')
            if rel_path_index >= 0 and moc_index < 0:
                if cpp_index >= 0:
                    cpp_file_name = get_file_name(line)
                    if len(cpp_file_name) > 0 and cpp_file_name.upper() != 'STDAFX.CPP':
                        project_to_cpp[proj_name][cpp_file_name] = True
                elif h_index >= 0:
                    h_file_name = get_file_name(line)
                    if len(h_file_name) > 0 and h_file_name.upper() != 'STDAFX.H':
                        header_to_project[h_file_name] = proj_name
    except:
        traceback.print_exc()
        os.system('pause')
    finally:
        f.close()


class_search_start = [' ', '\t', '(', '::']
class_search_end = [' ', '\t', '<', '*', '::', '(']
function_search_start = [' ', '\t', '::']
function_search_end = ['(']


def process_cpp_line(line, search_start, search_end, real_name):
    p_and_index = get_first_index(line, search_start, 0)
    # print str(p_and_index[0]) + '=' + str(p_and_index[1]) + '|' + line
    # os.system('pause')
    while p_and_index[1] >= 0:
        word_start_index = p_and_index[1] + len(p_and_index[0])
        while (word_start_index < len(line)) and is_match(line[word_start_index], search_start):
            word_start_index += 1
        if word_start_index >= len(line):
            break
        next_p_and_index = get_first_index(line, search_end, word_start_index)
        if next_p_and_index[1] >= 0:
            object_name = line[word_start_index : next_p_and_index[1]]
            if is_valid_object(object_name):
                # print line + ' :\t(' + str(len(object_name)) + ')\t' + object_name
                # os.system('pause')
                cpp_to_object[real_name][object_name] = True
            p_and_index = get_first_index(line, search_start, next_p_and_index[1])
        else:
            object_name = line[word_start_index : ]
            if is_valid_object(object_name):
                # print line + ' :\t(' + str(len(object_name)) + ')\t' + object_name
                # os.system('pause')
                cpp_to_object[real_name][object_name] = True
            break


def process_cpp_file(file_name):
    # print 'processing file \"' + file_name + '\" :'
    real_name = get_file_name(file_name)
    cpp_to_object[real_name] = {}
    f = open(file_name)
    try:
        lines = f.readlines()
        for line in lines:
            process_cpp_line(line, class_search_start, class_search_end, real_name)
            process_cpp_line(line, function_search_start, function_search_end, real_name)
    except:
        traceback.print_exc()
        os.system('pause')
    finally:
        f.close()


def process_header_line(line, search_start_index, space_pattern, end_pattern, file_name):
    [res_space_pattern, space_index] = get_first_index(line, space_pattern, search_start_index)
    if space_index >= 0:
        start_index = space_index + 1
        while start_index < len(line) and is_match(line[start_index], [' ', '\t']):
            start_index += 1
        if start_index < len(line):
            [res_end_pattern, end_index] = get_first_index(line, end_pattern, start_index)
            if end_index >= 0:
                object_name = line[start_index : end_index]
                if cpp_keywords.has_key(object_name):
                    process_header_line(line, start_index, space_pattern, end_pattern, file_name)
                else:
                    object_to_header[object_name] = get_file_name(file_name)


def process_header_file(file_name):
    # print 'processing file \"' + file_name + '\" :'
    f = open(file_name)
    try:
        lines = f.readlines()
        for line in lines:
            dll_export_index = line.find('DLL_EXPORT')
            if dll_export_index >= 0:
                class_pattern = 'class '
                class_index = line.find(class_pattern)
                struct_pattern = 'struct '
                struct_index = line.find(struct_pattern)
                if class_index >= 0 and class_index < dll_export_index:
                    process_header_line(line, dll_export_index, [' ', '\t'], [' ', '\t', ':'], file_name)
                elif struct_index >= 0 and struct_index < dll_export_index:
                    process_header_line(line, dll_export_index, [' ', '\t'], [' ', '\t', ':'], file_name)
                else:
                    [ret_space_pattern, space_index] = get_first_index(line, [' ', '\t'], dll_export_index)
                    ret_start_index = space_index + 1
                    while is_match(line[ret_start_index], [' ', '\t']):
                        ret_start_index += 1
                    process_header_line(line, ret_start_index, [' ', '\t', '*', '&'], [' ', '\t', '('], file_name)
    except:
        traceback.print_exc()
        os.system('pause')
    finally:
        f.close()


def read_keywords():
    print 'read cpp keywords'
    f = open('keywords.txt')
    try:
        lines = f.readlines()
        for line in lines:
            k = line
            [ret_pattern, ret_index] = get_first_index(line, ['\r', '\n'], 0)
            if ret_index >= 0:
                k = line[0 : ret_index]
            cpp_keywords[k] = True
    except:
        traceback.print_exc()
        os.system('pause')
    finally:
        f.close()


def walk_dir(src_dir):
    print 'processing directory \"' + src_dir + '\" :'
    for parent, dirnames, filenames in os.walk(src_dir):
        for f in filenames:
            src_file = src_dir + '\\' + f
            if os.path.isfile(src_file):
                idx = f.rfind('.')
                if (idx >= 0):
                    file_postfix_name = f[idx + 1 : len(f)]
                    if file_postfix_name.upper() == 'H':
                        process_header_file(src_file)
                    elif file_postfix_name.upper() == 'CPP' and f.find('moc_') < 0:
                        process_cpp_file(src_file)
                    elif file_postfix_name.upper() == 'VCPROJ':
                        process_proj_file(src_file)
        for d in dirnames:
            src_sub_dir = src_dir + '\\' + d
            walk_dir(src_sub_dir)


def filter_objects():
    print ''
    print 'start filtering objects'
    for (cpp_file, objects) in cpp_to_object.items():
        for (item, o) in objects.items():
            if not object_to_header.has_key(item):
                objects.pop(item)
    print 'filter done'
    print ''


def print_table1(f, tbl, tag):
    print 'table ' + tag + ':'
    f.write('\n')
    f.write('------------------------------\n')
    f.write('' + tag + ' : \n')
    f.write('------------------------------\n')
    for (k, v) in tbl.items():
        f.write(k + ' :\t' + v + '\n')
    f.write('\n')


def print_table2(f, tbl, tag):
    print 'table ' + tag + ':'
    f.write('\n')
    f.write('------------------------------\n')
    f.write('' + tag + ' : \n')
    f.write('------------------------------\n')
    for (k, v) in tbl.items():
        f.write(k + ':\n')
        for (sub_k, sub_v) in v.items():
            f.write('    ' + sub_k + '\n')
    f.write('\n')


def print_mid_res():
    print 'output middle results:'
    f = open('mid_res.txt', 'wt')
    print_table1(f, header_to_project, 'header_to_project')
    print_table2(f, project_to_cpp, 'project_to_cpp')
    print_table2(f, cpp_to_object, 'cpp_to_object')
    print_table1(f, object_to_header, 'object_to_header')
    f.close()


def print_final_res():
    print 'output final results:'
    f1 = open('final_res.csv', 'wt')
    f2 = open('final_res_without_self.csv', 'wt')
    f1.write('原始工程,依赖工程,原始工程文件,依赖对象,依赖头文件\n')
    f2.write('原始工程,依赖工程,原始工程文件,依赖对象,依赖头文件\n')
    for (proj, cpps) in project_to_cpp.items():
        for cpp in cpps:
            if cpp_to_object.has_key(cpp):
                objects = cpp_to_object[cpp]
                for (obj, o) in objects.items():
                    if object_to_header.has_key(obj):
                        h_file = object_to_header[obj]
                        if header_to_project.has_key(h_file):
                            rely_proj = header_to_project[h_file]
                            f1.write('%s,%s,%s,%s,%s\n' % (proj, rely_proj, cpp, obj, h_file))
                            if rely_proj != proj:
                                f2.write('%s,%s,%s,%s,%s\n' % (proj, rely_proj, cpp, obj, h_file))
    f1.close()
    f2.close()


if '__main__' == __name__:

    read_keywords()
    walk_dir(os.path.abspath('.'))
    filter_objects()
    print_mid_res()
    print_final_res()
    
    os.system('pause')

