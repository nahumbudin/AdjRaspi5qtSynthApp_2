/**
 *	@file		utils.cpp
 *	@author		Nahum Budin
 *	@date		27-June-2026
 *	@version	1.1
 *					1. Added a time guard to the rotary encoder value update function to avoid too fast updates.
 *
 *	@brief		Utilities.
 *
 *	History:\n
 *		Version 1.0	12-Jul-2024
 */

#include <bits/stdc++.h>

#include <iostream>
#include <string>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <chrono>

#include "utils.h"


/**
 * Strips the client name prefix (prefix:name -> name)
 *
 * @param name the full client name 
 * @return the stripped name
 */
std::string strip_client_name_prefix(std::string name)
{
	int prefix_end = name.find_first_of(':');

	if (prefix_end != std::string::npos)
	{
		return name.substr(prefix_end + 1, name.length() - 1);
	}

	return name;
}

/**
 * Replaces whit spaces with a backslash and a space (abc de f -> abc\ de\ f)
 * @param input string 
 * @return replacement string
 */
std::string replace_white_spaces(std::string input_str)
{
	if (input_str == "")
	{
		return "";
	}

	std::string new_str = "";

	for (size_t i = 0; i < input_str.size(); i++)
	{
		if (input_str[i] == ' ')
		{
			new_str += '\\';
			new_str += " ";
		}
		else
		{
			new_str += input_str[i];
		}
	}
	
	return new_str;
}

/**
 * Returns a new value for a rotary knob new entry.
 * Rotary wraparound at 127.
 * @param previous controled value
 * @param new rotary encoder value
 * @param pointer to previous rotary encoder
 * @param controled value minimum value
 * @param controled value maximum value
 * @param increment or decrement value for each call
 * @return new controled value
 */
int update_rotary_encoder_value(int prev_value,
								int new_rot_val,
								int *prev_rot_val,
								int min_val,
								int max_val,
								int inc_dec_value,
								int time_guard_ms)
{
	static auto last_call_time = std::chrono::steady_clock::now();

	auto current_time = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
					   current_time - last_call_time)
					   .count();
	last_call_time = current_time;

	// Check if less than time_guard_ms since last call
	if (elapsed < time_guard_ms)
	{
		return prev_value;
	}
	
	if (!prev_rot_val)
	{
		return prev_value; // Guard against null pointer
	}
	
	int new_value = prev_value;
	
	if (((new_rot_val - *prev_rot_val) > 0) && ((new_rot_val - *prev_rot_val) < 80))
	{
		/* CW */
		new_value = prev_value + inc_dec_value;
		if (new_value > max_val)
		{
			new_value = max_val;
		}
	}
	else
	{
		/* CCW */
		new_value = prev_value - inc_dec_value;
		if (new_value < min_val)
		{
			new_value = min_val;
		}
	}
	
	*prev_rot_val = new_rot_val;
	
	return new_value;
}

/**
 * Returns a new value for a slider new entry 0-100.
 * @param new slider value
 * @param normalized value maximum value
 * @param normalized value minimum value
 * @return new controled value
 */
int normalize_slider_value(int new_value, int max_val, int min_val)
{
	int normlized_value = (int)(((new_value / 100.0) * (max_val - min_val)) + min_val);	
	
	return normlized_value;
}

std::string getEthernetIP(const std::string &interfaceName)
{
	struct ifaddrs *interfaces = nullptr;
	struct ifaddrs *tempAddr = nullptr;
	std::string ipAddress = "";

	// Retrieve the current interfaces
	if (getifaddrs(&interfaces) == 0)
	{
		tempAddr = interfaces;

		// Loop through the linked list of interfaces
		while (tempAddr != nullptr)
		{
			// Check if it is an IPv4 interface
			if (tempAddr->ifa_addr != nullptr && tempAddr->ifa_addr->sa_family == AF_INET)
			{
				// Check if the interface name matches eth0
				if (std::string(tempAddr->ifa_name) == interfaceName)
				{
					char ipBuffer[INET_ADDRSTRLEN];
					struct sockaddr_in *ipv4 = (struct sockaddr_in *)tempAddr->ifa_addr;

					// Convert the IP structure to a readable string
					if (inet_ntop(AF_INET, &(ipv4->sin_addr), ipBuffer, INET_ADDRSTRLEN))
					{
						ipAddress = ipBuffer;
						break; // IP found, exit loop
					}
				}
			}
			tempAddr = tempAddr->ifa_next;
		}
	}

	// Free allocated memory
	if (interfaces != nullptr)
	{
		freeifaddrs(interfaces);
	}

	return ipAddress;
}

// Helper to check if a string is structured as valid Base64 data
bool is_valid_base64(const std::string &s)
{
	if (s.empty() || s.length() % 4 != 0)
		return false;

	// Check if it contains only legal Base64 characters
	return std::all_of(s.begin(), s.end(), [](unsigned char c) {
		return (std::isalnum(c) || c == '+' || c == '/' || c == '=');
	});
}

// Converts a Base64 string back into raw binary bytes
std::vector<uint8_t> decode_base64(const std::string &input)
{
	static const std::string b64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	std::vector<uint8_t> out;
	int val = 0, valb = -8;

	for (unsigned char c : input)
	{
		if (c == '=')
			break; // Stop at padding
		size_t idx = b64_chars.find(c);
		if (idx == std::string::npos)
			continue; // Skip invalid chars

		val = (val << 6) + idx;
		valb += 6;
		if (valb >= 0)
		{
			out.push_back(static_cast<uint8_t>((val >> valb) & 0xFF));
			valb -= 8;
		}
	}
	return out;
}

// Converts raw binary bytes into a Base64 encoded string
std::string encode_base64(const std::vector<uint8_t> &input)
{
	static const char b64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	std::string out;
	size_t i = 0;
	size_t length = input.size();

	// Process blocks of 3 bytes into blocks of 4 Base64 characters
	while (i < length)
	{
		uint32_t octet_a = i < length ? input[i++] : 0;
		uint32_t octet_b = i < length ? input[i++] : 0;
		uint32_t octet_c = i < length ? input[i++] : 0;

		uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

		out.push_back(b64_chars[(triple >> 18) & 0x3F]);
		out.push_back(b64_chars[(triple >> 12) & 0x3F]);
		out.push_back(b64_chars[(triple >> 6) & 0x3F]);
		out.push_back(b64_chars[triple & 0x3F]);
	}

	// Replace trailing extra padding values if the original size wasn't divisible by 3
	size_t remainder = length % 3;
	if (remainder == 1)
	{
		out[out.size() - 1] = '=';
		out[out.size() - 2] = '=';
	}
	else if (remainder == 2)
	{
		out[out.size() - 1] = '=';
	}

	return out;
}

// Used for extracting Settings names:
// /x/y/mso/file_name.xml -> mso: file_name
std::optional<std::string> format_settings_name_string(std::string_view path)
{
	// 1. Locate the position of the extension dot and the last slash
	size_t dot_pos = path.rfind('.');
	size_t last_slash = path.rfind('/');

	// Find the second-to-last slash by searching backwards from just before the last slash
	size_t second_last_slash = (last_slash != std::string_view::npos && last_slash > 0)
								   ? path.rfind('/', last_slash - 1)
								   : std::string_view::npos;

	// 2. Structural safety check: Ensure all necessary delimiters exist in the path
	if (dot_pos == std::string_view::npos ||
		last_slash == std::string_view::npos ||
		second_last_slash == std::string_view::npos ||
		last_slash >= dot_pos ||
		second_last_slash >= last_slash)
	{

		return std::nullopt; // Return null state if the path format is unparseable
	}

	// 3. Slice out the directory 'y' and the 'file_name' safely using substrings
	std::string_view folder = path.substr(second_last_slash + 1, last_slash - second_last_slash - 1);
	std::string_view file_name = path.substr(last_slash + 1, dot_pos - last_slash - 1);

	// 4. Build and return the consolidated layout string
	return std::string(folder) + ": " + std::string(file_name);
}

