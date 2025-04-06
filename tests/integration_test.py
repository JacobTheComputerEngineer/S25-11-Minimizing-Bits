import pexpect
import pexpect.replwrap as replwrap
import unittest

# the erl executable
cmd = './erl'


class TestCLI(unittest.TestCase):

    def test_example(self):
        # args = ' -e "(4 2 -)" '
        # (output, retcode) = pexpect.run(cmd + args, withexitstatus=True, extra_args=args)
        # self.assertEqual(retcode, 0)
        # self.assertEqual(output.strip(), b"(2)")
        return

# TODO: Add more specific tests later

# run the tests
unittest.main()
