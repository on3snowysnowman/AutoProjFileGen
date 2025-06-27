#include <iostream>
#include <string>

#include "JsonHandler.hpp"
#include "FileSystemHandler.hpp"
#include "TextFileHandler.hpp"
#include "TimeObserver.hpp"

void generate_header_file(const json& config_json, 
    const std::string& new_file_name, const std::string& full_include_path)
{
    // The current date (time).
    std::string date = TimeObserver::get_local_date();

    // Header file already exists with file overwriting disabled.
    if(FileSystemHandler::does_directory_exist(full_include_path) && 
        !config_json.at("overwrite_existing_files"))
    {
        std::cout << "[WARN] Header file already exists with file overwriting"
            " disabled. Skipping...\n";
        return;
    }

    std::string uppercase_file_name = new_file_name;
    std::transform(uppercase_file_name.begin(), uppercase_file_name.end(), 
        uppercase_file_name.begin(),
                [](unsigned char c) { return std::toupper(c); });

    // Default header file contents.
    std::string def_header_contents = 
    "/**\n"
    " * @file " + new_file_name + ".h\n"
    " * @author Joel Height (On3SnowySnowman@gmail.com)\n"
    " * @brief \n"
    " * @version 0.1\n"
    " * @date " + date + "\n"
    " *\n * @copyright Copyright (c) 2025\n"
    " *\n"
    " */\n\n#ifndef " + uppercase_file_name + "_H\n"
    "#define " + uppercase_file_name + "_H\n\n\n\n#endif // "
    + uppercase_file_name + "_H";

    // Write the default header file contents to the header file.
    TextFileHandler::add_to_buffer(def_header_contents);
    if(!TextFileHandler::write(full_include_path))
    {
        std::cout << "[ERR] Failed to write header file.\n";
    }
}

void generate_c_file(const json& config_json,
    const std::string& new_file_name, const std::string& full_c_path)
{
    // The current date (time).
    std::string date = TimeObserver::get_local_date();

    // C file already exists with file overwriting disabled.
    if(FileSystemHandler::does_directory_exist(full_c_path) && 
        !config_json.at("overwrite_existing_files"))
    {
        std::cout << "[WARN] C file already exists with file overwriting "
            "disabled. Skipping...\n";
        return;
    }

    std::string c_header_include_path = 
        config_json.at("c_header_include_path");

    // Default c file contents. 
    std::string def_c_contents =
    "/**\n"
    " * @file " + new_file_name + ".c\n"
    " * @author Joel Height (On3SnowySnowman@gmail.com)\n"
    " * @brief \n"
    " * @version 0.1\n"
    " * @date " + date + "\n"
    " *\n * @copyright Copyright (c) 2024\n"
    " *\n"
    " */\n\n#include \"" + c_header_include_path + "\"\n\n";

    // Write the default c file contents to the c file.
    TextFileHandler::add_to_buffer(def_c_contents);
    if(!TextFileHandler::write(full_c_path))
    {
        std::cout << "[ERR] Failed to write c file.\n";
    }
}


int main()
{
    json config_json = JsonHandler::get("config_c.json");

    // Get the name of the file the user wants to create.
    std::string new_file_name = config_json.at("file_name");

    // Assign the directories for each position of the new file.

    std::string include_directory = config_json.at("include_directory");

    if(include_directory.size() != 0)
    {
        generate_header_file(config_json, new_file_name, 
            include_directory + '/' + new_file_name + ".h");
    }

    std::string c_directory = config_json.at("c_directory");

    if(c_directory.size() != 0)
    {
        generate_c_file(config_json, new_file_name,
            c_directory + '/' + new_file_name + ".c");
    }
    
    return 0;
}
