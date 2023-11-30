import os
import sys
import shutil
import threading
import subprocess
import xml.etree.ElementTree as ET
sys.dont_write_bytecode = True
sys.stdout.reconfigure(encoding='utf-8')

'''
def _GetScriptPath(in_file):
  #script_directory = os.path.abspath(__file__)
  #parent_directory = os.path.join(script_directory, os.pardir)
  #return parent_directory
  script_path = os.path.dirname(os.path.abspath(in_file))
  #return script_path+"\\"
  return os.path.join(script_path,"","")
'''


def _GetScriptPath(in_file):
    # 获取脚本所在目录的绝对路径
    script_directory = os.path.dirname(os.path.abspath(in_file))
    return script_directory

def _DeleteTargetDir(in_dir):
  result=False
  norm_path = os.path.normpath(in_dir)
  if os.path.isdir(norm_path) :
    shutil.rmtree(norm_path)
    result=True
  return result

def _PyPath(in_path):
  result=in_path
  norm_path = os.path.normpath(result)
  result = result.replace("\\", "/")
  return result
   

def _CmakeConfigureAndBuildOnMSVC():
  return 0
