# THIS IS THE MAIN CONFIGUARATION FILE - WHERE REAL WORK IS DONE

import lit.formats

config.name = 'Test LLVM Passes'
config.test_format = lit.formats.ShTest(True)

config.suffixes = ['.c', '.cpp', '.cc', '.py']

config.test_source_root = os.path.dirname(__file__)

# by default the 'Output' folder is created next to the test case, inside the test suite directory
# this line tells lit to put it inside the build folder (where the object file is).
config.test_exec_root = os.path.join(config.build_dir, 'test')

# here I am creating a custom substitution which represent the path to the binaries I am testing
config.substitutions.append(('%profile_all_ops',
                             os.path.join(config.build_dir, 'libAllOpsProfile.so')))
config.substitutions.append(('%replace_multiply',
                             os.path.join(config.build_dir, 'libReplaceMultiply.so')))

config.suffixes = ['']
config.enable_bindings_python = 1
config.do_whatever_i_want = "i am humble" # "conquer the world"