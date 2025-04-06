import pexpect
import unittest

# the erl executable
cmd = './erl'

class TestCLI(unittest.TestCase):

    def test_erl(self):
        # Run the encoder
        args = ' ./preprocessorTestFile.txt ./defaultdictionary.txt ./pythonout.erl '
        (output, retcode) = pexpect.run(cmd + args, withexitstatus=True, extra_args=args)
        self.assertEqual(retcode, 0)
        output = output.strip()

        # Check the output has the correct format
        required_substrings = [
            b"Size of original:",
            b"Size of erl:",
            b"Size Reduction:",
            b"Hit Rate:"
        ]
        all_present = all(sub in output for sub in required_substrings)
        self.assertTrue(all_present)

        # Run the decoder
        args = ' ./pythonout.erl ./defaultdictionary.txt ./pythonout.txt '
        (output, retcode) = pexpect.run(cmd + args, withexitstatus=True, extra_args=args)
        self.assertEqual(retcode, 0)
        output = output.strip()

        # Check the output has the correct format
        required_substrings = [
            b"Size of erl:",
            b"Size of decoded:",
        ]
        all_present = all(sub in output for sub in required_substrings)
        self.assertTrue(all_present)

        # Check that the text is roughly the same
        with open('preprocessorTestFile.txt', 'r') as file:
            original_contents = file.read()
        with open('pythonout.txt', 'r') as file:
            decoded_contents = file.read()
        
        # Assume all lowercase
        original_contents = original_contents.lower()

        required_substrings = [
            "the sun was setting over the horizon",
            "watching the world go by",
            "i noticed a young couple walking hand",
            "i began to daydream about my own trips",
            "but as the sun dipped lower and the sky turned darker",
            "as i stood up to leave"
        ]

        all_present_original = all(sub in original_contents for sub in required_substrings)
        all_present_decoded = all(sub in decoded_contents for sub in required_substrings)

        self.assertTrue(all_present_original and all_present_decoded)
        return

# run the tests
unittest.main()
