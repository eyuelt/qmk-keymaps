#!/bin/bash


script_dir="$(pwd)"  # TODO: change this, since we may not be running this in the expected directory)
qmk_home="./qmk_firmware" # TODO: if the directory doesn't exist, we'll need to clone. if it does, we need to make sure it has no pending git changes and is up to date. (func: prepareQmkHome)

keyboard="crkbd/rev1"  # TODO
keymap="eyuelt_corne"  # TODO: (this is determined by prepending the path_to_file basename with "eyuelt_")

# no point continuing if we won't be able to do the compile later
qmk_version="$(brew ls --versions qmk/qmk/qmk 2>/dev/null)";
if [[ $? -ne 0 ]]
then
  echo "QMK command line tool not found";
  exit 1
fi

file_to_symlink="${script_dir}/corne"  # TODO: don't use "." here, because then the symlink will be relative
symlink_name="./qmk_firmware/keyboards/${keyboard}/keymaps/${keymap}"  # TODO: (don't rely on "." since we may not be running this in the expected directory)
mkdir "$(dirname ${symlink_name})" 2>/dev/null;  # in case the keymaps directory doesn't exist
ln -shf "${file_to_symlink}" "${symlink_name}";  # the -hf flags make it so it replaces the directory symlink each time

cd $qmk_home
git pull 1>/dev/null
qmk compile -kb "${keyboard}" -km "${keymap}"
cd $script_dir
mv "${qmk_home}/$(echo $keyboard | sed "s/\//_/g")_${keymap}.hex" "${script_dir}"


# # maybe also get this from the cmd line flag
# qmk_home="$(qmk config user.qmk_home)";
# if [[ $qmk_home -eq "user.qmk_home=None" ]]
# then
#   echo "QMK_HOME not provided";
#   exit 1
# fi

# qmk_home="$(qmk config user.keyboard)";
# if [[ $qmk_home -eq "user.keyboard=None" ]]
# then
#   echo "keyboard not specified";
#   exit 1
# fi

# TODO: make sure qmk_home exists

#if i say "make corne"
#then
#  assert qmk tool is installed
#  get qmk_firmware_path from qmk tool ("qmk config user.qmk_home") (or from the commandline args to this job)
#  assert qmk_firmware_path exists
#  assert qmk_firmware repo has no pending changes
#  copy over the files to the appropriate place in qmk_firmware repo (maybe create a new branch. what if there are pending changes? git stash?)
#  after that, do a "qmk compile -kb crkbd/rev1 -km <keymap-name>"
#  copy (or move) the generated file over
#fi
