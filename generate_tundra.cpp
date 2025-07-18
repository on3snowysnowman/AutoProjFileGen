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

    std::string namespace_signature = config_json.at("namespace_sig");

    // Default header file contents.
    std::string def_header_contents = 
    "/**\n"
    " * @file " + new_file_name + ".hpp\n"
    " * @author Joel Height (On3SnowySnowman@gmail.com)\n"
    " * @brief \n"
    " * @version 0.1\n"
    " * @date " + date + "\n"
    " *\n * @copyright Copyright (c) 2024\n"
    " *\n"
    " */\n\n#pragma once\n\n\nnamespace Tundra::" +  namespace_signature +
    "\n{\n\n";

    // This is a class header file.
    if(config_json.at("is_component_file"))
    {
        def_header_contents += "// Containers ---------------------------------"
            "---------------------------------\n\nstruct " + new_file_name + 
            " {};\n\n\n// Internal Methods ----------------------------------"
            "-----------------------------\n\nnamespace Internal\n{\n\n} "
            "// namespace Internal\n\n\n// Public ------------------------------"
            "---------------------------------------\n\n";
    }

    def_header_contents += "} // namespace Tundra::" + namespace_signature +
        "\n";

    // Write the default header file contents to the header file.
    TextFileHandler::add_to_buffer(def_header_contents);
    if(!TextFileHandler::write(full_include_path))
    {
        std::cout << "[ERR] Failed to write header file.\n";
    }
}

void generate_cpp_file(const json& config_json,
    const std::string& new_file_name, const std::string& full_cpp_path)
{
    // The current date (time).
    std::string date = TimeObserver::get_local_date();

    // Cpp file already exists with file overwriting disabled.
    if(FileSystemHandler::does_directory_exist(full_cpp_path) && 
        !config_json.at("overwrite_existing_files"))
    {
        std::cout << "[WARN] Cpp file already exists with file overwriting "
            "disabled. Skipping...\n";
        return;
    }

    std::string cpp_header_include_path = 
        (std::string)config_json.at("include_directory") + "/" + new_file_name + 
        ".hpp";
        // config_json.at("cpp_header_include_path");

    // Default cpp file contents. 
    std::string def_cpp_contents =
    "/**\n"
    " * @file " + new_file_name + ".cpp\n"
    " * @author Joel Height (On3SnowySnowman@gmail.com)\n"
    " * @brief \n"
    " * @version 0.1\n"
    " * @date " + date + "\n"
    " *\n * @copyright Copyright (c) 2024\n"
    " *\n"
    " */\n\n#include \"" + cpp_header_include_path + "\"\n\n";
    
    std::string namespace_sig = config_json.at("namespace_sig");

    if(config_json.at("is_component_file"))
    {
        def_cpp_contents += "\n// Internal -----"
            "---------------------------------------------------------------\n"
            "\n\n\n// Public --------------------------------------------------"
            "--------------------\n";
    }
    
    // Write the default cpp file contents to the cpp file.
    TextFileHandler::add_to_buffer(def_cpp_contents);
    if(!TextFileHandler::write(full_cpp_path))
    {
        std::cout << "[ERR] Failed to write cpp file.\n";
    }
}


int main()
{
    json config_json = JsonHandler::get("config_tundra.json");

    // Get the name of the file the user wants to create.
    std::string new_file_name = config_json.at("file_name");

    // Assign the directories for each position of the new file.

    std::string include_directory = config_json.at("include_directory");

    if(include_directory.size() != 0)
    {
        generate_header_file(config_json, new_file_name, 
            include_directory + '/' + new_file_name + ".hpp");
    }

    std::string cpp_directory = config_json.at("cpp_directory");

    if(cpp_directory.size() != 0)
    {
        generate_cpp_file(config_json, new_file_name,
            cpp_directory + '/' + new_file_name + ".cpp");
    }
    
    return 0;
}
