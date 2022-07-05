#! /usr/local/bin/python3
#
# Minimum python version: 3.5

import argparse
import glob
import os
import subprocess

from collections import namedtuple

KEYMAP_PREFIX = os.environ['USER']

def log_info(msg, gap_above=False):
    print('%s\033[36mINFO: %s\033[m' % ('\n' if gap_above else '', msg))

def log_warning(msg, gap_above=False):
    print('%s\033[33mINFO: %s\033[m' % ('\n' if gap_above else '', msg))

def log_error(msg, gap_above=False):
    print('%s\033[31mERROR: %s\033[m' % ('\n' if gap_above else '', msg))

class ShellOutput(namedtuple('ShellOutput', 'stdout stderr')):
    pass

# Note: when output_to_shell is enabled, stdout/stderr are not returned
def run_cmd(cmd, additional_env={}, output_to_shell=True):
    new_env = os.environ.copy()
    for k in additional_env:
        new_env[k] = additional_env[k]
    if output_to_shell:
        # prints stdout and stderr to the shell
        subprocess.run(cmd, env=new_env)
        return None
    else:
        result = subprocess.run(cmd, env=new_env, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        return ShellOutput(
                result.stdout.decode('UTF-8'),
                result.stderr.decode('UTF-8'))

def update_qmk_firmware_code(qmk_firmware_root):
    log_info('Updating qmk_firmware code', gap_above=True)
    saved_dir = os.getcwd()
    if not os.path.exists(qmk_firmware_root):
        # TODO: 'https://github.com/qmk/qmk_firmware.git'
        run_cmd(['git', 'clone', 'https://github.com/eyuelt/qmk_firmware.git', qmk_firmware_root])
        run_cmd(['make', 'git-submodule', '-C', qmk_firmware_root])
        return
    os.chdir(qmk_firmware_root)
    run_cmd(['git', 'pull'])
    os.chdir(saved_dir)

def link_keymap_files(project_root, qmk_firmware_root, keyboard, keymap_dir_name, keymap_name):
    symlink_dest = os.path.join(project_root, keymap_dir_name)
    keymaps_dir = os.path.join(qmk_firmware_root, 'keyboards', keyboard, 'keymaps')
    # make the keymaps directory in case it doesn't exist
    run_cmd(['mkdir', keymaps_dir], output_to_shell=False)
    symlink_name = os.path.join(keymaps_dir, keymap_name)
    log_info('Linking "%s" to "%s"' % (symlink_dest, symlink_name), gap_above=True)
    # the -hf flags make it so the existing directory symlink is replaced each time
    run_cmd(['ln', '-shf', symlink_dest, symlink_name])

def compile_keymap(qmk_firmware_root, keyboard, keymap_name):
    log_info('Compiling with `qmk compile -kb "%s" -km "%s"`' % (keyboard, keymap_name), gap_above=True)
    # Note: this sets the config globally
    run_cmd(['qmk', 'config', 'user.qmk_home=%s' % qmk_firmware_root])
    # Note: this may fail if git submodules are out of date, in which case we need to run 'make git-submodule'
    run_cmd(['qmk', 'compile', '-kb', keyboard, '-km', keymap_name])

def move_hex_file_to_root_dir(project_root, qmk_firmware_root, keyboard, keymap_name):
    hex_file_name = '%s_%s.hex' % (keyboard.replace('/', '_'), keymap_name)
    old_path = os.path.join(qmk_firmware_root, hex_file_name)
    new_path = os.path.join(project_root, hex_file_name)
    run_cmd(['mv', old_path, new_path], output_to_shell=False)
    log_info('Firmware file output: %s' % new_path, gap_above=True)

def clean(project_root, qmk_firmware_root):
    log_info('Removing generated files', gap_above=True)
    if 'qmk_firmware' not in os.path.abspath(qmk_firmware_root):
        log_error('Unexpected qmk_firmware_root %s. Aborting rm -rf.' % qmk_firmware_root);
        return
    run_cmd(['rm', '-rf', qmk_firmware_root], output_to_shell=False)
    for hex_file in glob.glob(os.path.join(project_root, '*.hex')):
        run_cmd(['rm', hex_file], output_to_shell=False)

def keymap_dirs(project_root):
    # find all dirs directly under the project_root that contain a keymap.c
    # TODO: change this to look for the per-keymap-dir config file instead of keymap.c
    glob_pattern = os.path.join(project_root, '*', 'keymap.c')
    return [os.path.basename(os.path.dirname(x)) for x in glob.glob(glob_pattern)]

# set up args
def parse_args(project_root):
  parser = argparse.ArgumentParser(description='Build QMK firmware with custom keymaps.')
  parser.add_argument('keymap_dir', nargs='?', choices=keymap_dirs(project_root), type=str, help='the keymap directory to build (must be under project root)')
  parser.add_argument('-kb', '--keyboard', type=str, default=None, help='the QMK keyboard that this keymap is for')
  parser.add_argument('--clean', action='store_true', default=False, help='delete generated files')
  return parser.parse_args()

def main():
    project_root = os.path.abspath(os.path.dirname(__file__))
    args = parse_args(project_root)
    qmk_firmware_root = os.path.join(project_root, 'qmk_firmware')
    os.chdir(project_root)  # change working dir to project root
    print('Project root: %s' % project_root)
    if args.clean:
        clean(project_root, qmk_firmware_root)
    if args.keymap_dir is None or '/' in args.keymap_dir or not os.path.isdir(os.path.join(project_root, args.keymap_dir)):
        log_error('Invalid keymap_dir: %s' % args.keymap_dir)
        return
    keymap_name='%s_%s' % (KEYMAP_PREFIX, args.keymap_dir)
    if args.keyboard is not None:
        keyboard = args.keyboard
    else:
        keyboard = 'crkbd/rev1'  # TODO: get it from a per-keymap-dir config
    if not os.path.isdir(os.path.join(qmk_firmware_root, 'keyboards', keyboard)):
        log_error('Invalid keyboard: %s' % keyboard)
        return

    update_qmk_firmware_code(qmk_firmware_root)
    link_keymap_files(project_root, qmk_firmware_root, keyboard, args.keymap_dir, keymap_name)
    compile_keymap(qmk_firmware_root, keyboard, keymap_name)
    move_hex_file_to_root_dir(project_root, qmk_firmware_root, keyboard, keymap_name)

if __name__ == '__main__':
    main()
