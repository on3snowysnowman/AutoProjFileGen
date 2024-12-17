#include <iostream>
#include <string>

#include "JsonHandler.hpp"
#include "FileSystemHandler.hpp"
#include "TextFileHandler.hpp"
#include "TimeObserver.hpp"

int main()
{
    json config_json = JsonHandler::get("config.json");

    // Get the name of the file the user wants to create.
    std::string new_file_name = config_json.at("file_name");

    // Assign the directories for each position of the new file.

    std::string include_directory = std::string(config_json.at("include_directory"))
        + new_file_name + ".hpp";

    std::string cpp_directory = std::string(config_json.at("cpp_directory")) 
        + new_file_name + ".cpp";

    // The current date (time).
    std::string date = TimeObserver::get_local_date();

    // Default cpp file contents. 
    const std::string DEF_CPP_CONTENTS =
    "/**\n"
    " * @file " + new_file_name + ".cpp\n"
    " * @author Joel Height (On3SnowySnowman@gmail.com)\n"
    " * @brief \n"
    " * @version 0.1\n"
    " * @date " + date + "\n"
    " *\n * @copyright Copyright (c) 2024\n"
    " *\n"
    " */\n\n#include \"" + new_file_name + ".hpp\"\n\n\n"
    "// Constructors / Deconstructor\n\n\n\n// Public\n\n\n\n// Private\n\n\n";

    // Default header file contents.
    const std::string DEF_HEADER_CONTENTS = 
    "/**\n"
    " * @file " + new_file_name + ".hpp\n"
    " * @author Joel Height (On3SnowySnowman@gmail.com)\n"
    " * @brief \n"
    " * @version 0.1\n"
    " * @date " + date + "\n"
    " *\n * @copyright Copyright (c) 2024\n"
    " *\n"
    " */\n\n#pragma once\n\n\n";

    // Header file already exists with file overwriting disabled.
    if(FileSystemHandler::does_directory_exist(include_directory) && !config_json.at("overwrite_existing_files"))
    {
        std::cout << "[WARN] Header file already exists with file overwriting disabled. Skipping...\n";
    }

    else
    {
        // Write the default header file contents to the header file.
        TextFileHandler::add_to_buffer(DEF_HEADER_CONTENTS);
        if(!TextFileHandler::write(include_directory))
        {
            std::cout << "[ERR] Failed to write header file.\n";
        }
    }

    // Cpp file already exists with file overwriting disabled.
    if(FileSystemHandler::does_directory_exist(cpp_directory) && !config_json.at("overwrite_existing_files"))
    {
        std::cout << "[WARN] Cpp file already exists with file overwriting disabled. Skipping...\n";
    }

    else
    {
        // Write the default cpp file contents to the cpp file.
        TextFileHandler::add_to_buffer(DEF_CPP_CONTENTS);
        if(!TextFileHandler::write(cpp_directory))
        {
            std::cout << "[ERR] Failed to write cpp file.\n";
        }
    }

    return 0;
}
