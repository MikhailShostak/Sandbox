import os
import subprocess
import sys

ADDITIONAL_CONAN_COMMANDS = [arg for arg in ['--keep-source', '--keep-build'] if arg in sys.argv]
BUILD_DIR = os.environ.get('BUILD_DIR', '.build')
ARCHITECTURES = [os.environ['BUILD_ARCHITECTURE']] if 'BUILD_ARCHITECTURE' in os.environ else ['x86_64']
CONFIGURATIONS = [os.environ['BUILD_CONFIGURATION']] if 'BUILD_CONFIGURATION' in os.environ else ['Release', 'Debug']
DRY_RUN = '--dry-run' in sys.argv
LOCAL_PACKAGES = [

]


def run(command, *args, **kwargs):
    print(*command, *args, **kwargs)
    if not DRY_RUN:
        subprocess.check_call(command + [], *args, **kwargs)


def create_package(package, profile):
    conan_command = ['conan', 'create'] + package + ['--profile', profile, '--test-folder', 'None'] + ADDITIONAL_CONAN_COMMANDS
    run(conan_command)


if '--install-conan' in sys.argv:
    run([sys.executable, '-m', 'pip', 'install', 'conan'])

for arch in ARCHITECTURES:
    for config in CONFIGURATIONS:
        profile =  config + '-' + arch
        if '--create-profile' in sys.argv:
            run(['conan', 'profile', 'new', profile, '--detect', '--force'])
            run(['conan', 'profile', 'update', 'settings.build_type=' + config, profile])
            run(['conan', 'profile', 'update', 'settings.arch=' + arch, profile])
            run(['conan', 'profile', 'update', 'settings.arch_build=' + arch, profile])

        if '--keep-remote-packages' not in sys.argv:
            run(['conan', 'install', '.', '-if', os.path.join(BUILD_DIR, profile)] + ['--profile', profile, '--update', '--build=missing'])

        if '--keep-local-packages' not in sys.argv:
            for package in LOCAL_PACKAGES:
                create_package(package, profile)
