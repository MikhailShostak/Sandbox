import os

ROOT = os.path.dirname(os.path.realpath(__file__))

with open(os.path.join(ROOT, 'Legacy.pch.hpp'), 'w') as f:
    f.write('#pragma once\n\n')
    f.write('#include <ThirdParty.pch.hpp>\n\n')
    for root, dirs, files in os.walk(ROOT):
        if root == ROOT:
            continue
        for file in files:
            path = root + '/' + file
            path = path.replace('\\', '/')
            if file.endswith('.h') or file.endswith('.hpp'):
                f.write('#include "{}"\n'.format(path[len(ROOT) + 1:]))
