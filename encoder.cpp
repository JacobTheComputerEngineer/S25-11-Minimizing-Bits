#include "encoder.h"

bool encoder_::printWord(bit_code_13_ code, std::string filename)
{
	buffer.reset(index);	// Prepending the '0' tag bit
	index--;				// Shift the index for the buffer right one
	if (index == -1)		// If end of buffer is reached
	{
		index = 7;			// Reset index
		if (!(appendToFile(filename)))	// Append "full" buffer to output .erl file
		{
			return false;
		}
	}
	for (int i = code.size() - 1; i >= 0; i--)	// Traverses code bitstring, from left to right
	{
		if (code.test(i))	// If a 1 is present at the index i in code bitstring
		{
			buffer.set(index);		// Set bit in buffer to '1'
			index--;				// Shift the index for the buffer right one
			if (index == -1)		// If end of buffer is reached
			{
				index = 7;			// Reset index
				if (!(appendToFile(filename)))	// Append "full" buffer to output .erl file
				{
					return false;
				}
			}
		}
		else
		{
			buffer.reset(index);	// Set bit in buffer to '0'
			index--;				// Shift the index for the buffer right one
			if (index == -1)		// If end of buffer is reached
			{
				index = 7;			// Reset index
				if (!(appendToFile(filename)))	// Append "full" buffer to output .erl file
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool encoder_::printCharacter(bit_code_6_ code, std::string filename)
{
	buffer.set(index);		// Prepending the '1' tag bit
	index--;				// Shift the index for the buffer right one
	if (index == -1)		// If end of buffer is reached
	{
		index = 7;			// Reset index
		if (!(appendToFile(filename)))	// Append "full" buffer to output .erl file
		{
			return false;
		}
	}
	for (int i = code.size() - 1; i >= 0; i--)	// Traverses code bitstring, from left to right
	{
		if (code.test(i))	// If a 1 is present at the index i in code bitstring
		{
			buffer.set(index);		// Set bit in buffer to '1'
			index--;				// Shift the index for the buffer right one
			if (index == -1)		// If end of buffer is reached
			{
				index = 7;			// Reset index
				if (!(appendToFile(filename)))	// Append "full" buffer to output .erl file
				{
					return false;
				}
			}
		}
		else
		{
			buffer.reset(index);	// Set bit in buffer to '0'
			index--;				// Shift the index for the buffer right one
			if (index == -1)		// If end of buffer is reached
			{
				index = 7;			// Reset index
				if (!(appendToFile(filename)))	// Append "full" buffer to output .erl file
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool encoder_::appendToFile(std::string filename)
{
	if (write.is_open())									// If file was properly opened
	{
		unsigned long n = buffer.to_ulong();				// Convert buffer contents to long
		write.write(reinterpret_cast<const char*>(&n), 1);	// Append encoding by appending the binary of the character represented by the contents of buffer
		//write.close();										// Close the file
	}
	else
	{
		return false;										// Return false if malfunction, e.g. file couldn't be created/found
	}
	return true;
}

void encoder_::setOutputFile(std::string filename) {
	write = std::ofstream(filename, std::ios::app | std::ios::binary);		// Open output stream to indicated binary file
}

void encoder_::closeOutputFile() {
	write.close();
}