/**
*	@file		utils.h
*	@author		Nahum Budin
*	@date		12-Jul-2024
*	@version	1.0 
*
*	@brief		Utilities.
* 
*	History:\n
*/
#pragma once

#include <string>
#include <string_view>
#include <optional>

#include "Defs.h"


std::string strip_client_name_prefix(std::string name);

std::string replace_white_spaces(std::string input_str);

int update_rotary_encoder_value(int prev_val, int new_rot_val, int *prev_rot_val,
								int min_val, int max_valint, int inc_dec_value,
								int time_guard_ms = _DIAL_TIME_GUARD_MS);

int normalize_slider_value(int new_value, int max_val, int min_val);

std::string getEthernetIP(const std::string &interfaceName = "eth0");

// Helper to check if a string is structured as valid Base64 data
bool is_valid_base64(const std::string &s);

// Converts a Base64 string back into raw binary bytes
std::vector<uint8_t> decode_base64(const std::string &input);

// Converts raw binary bytes into a Base64 encoded string
std::string encode_base64(const std::vector<uint8_t> &input);

// Used for extracting Settings names:
// /x/y/mso/file_name.xml -> mso: file_name
std::optional<std::string> format_settings_name_string(std::string_view path);
