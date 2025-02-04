import pexpect
import pexpect.replwrap as replwrap
import unittest

# the erl executable
cmd = './erl'

# the prompt to expect
prompt = u'erl>'

# These are example tests to show how to interact with REPL and CLI
# Commented out for now so it runs
class TestREPL(unittest.TestCase):

    def setUp(self):
        # self.wrapper = replwrap.REPLWrapper(cmd, prompt, None)
        return

    def test_example(self):
        # output = self.wrapper.run_command(u'(1 2 +)')
        # self.assertEqual(output.strip(), "(3)")
        return       


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
