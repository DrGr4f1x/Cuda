'''
Copyright (c) Microsoft. All rights reserved.
This code is licensed under the MIT License (MIT).
THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.

Developed by Minigraph

Author:  James Stanard
'''

import os
import sys
import shutil
from glob import glob
from uuid import uuid4

TEMPLATES_FOLDER = "./Programs/ProjectGen/Templates"

def copy_template_file(filename, project, project_dir, guid):
    '''Copies one template file and replaces templated values'''
    template_filename = os.path.join(TEMPLATES_FOLDER, filename)
    output_filename = os.path.join(project_dir, project)
    output_filename = os.path.join(output_filename, filename)
    output_filename = output_filename.replace('TEMPLATE', project)
    with open(template_filename, 'r', encoding='utf-8') as infile:
        with open(output_filename, 'w', encoding='utf-8') as outfile:
            contents = infile.read()
            contents = contents.replace('TEMPLATE_GUID', guid)
            contents = contents.replace('TEMPLATE_NAME', project)
            contents = contents.replace('TEMPLATE', project)
            outfile.write(contents)

def copy_app_template(project, project_dir, guid):
    '''Instantiates a new solution from a template'''
    copy_template_file('Stdafx.h', project, project_dir, guid)
    copy_template_file('Stdafx.cpp', project, project_dir, guid)
    copy_template_file('Main.cpp', project, project_dir, guid)
    copy_template_file('TEMPLATE.vcxproj', project, project_dir, guid)
    copy_template_file('TEMPLATE.vcxproj.filters', project, project_dir, guid)

def create_project():
    if len(sys.argv) != 3:
        print(f'Usage:  {sys.argv[0]} <ProjectDir> <ProjectName>')
        return

    project_dir = sys.argv[1]
    project_name = sys.argv[2]

    folder_contents = set(os.listdir())
    project_folder_contents = set(os.listdir(project_dir))
    expected_contents = set(['Deep-Learning-Cpp', 'External', 'Programs'])
    if not expected_contents.issubset(folder_contents):
        print('Run this script from the root of Deep-Learning')
    elif project_name in project_folder_contents:
        print('Project already exists')
    else:
        new_project_dir = os.path.join(project_dir, project_name)
        os.mkdir(new_project_dir)
        copy_app_template(project_name, project_dir, str(uuid4()).upper())
        

if __name__ == "__main__":
    create_project()
